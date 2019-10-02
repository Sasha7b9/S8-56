#pragma once
#include "defines.h"



#define ERROR_HANDLER()                             ::HAL::ErrorHandler(__FILE__, __LINE__)



namespace HAL
{
    void ErrorHandler(const char *, int);

    
    class EEPROM_
    {
    public:
        static void EraseSector(uint startAddress);
        static void WriteBytes(uint address, const uint8 *data, int size);
    };

    
    class FSMC
    {
    public:
        static void WriteToPanel(uint8 *buffer, int size);
    };
}

