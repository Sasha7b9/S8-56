#include "defines.h"
#include "Log.h"
#include <Display/Display.h>
#include <Hardware/CPU.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
//#include "stub.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//static bool loggerUSB = false;


#define SIZE_BUFFER_LOG 200

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Log::Write(TypeTrace type, const char *format, ...)
{
    char buffer[SIZE_BUFFER_LOG];
    char *pointer = buffer;

    if (type == TypeTrace_Error)
    {
        buffer[0] = 0;
        strcat(buffer, "!!! ERROR !!! ");
        while (*pointer++) {};
        ++pointer;
    }
    va_list args;
    va_start(args, format); //-V2528
    vsprintf(pointer, format, args);
    va_end(args);
    DISPLAY_ADD_STRING(buffer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Log::Trace(TypeTrace type, const char *module, const char *func, int numLine, char *format, ...)
{
    char buffer[SIZE_BUFFER_LOG];
    char message[SIZE_BUFFER_LOG];
    va_list args;
    va_start(args, format); //-V2528
    vsprintf(buffer, format, args);
    va_end(args);
    const int SIZE = 20;
    char numBuffer[SIZE];
    snprintf(numBuffer, 19, ":%d", numLine);
    message[0] = 0;

    if (type == TypeTrace_Error)
    {
        strcat(message, "!!!ERROR!!! ");
    }
    else if (type == TypeTrace_Info) //-V547
    {
        strcat(message, "            ");
    }
    else
    {
        // ������ ����� ���
    }

    strcat(message, module);
    strcat(message, " ");
    strcat(message, func);
    strcat(message, numBuffer);
    DISPLAY_ADD_STRING(message);
    DISPLAY_ADD_STRING(buffer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Log::DisconnectLoggerUSB()
{
    //static uint8 data = 20;
    //Log_Write("������� %d", data);
    //VCP_SendData(&data, 1);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Log::EnableLoggerUSB(bool)
{
//    loggerUSB = enable;
}
