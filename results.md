# Benchmark Results: Data Structures Performance Comparison

## Dataset Design

- Three input arrangements: random, sorted, and reversed
- 50K dataset for initial testing
- 10M dataset for full performance and memory benchmarks
- Separate datasets for insertion and search to avoid bias

## Data Structures Benchmarked

- Hash Table (chaining + open addressing)
- Binary Search Tree (BST)
- AVL Tree
- Trie
- Singly Linked List (SLL)
- Doubly Linked List (DLL)

## Benchmark Tasks

- **Insertion**
- **Search**
- **Deletion**
  Each tested separately using the dual-dataset approach.

## Observations

- Hash Table performed best overall, assuming good hash function
- Trie showed great search performance but high memory usage
- AVL Tree had better search time than BST but much worse insertion time
- SLL and DLL excluded from 10M tests due to O(n) bottlenecks

## Performance (10M Dataset)

| Structure  | Insert  | Search  | Unload | Total   |
| ---------- | ------- | ------- | ------ | ------- |
| Hash Table | 3.08 s  | 10.10 s | 1.43 s | 14.61 s |
| Trie       | 8.53 s  | 14.28 s | 3.25 s | 26.06 s |
| BST        | 12.96 s | 22.27 s | 1.38 s | 36.62 s |
| AVL        | 20.74 s | 20.86 s | 1.42 s | 43.02 s |

## Memory Usage (50K dataset)

| Structure  | Allocated |
| ---------- | --------- |
| SLL        | 810 KB    |
| DLL        | 1.2 MB    |
| BST/AVL    | 1.2 MB    |
| Trie       | 12 MB     |
| Hash Table | 810 KB    |

> ⚠️ Trie with 10M entries consumed ~2.57 GB and crashed under Valgrind

## Conclusion

- Hash Table: best general-purpose performer
- Trie: excellent search but impractical memory usage at scale
- AVL: balanced but slower insertions
- SLL/DLL: good for small datasets, poor scaling
