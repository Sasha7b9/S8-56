#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Keyboard.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Key::E Keyboard::WaitPressingButton()
{
    return Key::None;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Keyboard::Enable()
{
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Keyboard::Disable()
{
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString Key::Name()
{
    static const pString names[Key::Number] =
    {
        "None",
        "�������",
        "�����",
        "������",
        "������",
        "����� 1",
        "����� 2",
        "���������",
        "����/����",
        "�����",
        "�������",
        "Range 1 ������",
        "Range 1 ������",
        "RShift 1 ������",
        "RShift 1 ������",
        "Range 2 ������",
        "Range 2 ������",
        "RShift 2 ������",
        "RShift 2 ������",
        "TBase ������",
        "TBase ������",
        "TShift ������",
        "TShift ������",
        "����� ������",
        "����� ������",
        "�����",
        "������",
        "�����",
        "����",
        "����",
        "1",
        "2",
        "3",
        "4",
        "5"
    };

    return names[value];
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString TypePress::ToString()
{
    static const pString names[4] =
    {
        "����",
        "������",
        "�����",
        "�����"
    };

    return names[value];
}
