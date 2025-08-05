# Data Structures Performance Comparison

A benchmarking project that compares the efficiency of core data structures in C, focusing on real-world insertion, search, and deletion performance using large datasets.

## Overview

This project implements and benchmarks six different data structures using a dual-dataset approach: one dataset for insertion operations and a separate search dataset for benchmarking queries. Initial testing used 50,000 numbers in random, sorted, and reverse-sorted arrangements to identify performance patterns, then scaled to 10 million numbers to reveal real-world bottlenecks and efficiency differences.

## Requirements

- C11 compatible compiler (clang recommended)
- POSIX-compliant system for timing functions
- Memory leak-free implementation (validated with Valgrind)

## Goals

This project demonstrates how theoretical time complexities translate (or break down) in real-world implementation, particularly highlighting how data arrangement affects structure performance. The dual-dataset methodology and scaling to 10M records exposes real-world bottlenecks beyond small-scale academic examples.

## Data Structures Implemented

- **Hash Tables** - Separate chaining and open addressing collision handling
- **Binary Search Trees (BST)** - Basic unbalanced implementation
- **AVL Trees** - Self-balancing binary search tree
- **Tries** - Prefix trees for string-based searching
- **Singly Linked Lists** - Sequential data structure
- **Doubly Linked Lists** - Bi-directional linked structure

## Key Findings

🏆 **Hash Table** delivers the best overall performance with proper hash function implementation

🥈 **Trie** shows excellent time complexity but suffers from massive memory overhead (2.57GB+ for 10M entries)

⚖️ **AVL Tree** has slower insertion due to rotation overhead, making it less efficient than basic BST for this use case

📊 **Data arrangement impact**: Sorted data significantly affects BST performance, demonstrating worst-case O(n) behavior

## Expected Time Complexities

| Structure    | Insertion                    | Search                   | Deletion                               |
| ------------ | ---------------------------- | ------------------------ | -------------------------------------- |
| Hash Table   | O(1) avg, O(n) worst         | O(1) avg, O(n) worst     | O(1) avg, O(n) worst                   |
| BST          | O(log n) avg, O(n) worst     | O(log n) avg, O(n) worst | O(log n) avg, O(n) worst               |
| AVL Tree     | O(log n)                     | O(log n)                 | O(log n)                               |
| Trie         | O(m)                         | O(m)                     | O(m)                                   |
| Linked Lists | O(1) head/tail, O(n) general | O(n)                     | O(1) if node known, O(n) search+delete |

_where m = length of key, n = number of elements_

### View Detailed Results on _[RESULTS.MD](https://github.com/zbrusco/efficiency/blob/main/RESULTS.md)_

## Setup

1. Clone the repo:

   ```bash
   git clone https://github.com/zbrusco/efficiency.git
   cd efficiency
   ```

2. Compile the project:

   ```bash
   make efficiency
   ```

3. Run benchmarks:

   ```bash
    # Structure codes:
    #   h   - Hash Table
    #   bst - Binary Search Tree
    #   avl - AVL Tree
    #   t   - Trie
    #   sll - Singly Linked List
    #   dll - Doubly Linked List
    ./efficiency dataset/random.txt search/random.txt [structure]
   ```

The benchmark runs in three phases: insertion (load full dataset), search+delete (lookup and remove), and unload (free all remaining nodes).

> ⚠️ The search function in this implementation also deletes the element if found. <br>
> This was intentional to benchmark lookup and deletion in one pass.

### Dataset Generation

The project includes `createdata.c` which generates datasets of 10 million random numbers. Use this to create custom test files or regenerate the existing datasets:

```bash
# Compile the data generator
gcc -o createdata createdata.c

# Generate new datasets
./createdata dataset/random.txt
./createdata search/random.txt

# Create sorted and reversed versions manually using system tools
sort -n dataset/random.txt > dataset/sorted.txt
sort -nr dataset/random.txt > dataset/reversed.txt
sort -n search/random.txt > search/sorted.txt
sort -nr search/random.txt > search/reversed.txt
```

## Project Structure

```
├── efficiency.c       # Main benchmarking program
├── *.c, *.h           # Data structure implementations
├── createdata.c       # Dataset generation utility
├── Makefile          # Build configuration
├── dataset/          # Primary datasets (insertion data)
├── search/           # Search datasets (query data)
└── results.md      # Benchmark results and analysis
```
