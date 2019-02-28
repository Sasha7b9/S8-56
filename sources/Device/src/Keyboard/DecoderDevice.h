#pragma once
#include "Command.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef bool(*pFuncBU8)(uint8);

class Decoder
{
public:

    static void AddData(uint8 data);

    static void Update();
    /// ���������� ���������� ��������, �� �� ������������ ����
    static int BytesInBuffer();

    static uint8 *Data();

    static void ClearBuffer();
};
