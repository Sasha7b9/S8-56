#include "defines.h"
#include "Data/Heap.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const uint SIZE_BUFFER = 73 * 1024 + 844;
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
