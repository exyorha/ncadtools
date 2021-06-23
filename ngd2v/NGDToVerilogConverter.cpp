#include "NGDToVerilogConverter.h"

#include <ncadtoollib/NGDFile.h>

#include <iostream>
#include <sstream>

#include <inttypes.h>

NGDToVerilogConverter::NGDToVerilogConverter(const ncadtoollib::NGDFile& ngd, std::ostream& output) : m_ngd(ngd), m_output(output) {

}

NGDToVerilogConverter::~NGDToVerilogConverter() = default;

void NGDToVerilogConverter::convert() {
	m_output <<
		"/*\n"
		" * Generated from " << m_inputFilename << " with ngd2v\n"
		" *\n"
		" * Toplevel module: " << m_ngd.netlistObject.objectName.string() << "\n"
		" *\n";

	for (const auto& propVariant : m_ngd.netlistObject.properties.properties) {
		const auto &prop = ncadtoollib::propertyFromVariant(propVariant.variant);

		m_output << " * " << prop.propertyName.string();

		auto value = prop.valueAsString();

		if (!value.empty())
			m_output << ": " << value;

		m_output << "\n";

	}

	m_output <<
		" */\n"
		"\n";

	for (const auto& modVariant : m_ngd.hierarchy.blocks) {
		const auto& mod = ncadtoollib::moduleFromVariant(modVariant.variant);
		
		m_moduleMap.emplace(mod.thisModuleId, modVariant);
		m_moduleChildren.emplace(mod.parentModuleId, mod.thisModuleId);
	}

	writeModuleToOutput(m_ngd.hierarchy.topModuleId);
}

void NGDToVerilogConverter::writeModuleToOutput(uint32_t moduleId) {
	auto result = m_modulesAlreadyOutput.emplace(moduleId);
	if (!result.second)
		return;

	auto childRange = m_moduleChildren.equal_range(moduleId);
	for (auto childIt = childRange.first; childIt != childRange.second; ++childIt) {
		writeModuleToOutput(childIt->second);
	}

	auto modVariantIt = m_moduleMap.find(moduleId);
	if (modVariantIt == m_moduleMap.end())
		throw std::logic_error("module not found");

	const auto& modVariant = modVariantIt->second;

	std::string moduleName = getModuleName(modVariant);
	auto moduleString = convertModuleBodyToString(modVariant);

	auto bodyIt = m_moduleBodies.find(std::make_pair(moduleName, moduleString));
	if (bodyIt != m_moduleBodies.end()) {
		m_moduleNames.emplace(moduleId, bodyIt->second);
	}
	else {
		auto result = m_moduleNameCounts.emplace(moduleName, 1);

		std::string decoratedModuleName;

		if (result.second)
			decoratedModuleName = moduleName;
		else {
			auto moduleNumber = result.first->second + 1;
			result.first->second = moduleNumber;

			decoratedModuleName = moduleName + "_" + std::to_string(moduleNumber);
		}

		writeModuleImplementation(decoratedModuleName, modVariant, moduleString);

		m_moduleBodies.emplace(std::make_pair(moduleName, moduleString), decoratedModuleName);
		m_moduleNames.emplace(moduleId, decoratedModuleName);
	}
}

std::string NGDToVerilogConverter::getModuleName(const ncadtoollib::NGDModuleVariant& moduleVariant) {
	const auto& mod = ncadtoollib::moduleFromVariant(moduleVariant.variant);

	auto moduleName = mod.objectName.string();

	for (const auto& propVariant : mod.properties.properties) {
		const auto& prop = ncadtoollib::propertyFromVariant(propVariant.variant);
		const auto& name = prop.propertyName.string();

		if (name == "TYPE") {
			moduleName = prop.valueAsString();
			break;
		}
	}

	return moduleName;
}

