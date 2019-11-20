#include "defines.h"
#include "Display/Primitives.h"
#include "Utils/StringUtils.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>


const char * const String::ERROR = "---.---";


String::String() : buffer(nullptr)
{
    Set(TypeConversionString::None, "");
}


String::String(const String &rhs) : buffer(nullptr)
{
    Set(TypeConversionString::None, "");

    if (Allocate(std::strlen(rhs.CString()) + 1))
    {
        std::strcpy(buffer, rhs.CString());
    }
}


String::String(char symbol) : buffer(nullptr)
{
    Set(TypeConversionString::None, "");

    if (Allocate(2))
    {
        buffer[0] = symbol;
        buffer[1] = 0;
    }
}


String::String(const char *format, ...) : buffer(nullptr)
{
    Set(TypeConversionString::None, "");

    if (format == nullptr)
    {
        return;
    }

    static const int SIZE = 100;
    char buf[SIZE + 1];

    std::va_list args;
    va_start(args, format); //-V2528
    int numSymbols = std::vsprintf(buf, format, args);
    va_end(args);

    if (numSymbols < 0 || numSymbols > SIZE)
    {
        std::strcpy(buffer, "����� ������� ���");
    }
    else if (Allocate(std::strlen(buf) + 1))
    {
        std::strcpy(buffer, buf);
    }
    else
    {
        // ����� ������
    }
}


void String::Set(TypeConversionString::E conv, const char *format, ...)
{
    Free();

    if(format)
    {
        static const int SIZE = 100;
        char buf[SIZE + 1];

        std::va_list args;
        va_start(args, format); //-V2528
        int numSymbols = std::vsprintf(buf, format, args);
        va_end(args);

        if(numSymbols < 0 || numSymbols > SIZE)
        {
            std::strcpy(buffer, "����� ������� ���");
        }
        else if(Allocate(std::strlen(buf) + 1))
        {
            std::strcpy(buffer, buf);
            Conversion(conv);
        }
        else
        {
            // ����� ������
        }
    }
}


void String::Append(const char *str)
{
    if (!str || *str == '\0')
    {
        return;
    }

    String old(*this);

    Free();

    Allocate(std::strlen(old.CString()) + std::strlen(str) + 1);

    std::strcpy(buffer, old.CString());
    std::strcat(buffer, str);
}


String::~String()
{
    std::free(buffer);
}


void String::Free()
{
    if(buffer)
    {
        std::free(buffer);
        buffer = nullptr;
        Set(TypeConversionString::None, "");
    }
}


char *String::CString() const
{
    return buffer;
}


bool String::Allocate(uint size)
{
    std::free(buffer);
    buffer = static_cast<char *>(std::malloc(size));
    if (buffer)
    {
        return true;
    }
    else
    {
        LOG_ERROR("�� ������� ������");
    }
    return false;
}


int String::Draw(int x, int y, Color color) const
{
    color.SetAsCurrent();
    return Text(CString()).Draw(x, y);
}


void String::Conversion(TypeConversionString::E conv)
{
    char *pointer = buffer;

    if(conv == TypeConversionString::FirstUpper)
    {
        if(*pointer)
        {
            *pointer = SU::ToUpper(*pointer);
            pointer++;
        }

        while(*pointer)
        {
            *pointer = SU::ToLower(*pointer);
            pointer++;
        }
    }
}


void String::RemoveFromBegin(uint numSymbols)
{
    if (std::strlen(buffer) == numSymbols)
    {
        Free();
    }
    else
    {
        String old(buffer);

        Free();

        Allocate(old.Size() - numSymbols + 1);

        std::strcpy(buffer, old.CString() + numSymbols);
    }
}


uint String::Size() const
{
    if (buffer == nullptr)
    {
        return 0;
    }

    return std::strlen(buffer);
}


char &String::operator[](uint i)
{
    static char result = 0;

    if (buffer == nullptr || Size() < i)
    {
        return result;
    }

    return buffer[i];
}
