#ifndef NGD_TO_VERILOG_CONVERTER_H
#define NGD_TO_VERILOG_CONVERTER_H

#include <ios>
#include <unordered_set>
#include <unordered_map>

#include <ncadtoollib/NGDesign.h>

namespace ncadtoollib {
	class NGDFile;
}

class NGDToVerilogConverter {
public:
	NGDToVerilogConverter(const ncadtoollib::NGDFile& ngd, std::ostream& output);
	~NGDToVerilogConverter();

	NGDToVerilogConverter(const NGDToVerilogConverter& other) = delete;
	NGDToVerilogConverter &operator =(const NGDToVerilogConverter& other) = delete;

	inline const std::string& inputFilename() const { return m_inputFilename; }
	inline void setInputFilename(const std::string& inputFilename) { m_inputFilename = inputFilename; }

	void convert();

private:
	struct ModuleBodyHasher {
		size_t operator()(const std::pair<std::string, std::string>& key) const;
	};

	void writeModuleToOutput(uint32_t moduleId);
	std::string getModuleName(const ncadtoollib::NGDModuleVariant& moduleVariant);
	std::string convertModuleBodyToString(const ncadtoollib::NGDModuleVariant& moduleVariant);

	void writeModuleInterfaceSection(std::ostream& stream, const ncadtoollib::NGDModuleVariant& moduleVariant, std::unordered_map<uint32_t, std::string>& wireNames);

	void writeModuleInterfaceSection(std::ostream& stream, const ncadtoollib::NGLogBlock& mod, std::unordered_map<uint32_t, std::string> &wireNames);
	void writeModuleInterfaceSection(std::ostream& stream, const ncadtoollib::NGPhysBlock& mod, std::unordered_map<uint32_t, std::string>& wireNames);
	void writeModuleInterfaceSection(std::ostream& stream, const ncadtoollib::NGLogPrim& mod, std::unordered_map<uint32_t, std::string>& wireNames);

	template<typename T>
	void writeModuleInterfaceSection(std::ostream& stream, const std::vector<T>& pins, std::unordered_map<uint32_t, std::string>& wireNames);

	void writeModulePins(std::ostream& stream, const ncadtoollib::NGDModuleVariant& moduleVariant);

	void writeModulePins(std::ostream& stream, const ncadtoollib::NGLogBlock& mod);
	void writeModulePins(std::ostream& stream, const ncadtoollib::NGPhysBlock& mod);
	void writeModulePins(std::ostream& stream, const ncadtoollib::NGLogPrim& mod);

	template<typename T>
	void writeModulePins(std::ostream& stream, const std::vector<T>& pins);

	template<typename T>
	void writeWireDefinition(const char* directionKeyword, std::ostream& stream, const T& wire, std::unordered_map<uint32_t, std::string>& wireNames, bool isPort);

	void writePropertiesAsVerilogAttributes(std::ostream& stream, const ncadtoollib::NGPropertySet& properties);

	std::string makeVerilogIdentifier(const std::string& string) const;
	
	void writeModuleImplementation(const std::string& moduleName, const ncadtoollib::NGDModuleVariant& moduleVariant, const std::string& moduleBody);

	bool getObjectNameResolvingAliases(const ncadtoollib::NGObject& object, std::string& originalName, std::string& actualName);

	void writeModuleConnections(std::ostream& stream, const ncadtoollib::NGDModuleVariant& moduleVariant, const std::unordered_map<uint32_t, std::string>& wireNames);

	void writeModuleConnections(std::ostream& stream, const ncadtoollib::NGLogBlock& mod, const std::unordered_map<uint32_t, std::string>& wireNames);
	void writeModuleConnections(std::ostream& stream, const ncadtoollib::NGPhysBlock& mod, const std::unordered_map<uint32_t, std::string>& wireNames);
	void writeModuleConnections(std::ostream& stream, const ncadtoollib::NGLogPrim& mod, const std::unordered_map<uint32_t, std::string>& wireNames);

	template<typename T>
	void writeModuleConnections(std::ostream& stream, const std::vector<T> &pins, const std::unordered_map<uint32_t, std::string>& wireNames);

	const ncadtoollib::NGDFile& m_ngd;
	std::ostream& m_output;
	std::string m_inputFilename;

	std::unordered_set<uint32_t> m_modulesAlreadyOutput;
	std::unordered_map<uint32_t, const ncadtoollib::NGDModuleVariant&> m_moduleMap;
	std::unordered_multimap<uint32_t, uint32_t> m_moduleChildren;
	std::unordered_map<std::pair<std::string, std::string>, std::string, ModuleBodyHasher> m_moduleBodies;
	std::unordered_map<uint32_t, std::string> m_moduleNames;
	std::unordered_map<std::string, size_t> m_moduleNameCounts;

	static const std::unordered_set<std::string> m_hiddenModuleParameters;
	static const std::unordered_set<std::string> m_completelyHiddenParameters;
};

#endif
