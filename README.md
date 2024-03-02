# Alef Programming Language

This is a port of Alef Programming Language to Unix and Plan 9 From User Space.

Alef is a concurrent programming language designed for systems software. Exception handling, process management, and synchronization primitives are implemented by the language. Programs can be written using both shared variable and message passing paradigms. Expressions use the same syntax as C, but the type system is substantially different. Alef supports object-oriented programming through static inheritance and information hiding. The language does not provide garbage collection, so programs are expected to manage their own memory.

# Installation

In order to use Alef you need to build a compiler, loader and optionally assembler and archiver (you need them to build a standard library). To build a compiler, you need to have `lib9` and `libbio` from [plan9port](https://github.com/9fans/plan9port). For a convenience, all necessary libraries are backported and stripped to a bare minimum for build to work.

After building a compiler and loader, you can start writing programs. If you want to use Alef's full potential, you'll also need to build a runtime, which provides support for guarded sections, `alloc`/`unalloc`, `alt`,  `par`, `proc`, `task` primitives as well as for a channel type and its operations.

There is a _make.sh_ script available to build/clean everything at once: bootstrap libraries, toolchain, `libA`, `libbio`, test programs and examples from [user guide](doc/ug.pdf). Provide `-v` flag to see actual commands as they are running.

# Limitations

Currently only `freebsd/386` is supported. It shouldn't be difficult to port it to `linux` or other BSD flavours. It also shouldn't be difficult to build it for `sparc` and `mips` architectures (all necessary files could be taken from [original Alef distribution](https://github.com/anton2920/alef-plan9).

What's not that simple, however, is porting it to `amd64`. That would require writing an architecture-specific portion of a compiler and also porting `6l(1)` and `6a(1)` from Plan 9, although latter is not that difficult.

# Documentation

There are a few pieces of documentation available:

- [Alef Language Reference Manual](doc/alef.pdf) by Phil Winterbottom.
- [Alef User’s Guide](doc/ug.pdf) by Bob Flandrena.
- [Man pages for Alef compiler and libraries](man/).
- [8a(1) man page](https://9p.io/magic/man2html/1/8a).
- [8l(1) man page](https://9p.io/magic/man2html/1/8l).
- [ar(1) man page](https://9p.io/magic/man2html/1/ar).

# Copyright

Pavlovskii Anton, 2024 (MIT). See [LICENSE](LICENSE) file for more details.
