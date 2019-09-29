#pragma once
#include "Menu/MenuItems.h"
#include "Settings/SettingsOsci.h"


/// ��� �������� ������
struct RecorderTypeStorage
{
    enum E
    {
        RAM,    ///< ���
        ROM,    ///< ����� ��
        EXT     ///< ����� ��
    } value;
    explicit RecorderTypeStorage(E v) : value(v) {};
};

/// ������������ ��� ������ ���
struct RecorderAxis
{
    enum E
    {
        X,
        Y
    } value;
    explicit RecorderAxis(E v) : value(v) {};
};

/// ������ �� �������
struct RecorderScaleX
{
    enum E
    {
        _100ms, // TBase = 0.1c
        _200ms, // TBase = 0.2c
        _500ms, // TBase = 0.5c
        _1s,    // TBase = 1c
        _2s,    // TBase = 2c
        _5s,    // TBase = 5c
        _10s,   // TBase = 10c
        Size
    } value;
    explicit RecorderScaleX(E v) : value(v) {};
    static void Load();
    static void Change(int delta);
    static RecorderScaleX &Current();
    pString ToString() const;
    /// ���������� �������� ����������� ������ � ������/���
    uint BytesToSec() const;
    /// ���������� ����� ���������� ����� �����
    uint TimeForPointMS() const;
};


struct SettingsRecorder
{ //-V802
    bool                    enabledChanA;   ///< ��������� ������ ������ 1
    bool                    enabledChanB;   ///< ��������� ������ ������ 2
    bool                    enabledSensor;  ///< ��������� ������ ��������� �������
    RecorderTypeStorage::E  storageRecord;  ///< ���� ��������� ������
    RecorderTypeStorage::E  storagePlay;    ///< ������ ����� ����������� ������
    RecorderAxis::E         axisMove;       ///< ������� ��� �����������
    RecorderAxis::E         axisZoom;       ///< ������� ��� ���������������
    RecorderScaleX          scaleX;         ///< ������������� ������� �� �������
    int8                    currentCursor;
    Range::E                unused[2];      ///< ������� �� ��������� � ������ ������������
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PageRecorder
{
    static const Page *const self;

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    struct PageSource
    {
        static const Page *const self;
    };

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    struct PageShow
    {
        static const Page *const self;

        //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        struct PageOperations
        {
            static const Page *const self;
        };

        struct PageView
        {
            static const Page *const self;

            //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            struct PageCursors
            {
                static const Page *const self;
            };
        };
    };
};
