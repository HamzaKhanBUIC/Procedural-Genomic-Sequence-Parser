# Procedural Genomic Sequence Parser

> High-throughput, zero-overhead C++ genomic sequence analysis engine optimized for linear-time nucleotide frequency calculations, GC-ratio analysis, and sequence motif detection.

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17%2F20-00599C.svg?logo=c%2B%2B)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Build: CMake](https://img.shields.io/badge/Build-CMake-orange.svg?logo=cmake)](https://cmake.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

---

## Overview

Modern object-oriented bioinformatics libraries often introduce significant dynamic heap allocations, cache fragmentation, and pointer indirection when processing multi-gigabyte genomic sequence datasets (e.g., FASTA/FASTQ).

Bridging pre-medical biological domain knowledge with low-level systems engineering, **Procedural Genomic Sequence Parser** employs a procedural execution model. By avoiding virtual function tables and excessive object wrappers, the engine streams raw DNA datasets into contiguous memory buffers, enabling fast $O(N)$ nucleotide analysis with minimal RAM overhead.

---

## Problem & Algorithmic Rationale

- **Memory Fragmentation**: Heavy OOP wrappers allocate metadata objects per individual read or sequence segment, degrading CPU cache locality on large datasets.
- **Computational Overhead**: Virtual method dispatch adds unnecessary CPU cycles during high-throughput sequence scanning.
- **Procedural Solution**: Contiguous memory buffer streaming with stack-allocated accumulator tables allows the CPU to leverage vector prefetching and hardware branch prediction.

---

## System Architecture

```mermaid
graph LR
    A[Raw FASTA / DNA Text Dataset] --> B[Direct Buffer Streamer]
    B --> C[Linear-Time Character Scanner - O(N)]
    C --> D[Nucleotide Frequency Table - A, C, G, T]
    C --> E[GC-Content Ratio Engine]
    C --> F[Motif & Target Marker Locator]
    D --> G[Standard Output / Analysis Report]
    E --> G
    F --> G
```

---

## Core Capabilities

1. **Nucleotide Frequency Accumulation**: High-speed count of Adenine (A), Cytosine (C), Guanine (G), and Thymine (T) bases.
2. **GC-Content Calculation**: Computes the percentage of nitrogenous bases (G-C pairs) to analyze thermal stability and genomic coding density.
3. **Motif Scanning**: Linear scanning for custom genetic markers and restriction enzyme recognition sites.

---

## Repository Structure

```
.
├── Program.cpp               # Core procedural C++ parser implementation
├── dna_sample.txt            # Sample multi-kilobase genomic sequence dataset
├── build/                    # Build output directory
├── .vscode/                  # Editor build & debug tasks
├── CMakeLists.txt            # CMake compilation configuration
└── README.md                 # Technical documentation
```

---

## Getting Started

### Prerequisites
- C++17 compliant compiler (`g++`, `clang++`, or `MSVC`)
- [CMake](https://cmake.org/) 3.20+ (or direct CLI compilation)

### Building with CMake
```bash
# Clone the repository
git clone https://github.com/HamzaKhanBUIC/Procedural-Genomic-Sequence-Parser.git
cd Procedural-Genomic-Sequence-Parser

# Generate build files and compile
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Direct CLI Compilation (g++ / clang++)
```bash
# Compile directly with maximum optimization (-O3)
g++ -O3 -std=c++17 -o genomic_parser Program.cpp

# Execute parser against the sample DNA dataset
./genomic_parser ../dna_sample.txt
```

---

## Sample Output

```text
=====================================================
          GENOMIC SEQUENCE ANALYSIS REPORT           
=====================================================
Target Dataset         : dna_sample.txt
Total Bases Processed  : 142,850 bp
Adenine  (A) Count     : 42,120 (29.48%)
Thymine  (T) Count     : 41,890 (29.32%)
Guanine  (G) Count     : 29,430 (20.60%)
Cytosine (C) Count     : 29,410 (20.59%)
-----------------------------------------------------
GC-Content Ratio       : 41.19%
Target Marker Hits     : 14 matches found
Processing Time        : < 4 ms (Linear Pass)
=====================================================
```

---

## Limitations

- **File Format Scope**: Currently optimized for raw plain-text nucleotide streams and single-record FASTA files. Multi-line header parsing for complex FASTQ quality score arrays is planned for future iterations.

---

## License

MIT License - see [LICENSE](LICENSE) for details.
```
