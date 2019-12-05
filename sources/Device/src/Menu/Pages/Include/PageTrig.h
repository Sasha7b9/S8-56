#pragma once
#include "Menu/MenuItems.h"
#include "Settings/SettingsOsci.h"


/// �������� �������������
struct TrigSource
{
    TrigSource() {};
    operator Chan::E();
    static void Load();
};

/// ����� ������ ������������
struct TrigModeFind
{
    enum E
    {
        Hand,      ///< ������� ������������� ��������������� ������� ��� ������������� - ����������� ��������� ������.
        Auto       ///< ���������� ������ ������������� ������������ ������������� ����� ������� ������ ���������� �������.
    } value;
    explicit TrigModeFind(E v) : value(v) {};
};

struct TrigInput
{
    enum E
    {
        Full,
        HF,
        LF
    };
    TrigInput() {};
    /// ���������� � �������������� ��������� ������, ���������� �� �������� � ���� �������������
    static void Load();
};

struct TrigPolarity
{
    enum E
    {
        Rising,
        Falling
    };

    void Load();
};

/// ����� �������.
struct TrigStartMode
{
    enum E
    {
        Auto,     ///< ��������������.
        Wait,     ///< ������.
        Single    ///< �����������.
    } value;
    explicit TrigStartMode(E v) : value(v) {};
};


struct SettingsTrig
{
    Chan::E          source;
    TrigInput::E     input;
    TrigPolarity::E  polarity;
    int16            level[Chan::Count];
    TrigStartMode::E startMode;         ///< ����� �������.
    TrigModeFind::E  modeFind;          ///< ����� ������������� - ������� ��� �������������.
                                        /// \todo ����������� trig_holdOff ������������
    int16            holdOff;           ///< ��������� �������������
    bool             holdOffEnabled;    ///< ��������� ��������� �������������
};



struct PageTrig
{
    static void OnChanged_Mode(bool active);

    static const Page * const self;


    struct PageHoldOff
    {
        static const Page * const self;
    };


    struct PageFind
    {
        static const Page * const self;
    };
};
