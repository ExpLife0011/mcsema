MC-Semantics
============

[![Build Status](https://travis-ci.org/trailofbits/mcsema.svg?branch=master)](https://travis-ci.org/trailofbits/mcsema)

MC-Semantics (or mcsema, pronounced 'em see se ma') is a library for translating the semantics of native code to LLVM IR. McSema support translation of x86 machine code, including integer, floating point, and SSE instructions. Control flow recovery is separated from translation, permitting the use of custom control flow recovery front-ends. Code for McSema is open-source and licensed under BSD3.

At a high level, McSema is organized into subprojects for:
* Control Flow Recovery
* Instruction Semantics
* Binary File Parsing
* Semantics Testing

We hope that this library is useful to the program analysis and reverse engineering community. Work is in progress, and additional semantics are constantly being added. [Patches are welcome](https://github.com/trailofbits/mcsema/issues).

## Separation of Components

MC-Semantics is separated into two conceptual parts: control flow recovery and instruction translation. 

The two parts communicate via a control flow graph structure that contains native code. This control flow graph structure connects basic blocks and defines information about external calls, but provides no further semantic information.

The `bin_descend` program attempts to recover a control flow graph from a given binary file. It will write the recovered control flow graph into a Google Protocol Buffer serialized file. There is also an IDAPython script to recover control flow from within IDA Pro.

The `cfg_to_bc` program attempts to convert a control flow graph structure into LLVM bitcode. This translation process is more a transcription act than an analysis, since a control flow structure has already been recovered.

The problems of instruction semantics and control flow recovery are separated. Any recovered control flow graph, from any mechanism, may be analyzed and studied in an LLVM intermediate representation. 

## Documentation

Detailed design and usage information can be found in the [docs](docs/) directory.

### Building

Detailed build instructions for Windows and Linux are at [docs/BUILDING.md](docs/BUILDING.md). If you use Ubuntu 14.04, then `bash bootstrap.sh` will install dependencies via apt-get and compile the release version of the tools into a directory called `build`. The entire process can take over 40 minutes. 

### Usage

Usage instructions, with examples, are at [docs/TOOLS.md](docs/TOOLS.md). For more examples, see the demos described in [docs/DEMOS.md](docs/DEMOS.md).

Most of the documentation uses Windows-based examples, but pretty much everything should be cross-platform.

### Source Code Information 

The layout of the source code is described in [docs/NAVIGATION.md](docs/NAVIGATION.md). The description of the protocol buffer layout and the translation process is in [docs/USAGE_AND_APIS.md](docs/USAGE_AND_APIS.md).

## External Code
mcsema uses external code which has been included in this source release:
 * LLVM
 * Google Protocol Buffers
 * Boost

mcsema uses Intel Pin 2.10 which has not been included in this source release, but is freely available. Pin is used only for testing of instruction semantics and is not required to use the library.

## Contact

For any questions, contact mcsema@trailofbits.com.
