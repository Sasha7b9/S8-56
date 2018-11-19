#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "log.h"
#include "Display/Console.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SIZE_BUFFER 200


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Log::Message(char *format, ...)
{
    static char buffer[SIZE_BUFFER];
    buffer[0] = 0;
    
    va_list args;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    Console::AddString(buffer);
}
