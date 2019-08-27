#include "defines.h"
#include "Data/Heap.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const uint SIZE_BUFFER = 72 * 1024;
static uint8 buffer[SIZE_BUFFER];


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void *Heap::Begin()
{
    return buffer;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void *Heap::End()
{
    return buffer + Size();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint Heap::Size()
{
    return SIZE_BUFFER;
}
