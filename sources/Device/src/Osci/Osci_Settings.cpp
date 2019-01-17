#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "device.h"
#include "FPGA/FPGA_Settings.h"
#include "FPGA/FPGA_Types.h"
#include "Hardware/FSMC.h"
#include "Settings/Settings.h"
#include "Utils/Math.h"

#include "FPGA/FPGA.h"
#include "FPGA/FPGA_Hal.h"
#include "Hardware/Timer.h"
#endif


using FPGA::HAL::GPIO::Pin;
using FPGA::Settings::ModeCouple;


using Osci::Settings::Range;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static uint8 ValueForRange(Chan::E ch);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Osci::Settings::LoadHoldfOff()
{
    FSMC::WriteToFPGA8(WR_TRIG_HOLD_ENABLE, TRIG_HOLDOFF_ENABLED ? 1U : 0U);

    uint value = (uint)(0 - TRIG_HOLDOFF + 1);

    BitSet32 bs(value);

    FSMC::WriteToFPGA8(WR_TRIG_HOLD_VALUE_LOW, bs.byte0);
    FSMC::WriteToFPGA8(WR_TRIG_HOLD_VALUE_MID, bs.byte1);
    FSMC::WriteToFPGA8(WR_TRIG_HOLD_VALUE_HI, bs.byte2);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Osci::Settings::TBase::Change(int delta)
{
    if (delta > 0)
    {
        ::Math::LimitationIncrease<uint8>((uint8 *)(&SET_TBASE), (uint8)(TBase::Size - 1));
    }
    else
    {
        if (SET_PEAKDET_EN &&                               // ���� ������ ����� �������� ���������
            SET_TBASE == TBase::MIN_PEAK_DET)               // � ���������� ������� �� �������, ��������������� ����������� � ������ �������� ��������� :
        {
            ::Display::ShowWarning(Warning::EnabledPeakDet);  // ������� ��������� �� ����
            return;                                         // � �������
        }

        ::Math::LimitationDecrease<uint8>((uint8 *)(&SET_TBASE), 0);
    }

    Load();
    Start();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString Osci::Settings::TBase::ToString() const
{
    /// ��������� ��� �������� ��������� �������� �� �������.
    static const struct StructTBase
    {
        const char *name[Language::Size];    // �������� ��������� � ��������� ����, ��������� ��� ������ �� �����.
        StructTBase(pString nRU, pString nEN)
        {
            name[Language::RU] = nRU;
            name[Language::EN] = nEN;
        };
    }
    tBases[TBase::Size] =
    {
        StructTBase("2\x10��",     "2\x10ns"),
        StructTBase("5\x10��",     "5\x10ns"),
        StructTBase("10\x10��",    "10\x10ns"),
        StructTBase("20\x10��",    "20\x10ns"),
        StructTBase("50\x10��",    "50\x10ns"),
        StructTBase("0.1\x10���",  "0.1\x10us"),
        StructTBase("0.2\x10���",  "0.2\x10us"),
        StructTBase("0.5\x10���",  "0.5\x10us"),
        StructTBase("1\x10���",    "1\x10us"),
        StructTBase("2\x10���",    "2\x10us"),
        StructTBase("5\x10���",    "5\x10us"),
        StructTBase("10\x10���",   "10\x10us"),
        StructTBase("20\x10���",   "20\x10us"),
        StructTBase("50\x10���",   "50\x10us"),
        StructTBase("0.1\x10��",   "0.1\x10ms"),
        StructTBase("0.2\x10��",   "0.2\x10ms"),
        StructTBase("0.5\x10��",   "0.5\x10ms"),
        StructTBase("1\x10��",     "1\x10ms"),
        StructTBase("2\x10��",     "2\x10ms"),
        StructTBase("5\x10��",     "5\x10ms"),
        StructTBase("10\x10��",    "10\x10ms"),
        StructTBase("20\x10��",    "20\x10ms"),
        StructTBase("50\x10��",    "50\x10ms"),
        StructTBase("0.1\x10�",    "0.1\x10s"),
        StructTBase("0.2\x10�",    "0.2\x10s"),
        StructTBase("0.5\x10�",    "0.5\x10s"),
        StructTBase("1\x10�",      "1\x10s"),
        StructTBase("2\x10�",      "2\x10s"),
        StructTBase("5\x10�",      "5\x10s"),
        StructTBase("10\x10�",     "10\x10s")
    };

    return tBases[value].name[LANG];
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Osci::Settings::TPos::InBytes()
{
    static const int m[][2][3] =
    {
        {{0,   256,  510},  {0,   512,  1022}},
        {{0,   512,  1022}, {0,  1024,  2046}},
        {{0,  1024,  2046}, {0,  2048,  4094}},
        {{0,  2048,  4094}, {0,  4096,  8190}},
        {{0,  4096,  8190}, {0,  8192, 16382}},
        {{0,  8192, 16382}, {0,  8192, 16382}},
        {{0, 16384, 32766}, {0, 16384, 32766}}
    };
    return m[(int)FPGA_ENUM_POINTS][SET_PEAKDET][value];
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4310)
#endif

void Osci::Settings::TBase::Load()
{
    static const uint8 values[TBase::Size] =
    {
        BIN_U8(00000000),  // -V2501  // 2ns     1       200MHz
        BIN_U8(00000000),  // -V2501  // 5ns     1       200MHz
        BIN_U8(00000000),  // -V2501  // 10ns    1       200MHz
        BIN_U8(00000000),  // -V2501  // 20ns    1       200MHz
        BIN_U8(00000000),  // -V2501  // 50ns    1       200MHz
        BIN_U8(00000000),  // -V2501  // 100ns   1       200MHz
        BIN_U8(00100000),  // -V2501  // 200ns   2       100MHz
        BIN_U8(00100001),  // -V2501  // 500ns   5       40MHz
        BIN_U8(00100010),  // -V2501  // 1us     10      20MHz
        BIN_U8(00100011),  // -V2501  // 2us     20      10MHz
        BIN_U8(01000101),  // -V2501  // 5us     50      4MHz
        BIN_U8(01000110),  // -V2501  // 10us    100     2MHz
        BIN_U8(01000111),  // -V2501  // 20us    200     1MHz
        BIN_U8(01001001),  // -V2501  // 50us    500     400kHz
        BIN_U8(01001010),  // -V2501  // 100us   1k      200kHz
        BIN_U8(01001011),  // -V2501  // 200us   2k      100kHz
        BIN_U8(01001101),  // -V2501  // 500us   5k      40kHz
        BIN_U8(01001110),  // -V2501  // 1ms     10k     20kHz
        BIN_U8(01001111),  // -V2501  // 2ms     20k     10kHz
        BIN_U8(01010001),  // -V2501  // 5ms     50k     4kHz
        BIN_U8(01010010),  // -V2501  // 10ms    100k    2kHz
        BIN_U8(01010011),  // -V2501  // 20ms    200k    1kHz
        BIN_U8(01010101),  // -V2501  // 50ms    500k    400Hz
        BIN_U8(01010110),  // -V2501  // 100ms   1M      200Hz
        BIN_U8(01010111),  // -V2501  // 200ms   2M      100Hz
        BIN_U8(01011001),  // -V2501  // 500ms   5M      40Hz
        BIN_U8(01011010),  // -V2501  // 1s      10M     20Hz
        BIN_U8(01011011),  // -V2501  // 2s      20M     10Hz
        BIN_U8(01011101),  // -V2501  // 5s      50M     4Hz
        BIN_U8(01011110)   // -V2501  // 10s     100M    2Hz
    };

    FPGA::ClearDataRand();

    FSMC::WriteToFPGA8(WR_TBASE, values[SET_TBASE]);

    TShift::Load();
}

#ifdef WIN32
#pragma warning(pop)
#endif

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Osci::Settings::Range::LoadBoth()
{
    uint16 val = (uint16)(ValueForRange(Chan::B) + (ValueForRange(Chan::A) << 8));

    WriteRegisters(Pin::SPI3_CS2, val);

    PAUSE_ON_MS(10);                // �������� �����, ����� ���������� ���� ������ ����������

    WriteRegisters(Pin::SPI3_CS2, 0);    // ���������� ����, ����� ���� �� ���������� �������

    DEF_STRUCT(StructRange, uint8) vals[Range::Number] =
    {
        StructRange(BIN_U8(00000000)),  // 2mV      // -V2501
        StructRange(BIN_U8(00000001)),  // 5mV      // -V2501
        StructRange(BIN_U8(00000010)),  // 10mV     // -V2501
        StructRange(BIN_U8(00000011)),  // 20mV     // -V2501
        StructRange(BIN_U8(00000001)),  // 50mV     // -V2501
        StructRange(BIN_U8(00000010)),  // 100mV    // -V2501
        StructRange(BIN_U8(00000011)),  // 200mV    // -V2501
        StructRange(BIN_U8(00000001)),  // 500mV    // -V2501
        StructRange(BIN_U8(00000010)),  // 1V       // -V2501
        StructRange(BIN_U8(00000011)),  // 2V       // -V2501
        StructRange(BIN_U8(00000001)),  // 5V       // -V2501
        StructRange(BIN_U8(00000010)),  // 10V      // -V2501
        StructRange(BIN_U8(00000011))   // 20V      // -V2501
    };

    uint8 valueA = vals[SET_RANGE_A].val;

    WritePin(Pin::A1, _GET_BIT(valueA, 1));
    WritePin(Pin::A2, _GET_BIT(valueA, 0));

    uint8 valueB = vals[SET_RANGE_B].val;

    WritePin(Pin::A3, _GET_BIT(valueB, 1));
    WritePin(Pin::A4, _GET_BIT(valueB, 0));
}

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4310)
#endif

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static uint8 ValueForRange(Chan::E ch) // -V2506
{
    static const uint8 datas[ModeCouple::Size] =
    {
        BIN_U8(01000001),  // -V2501  // DC
        BIN_U8(10000001),  // -V2501  // AC
        BIN_U8(00000010)   // -V2501  // GND
    };

    DEF_STRUCT(StructRange, uint16) values[Range::Number][2] =
    {   //             A                    B
        { BIN_U8(00100100), BIN_U8(00100100) }, // -V2501  // 2mV
        { BIN_U8(00100100), BIN_U8(00100100) }, // -V2501  // 5mV
        { BIN_U8(00100100), BIN_U8(00100100) }, // -V2501  // 10mV
        { BIN_U8(00100100), BIN_U8(00100100) }, // -V2501  // 20mV
        { BIN_U8(00010100), BIN_U8(00010100) }, // -V2501  // 50mV
        { BIN_U8(00010100), BIN_U8(00010100) }, // -V2501  // 100mV
        { BIN_U8(00010100), BIN_U8(00010100) }, // -V2501  // 200mV
        { BIN_U8(00101000), BIN_U8(00101000) }, // -V2501  // 500mV
        { BIN_U8(00101000), BIN_U8(00101000) }, // -V2501  // 1V
        { BIN_U8(00101000), BIN_U8(00101000) }, // -V2501  // 2V
        { BIN_U8(00011000), BIN_U8(00011000) }, // -V2501  // 5V
        { BIN_U8(00011000), BIN_U8(00011000) }, // -V2501  // 10V
        { BIN_U8(00011000), BIN_U8(00011000) }  // -V2501  // 20V
    };

    ModeCouple::E couple = (Device::State::InModeRecorder()) ? ModeCouple::DC : SET_COUPLE(ch);
    Range::E range = (Device::State::InModeRecorder()) ? SET_RECORD_RANGE(ch) : SET_RANGE(ch);

    if (Device::State::InModeOsci() && couple == ModeCouple::GND)
    {
        return datas[ModeCouple::GND];
    }

    return (uint8)(values[range][ch].val | datas[couple]);
}

#ifdef WIN32
#pragma warning(pop)
#endif