std::string NGDToVerilogConverter::convertModuleBodyToString(const ncadtoollib::NGDModuleVariant& moduleVariant) {
	std::stringstream ss;

	const auto& mod = ncadtoollib::moduleFromVariant(moduleVariant.variant);

	std::unordered_map<uint32_t, std::string> wireNames;
	writeModuleInterfaceSection(ss, moduleVariant, wireNames);

	for (const auto& wire : mod.wires) {
		writeWireDefinition("wire", ss, wire, wireNames, false);
	}

	auto childRange = m_moduleChildren.equal_range(mod.thisModuleId);
	for (auto childIt = childRange.first; childIt != childRange.second; ++childIt) {
		auto childVariantIt = m_moduleMap.find(childIt->second);
		if (childVariantIt == m_moduleMap.end())
			throw std::logic_error("child module not found");

		const auto& childVariant = childVariantIt->second;
		const auto& childMod = ncadtoollib::moduleFromVariant(childVariant.variant);

		auto childImplIt = m_moduleNames.find(childIt->second);
		if (childImplIt == m_moduleNames.end())
			throw std::logic_error("child module is not implemented before its parent");

		ss << "\n";

		std::stringstream parameters;
		bool hasAnyParameters = false;

		for (const auto& propVariant : childMod.properties.properties) {
			const auto& prop = ncadtoollib::propertyFromVariant(propVariant.variant);
			const auto& name = prop.propertyName.string();
			auto value = prop.valueAsString();

			
			if(m_hiddenModuleParameters.count(name) == 0 && m_completelyHiddenParameters.count(name) == 0) {
				if (!hasAnyParameters)
					hasAnyParameters = true;
				else
					parameters << ",\n";

				parameters << "    ." << name << "(" << prop.valueAsVerilogFriendlyToken() << ")";
			}
		}

		ss << "  " << makeVerilogIdentifier(childImplIt->second) << " ";
		if (hasAnyParameters) {
			ss << "#(\n" << parameters.str() << "\n  ) ";
		}

		std::string originalName;
		std::string actualName;
		bool wasRenamed = getObjectNameResolvingAliases(childMod, originalName, actualName);

		ss 
			<< makeVerilogIdentifier("inst_" + actualName)
			<< " (";

		if (wasRenamed) {
			ss << " // original name: " << originalName;
		}

		ss << "\n";

		writeModuleConnections(ss, childVariant, wireNames);

		ss << "  );\n";
	}

	return ss.str();
}

void NGDToVerilogConverter::writeModuleInterfaceSection(std::ostream& stream, const ncadtoollib::NGDModuleVariant& moduleVariant, std::unordered_map<uint32_t, std::string>& wireNames) {
	std::visit([&stream, &wireNames, this](const auto& mod) {
		writeModuleInterfaceSection(stream, mod, wireNames);
	}, moduleVariant.variant);
}

void NGDToVerilogConverter::writeModuleInterfaceSection(std::ostream& stream, const ncadtoollib::NGLogBlock& mod, std::unordered_map<uint32_t, std::string>& wireNames) {
	writeModuleInterfaceSection(stream, mod.nonPrimitive.pins, wireNames);
}

void NGDToVerilogConverter::writeModuleInterfaceSection(std::ostream& stream, const ncadtoollib::NGPhysBlock& mod, std::unordered_map<uint32_t, std::string>& wireNames) {
	writeModuleInterfaceSection(stream, mod.nonPrimitive.pins, wireNames);
}

void NGDToVerilogConverter::writeModuleInterfaceSection(std::ostream& stream, const ncadtoollib::NGLogPrim& mod, std::unordered_map<uint32_t, std::string>& wireNames) {
	writeModuleInterfaceSection(stream, mod.primitive.pins, wireNames);
}

template<typename T>
void NGDToVerilogConverter::writeWireDefinition(const char* directionKeyword, std::ostream& stream, const T& wire, std::unordered_map<uint32_t, std::string>& wireNames, bool isPort) {
	bool hasPrimaryConnection = false;
	std::string primaryConnectionName;

	if (wire.internalConnectionId != 0) {
		auto it = wireNames.find(wire.internalConnectionId);
		if (it != wireNames.end()) {
			if (!isPort)
				return;

			hasPrimaryConnection = true;
			primaryConnectionName = it->second;
		}
	}

	std::string originalName, actualName;
	bool wasRenamed = getObjectNameResolvingAliases(wire, originalName, actualName);

	if (wire.internalConnectionId != 0 && !hasPrimaryConnection) {
		wireNames.emplace(wire.internalConnectionId, actualName);
	}

	writePropertiesAsVerilogAttributes(stream, wire.properties);

	stream << "  " << directionKeyword << " " << makeVerilogIdentifier(actualName);
	
	if (hasPrimaryConnection)
		stream << " = " << primaryConnectionName;
	
	stream << ";";

	if (wasRenamed)
		stream << " // original name: " << originalName;

	stream << "\n";
}

