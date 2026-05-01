#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char* base;
	size_t size;
	size_t offset;
} myMemory;

// void* myMalloc(size_t size);
// void* myCalloc(size_t size, size_t type);
// void* myRealloc(void* ptr, size_t size);

// void myGetStats();

// int myFreeAll(void* ptr);
// int myFree(void* ptr);

myMemory* arenaCreate(size_t size);
void* arenaAlloc(myMemory* arena, size_t size);

void arenaReset(myMemory* arena);
int arenaDestroy(myMemory* arena);

int main(void) {
	myMemory* arena = arenaCreate(1e5);

	int* a = (int*)arenaAlloc(arena, sizeof(int));
	if(a == nullptr){
		printf("ERROR: Niezaalokowano pamięci!");
		return EXIT_FAILURE;
	}
	*a = 5;

	int* b = (int*)arenaAlloc(arena, sizeof(int));
	if(b == nullptr){
		printf("ERROR: Niezaalokowano pamięci!");
		return EXIT_FAILURE;
	}
	*b = 7;

	printf("a + b = %d\n", (*a + *b));

	arenaReset(arena);
	
	char* text = (char*)arenaAlloc(arena, 33 * sizeof(int));

	printf("Podaj tekst do 32 znaków:\n");
	scanf("%[^\n]", text);

	printf("Oto twój tekst: %s", text);

	if(arenaDestroy(arena) == -1)
		printf("ERROR: Nie zwolniono pamięci!");

	return EXIT_SUCCESS;
}

myMemory* arenaCreate(size_t size){
	myMemory* create = malloc(sizeof(myMemory));
	create->base = malloc(size * sizeof(char));

	create->size = size;
	create->offset = 0;

	return create;
}

void* arenaAlloc(myMemory* arena, size_t size) {
	if(arena->size - arena->offset < size)
		return nullptr;

	arena->offset += size;

	return (void*)(arena->base + arena->offset - size);
}

void arenaReset(myMemory* arena) {
	arena->offset = 0;
}

int arenaDestroy(myMemory* arena) {
	if(arena != nullptr) {
		free(arena);
		arena = nullptr;
		return 1;
	}

	return -1;
}
