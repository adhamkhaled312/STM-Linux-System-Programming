## Description
### Heap Memory Manager
Provide the dynamic memory allocation service to the user space programs. 
Your HMM shall be a library that can be linked to the user application statically or dynamically. The user shall allocate the memory in bytes through {void *HmmAlloc(size_t size)}. The allocated memory can be freed through {void HmmFree(void *ptr)} with the same pointer returned from HmmAlloc().

## Features
- Support `malloc`, `calloc`, `realloc`, and `free` operations.
- Implementation of double linked list to manage and track all the blocks in the heap.
- Dynamic memory management as the implementation supports memory splitting and merging to optimize memory usage.
- Memory alignment of allocated blocks to 8 bytes.
- Interacting with the underlying heap using sbrk to request additional memory from the operating system when needed and release additional memory when not used.
- Error handling
  
## How to generate the library
you can use the makefile to compile the HMM as a static or dynamic ilbrary and link it with your program\
- static library
```bash
make static
```
- dynamic library
```bash
make dynamic
```
## testing
- Feel free to edit and try any test found in tests directory or make your own test.
