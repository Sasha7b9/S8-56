#pragma once
#include "Utils/String.h"


#define LOG_WRITE(...)      Log::Message(String(__VA_ARGS__).CString())
#define LOG_WRITE_AND_SHOW(...) Log::Message(String(__VA_ARGS__).CString()); Painter::EndScene();
#define LOG_ERROR(...)      Log::Message(__FILE__, __LINE__, String(__VA_ARGS__).CString())


#define LOG_FUNC_ENTER()     Log::Message(String("%s %d enter", __FUNCTION__, __LINE__).CString())
#define LOG_FUNC_LEAVE()     Log::Message(String("%s %d leave", __FUNCTION__, __LINE__).CString())



class Log
{
public:
    static void Message(const char *message);
    static void Message(const char *file, int line, char *message);
private:
};
