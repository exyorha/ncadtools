# NCAD netlist tools

This repository documents the format of NCAD netlists as used in the L. D.
synthesis toolchain. It includes a library for serializing and deserializing
these netlists, as well as converting them to human-readable synthesizable Verilog.

## Building the tools

You will need git, CMake 3.17 or newer, and a compiler supporting C++17.

Check out the sources:

    git clone https://github.com/moon-touched/ncadtools
    cd ncadtools
    git submodule update --init

Build the tools:

    mkdir build; cd build
    cmake ..
    make

## Using the tools

To convert an NCAD file to Verilog, run:

    ./build/ngd2v/ngd2v input.ngd output.v

The produced `output.v` file contains the same netlist as `input.ngd` as synthesizable Verilog.

## License

NCAD netlist tools are distributed under the terms of [MIT License](LICENSE.md).