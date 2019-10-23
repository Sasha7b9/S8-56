#pragma once
#include "Menu/MenuItems.h"


struct CalibratorMode
{
    enum E
    {
        Freq,
        DC,
        GND
    } value;
    explicit CalibratorMode(E v) : value(v) {};
};

struct ColorScheme
{
    enum E
    {
        WhiteLetters,   ///< � ���� ������ ��������� ��������� ���� ������� ����� - �� ����� ������ ����� �����
        BlackLetters    ///< � ���� ������ ��������� ��������� ���� ������� ������ - �� ����� ������� ��������
    } value;
    explicit ColorScheme(E v) : value(v) {}
};


struct SettingsService
{
    ColorScheme::E      colorScheme;
    CalibratorMode::E   calibratorMode;            ///< ����� ������ �����������.
    uint8               soundVolume;               ///< ��������� �����
    bool                showInfoVoltage;           ///< ���������� ���������� ������� �� ������
};



struct PageService
{
    static const Page * const self;


    struct PageBattery
    {
        static const Page * const self; 
    };


    struct PageCalibrate
    {
        static const Page * const self;
    };


    struct PageInformation
    {
        static const Page * const self;
    };
};



struct PageRTC
{
    static const Page * const self;
};
