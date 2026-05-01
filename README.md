# Memory Arena in C

This simple projects implements the simplest form of memory arena in C language.

Memory arena is previously allocated huge chunk of heap memory with it's own functions to allocate data types in this chunk for better managment of the memory with only one malloc() function call. This way your code is faster and you have more control over the memory.

### Structure of arena.c 
struct myMemory -> structure for arena that contains memory and size, offset variables.

***myMemory*** arenaCreate(**size_t size**) -> creates arena by allocating memory for our base and setting size to selected **size** and offset to 0. ***Returns pointer to arena***

***void\**** arenaAlloc(**myMemory\* arena, size_t size**) -> checks if u can "allocate" new memory, increases offset by **size**. ***Returns pointer to reserved chunk of base from previous_offset to current_offset.***

***void*** arenaReset(**myMemory\* arena**) -> resets **arena**'s offset to 0, which implies that u will be "allocating" memory form beginig of chunk. Previous data will be overriden.

***int*** arenaDestory(**myMemory* arena) -> frees **arena** if it's not a null pointer. ***Returns 1, if memory was freed; -1 otherwise.***
