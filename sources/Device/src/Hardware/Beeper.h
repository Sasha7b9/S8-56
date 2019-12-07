#pragma once
#include "Settings/Settings.h"


struct TypeWave
{
    enum E
    {
        Sine,
        Meandr,
        Triangle
    } value;
};


struct Beeper
{
    static void Init();
    /// ���� ������� �� ������.
    static void ButtonPress();
    /// ������� ������� ���� ����������� ������ ������ ���� ����� ���� ������������ ���� ������� ������.
    static void ButtonRelease();

    static void GovernorChangedValue();
    
    static void RegulatorShiftRotate();

    static void RegulatorSwitchRotate();

    static void WarnBeepBad();

    static void WarnBeepGood();
    /// ��� ������� ���� �������� ����� �������/��������� ����. ���� ����������� � ����.
    static void WaitForCompletion();

    static void Beep(TypePress::E type);

    static void Test();

    static uint8 Volume();

    struct Bell
    {
        static void On();

        static void Off();
    };
};