template<typename T>
void NGDToVerilogConverter::writeModuleInterfaceSection(std::ostream& stream, const std::vector<T>& pins, std::unordered_map<uint32_t, std::string>& wireNames) {
	for (const auto& pin : pins) {
		const char* directionKeyword;

		switch (pin.direction) {
		case 1:
			directionKeyword = "input";
			break;

		case 2:
			directionKeyword = "output";
			break;

		case 4:
			directionKeyword = "inout";
			break;

		default:
			throw std::logic_error("unsupported pin direction in NGD: " + std::to_string(pin.direction));
		}

		writeWireDefinition(directionKeyword, stream, pin, wireNames, true);

	}
}

void NGDToVerilogConverter::writePropertiesAsVerilogAttributes(std::ostream& stream, const ncadtoollib::NGPropertySet& properties) {
	bool firstProperty = true;

	for (const auto& propVariant : properties.properties) {
		const auto& prop = ncadtoollib::propertyFromVariant(propVariant.variant);

		if (m_completelyHiddenParameters.count(prop.propertyName.string()) != 0)
			continue;

		if (firstProperty) {
			stream << "  (* ";

			firstProperty = false;
		}
		else
			stream << ", ";


		stream << prop.propertyName.string();

		if (!std::holds_alternative<ncadtoollib::NGProperty>(propVariant.variant)) {
			stream << " = " << prop.valueAsVerilogFriendlyToken();
		}
	}

	if (!firstProperty)
		stream << " *)\n";
}

size_t NGDToVerilogConverter::ModuleBodyHasher::operator()(const std::pair<std::string, std::string>& key) const {
	std::hash<std::string> stringHasher;

	auto firstHash = stringHasher(key.first);
	auto secondHash = stringHasher(key.second);

	return firstHash ^ (secondHash + 0x9e3779b9 + (firstHash << 6) + (firstHash >> 2));
}

std::string NGDToVerilogConverter::makeVerilogIdentifier(const std::string& string) const {
	if (string.empty())
		throw std::logic_error("empty identifier");

	bool validIdentifier = true;

	auto lead = string.front();
	if ((lead >= 'A' && lead <= 'Z') || (lead >= 'a' && lead <= 'z') || lead == '_') {
		for (char ch : string) {
			if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch == '_' || ch == '$')) {
				validIdentifier = false;
				break;
			}
		}
	}
	else {
		validIdentifier = false;
	}

	if (validIdentifier)
		return string;
	else
		return "\\" + string + " ";
}

void NGDToVerilogConverter::writeModuleImplementation(const std::string& moduleName, const ncadtoollib::NGDModuleVariant& moduleVariant, const std::string& moduleBody) {
	m_output
		<<
		"module " << makeVerilogIdentifier(moduleName) << " (\n";

	writeModulePins(m_output, moduleVariant);

	m_output
		<<
		");\n"
		"\n";

	const auto& mod = ncadtoollib::moduleFromVariant(moduleVariant.variant);

	for (const auto& propVariant : mod.properties.properties) {
		const auto& prop = ncadtoollib::propertyFromVariant(propVariant.variant);
		const auto& name = prop.propertyName.string();
		auto value = prop.valueAsString();

		if (m_hiddenModuleParameters.count(name) != 0) {
			m_output << "  // " << name;
			if (!value.empty())
				m_output << ": " << value;
			m_output << "\n";
		}
		else if(m_completelyHiddenParameters.count(name) == 0) {
			m_output << "  parameter " << name << " = " << prop.valueAsVerilogFriendlyToken() << ";\n";
		}
	}

	m_output
		<< "\n"
		<< moduleBody
		<<
		"\n"
		"endmodule\n"
		"\n";
}


