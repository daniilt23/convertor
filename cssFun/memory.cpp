#include "memory.h"

char* allocateMemory(size_t size)
{
    return (char*)malloc(sizeof(char) * size);
}