void NGDToVerilogConverter::writeModulePins(std::ostream& stream, const ncadtoollib::NGDModuleVariant& moduleVariant) {
	std::visit([this, &stream](const auto& mod) { writeModulePins(stream, mod); }, moduleVariant.variant);
}

void NGDToVerilogConverter::writeModulePins(std::ostream& stream, const ncadtoollib::NGLogBlock& mod) {
	writeModulePins(stream, mod.nonPrimitive.pins);
}

void NGDToVerilogConverter::writeModulePins(std::ostream& stream, const ncadtoollib::NGPhysBlock& mod) {
	writeModulePins(stream, mod.nonPrimitive.pins);
}

void NGDToVerilogConverter::writeModulePins(std::ostream& stream, const ncadtoollib::NGLogPrim& mod) {
	writeModulePins(stream, mod.primitive.pins);
}

bool NGDToVerilogConverter::getObjectNameResolvingAliases(const ncadtoollib::NGObject& object, std::string& originalName, std::string& actualName) {
	originalName = object.objectName.string();

	for (const auto& propVariant : object.properties.properties) {
		const auto& prop = ncadtoollib::propertyFromVariant(propVariant.variant);
		const auto& name = prop.propertyName.string();

		if (name == "USER_ALIAS") {
			actualName = prop.valueAsString();
			return true;
		}
	}

	actualName = originalName;
	return false;
}

template<typename T>
void NGDToVerilogConverter::writeModulePins(std::ostream& stream, const std::vector<T>& pins) {
	bool firstPin = true;

	for (const auto& pin : pins) {
		if (firstPin)
			firstPin = false;
		else
			stream << ",\n";

		stream << "    " << makeVerilogIdentifier(pin.objectName.string());
	}

	if (!firstPin)
		stream << "\n";
}

void NGDToVerilogConverter::writeModuleConnections(std::ostream& stream, const ncadtoollib::NGDModuleVariant& moduleVariant, const std::unordered_map<uint32_t, std::string>& wireNames) {
	std::visit([&stream, &wireNames, this](const auto& mod) {
		writeModuleConnections(stream, mod, wireNames);
	}, moduleVariant.variant);
}

void NGDToVerilogConverter::writeModuleConnections(std::ostream& stream, const ncadtoollib::NGLogBlock& mod, const std::unordered_map<uint32_t, std::string>& wireNames) {
	writeModuleConnections(stream, mod.nonPrimitive.pins, wireNames);
}

void NGDToVerilogConverter::writeModuleConnections(std::ostream& stream, const ncadtoollib::NGPhysBlock& mod, const std::unordered_map<uint32_t, std::string>& wireNames) {
	writeModuleConnections(stream, mod.nonPrimitive.pins, wireNames);
}

void NGDToVerilogConverter::writeModuleConnections(std::ostream& stream, const ncadtoollib::NGLogPrim& mod, const std::unordered_map<uint32_t, std::string>& wireNames) {
	writeModuleConnections(stream, mod.primitive.pins, wireNames);
}

template<typename T>
void NGDToVerilogConverter::writeModuleConnections(std::ostream& stream, const std::vector<T>& pins, const std::unordered_map<uint32_t, std::string>& wireNames) {
	bool firstPin = true;

	for (const auto& pin : pins) {
		std::string originalName, actualName;
		getObjectNameResolvingAliases(pin, originalName, actualName);

		if (firstPin)
			firstPin = false;
		else
			stream << ",\n";

		stream << "    ." << makeVerilogIdentifier(actualName) << "(";

		if (pin.externalConnectionId != 0) {
			auto connIt = wireNames.find(pin.externalConnectionId);
			if (connIt == wireNames.end())
				throw std::logic_error("wire is not connected");

			stream << makeVerilogIdentifier(connIt->second);
		}

		stream << ")";
	}

	if (!firstPin)
		stream << "\n";
}

const std::unordered_set<std::string> NGDToVerilogConverter::m_hiddenModuleParameters{
	"BLOCK_BUSINFO",
	"orig_inst_of",
	"EDIF_LEAF",
	"LIBRARY",
	"TERMINAL",
	"PHYSICAL",
	"CELL"
};

const std::unordered_set<std::string> NGDToVerilogConverter::m_completelyHiddenParameters{
	"USER_ALIAS", "TYPE"
};
