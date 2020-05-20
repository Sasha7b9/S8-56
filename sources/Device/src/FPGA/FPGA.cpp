#include "defines.h"
#include "log.h"
#include "device.h"
#include "FPGA/FPGA.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Memory/IntRAM.h"
#include "Hardware/Memory/RAM.h"
#include "Hardware/Timer.h"
#include "Settings/Settings.h"
#include "Recorder/Recorder.h"
#include <cstring>


bool   FPGA::forcedStart = false;
uint16 Osci::valueADC = 0;
uint16 FPGA::post = static_cast<uint16>(~(512));
uint16 FPGA::pred = static_cast<uint16>(~(512));

bool          FPGA::isRunning = false;


void FPGA::ForcedStart()
{
    uint8 value = static_cast<uint8>(S_TRIG_POLARITY_U8 % 2);

    uint8 stop = 0;
    if (Device::InModeRecorder())           // � ������ ������������
    {
        stop = (1 << BIT_TRIG_ENABLED);     // ������������� ������� ����, ��� ������� ������ ������ ����������
    }

    HAL_BUS::FPGA::Write8(WR::TRIG, static_cast<uint8>(value++ | stop));
    HAL_BUS::FPGA::Write8(WR::TRIG, static_cast<uint8>((value % 2) | stop));

    forcedStart = true;
}


uint16 Osci::ReadLastRecord(Chan::E ch)
{
    static uint16 address = 0;

    if(ch == ChanA)
    {
        address = static_cast<uint16>(HAL_BUS::FPGA::Read(RD::LAST_RECORD_LO) + ((HAL_BUS::FPGA::Read(RD::LAST_RECORD_HI)) << 8));

        static const uint16 deltas[8] = { 5, 5, 5, 5, 5, 10, 5, 2 };

        if (S_TIME_BASE <= TBase::_500ns)
        {
            address += deltas[S_TIME_BASE];
        }
    }

    return address;
}


void FPGA::OnPressStart()
{
    if (Device::InModeRecorder())
    {
        Recorder::OnPressStart();
    }
    else
    {
        if (IsRunning())
        {
            Osci::Stop();
        }
        else
        {
            Osci::Start(true);
        }
    }
}


void FPGA::Reset()
{
    TShift::Load();

    LoadRegUPR();
}


bool FPGA::IsRunning()
{
    return isRunning;
}


void FPGA::GiveStart(uint16 pr, uint16 po)
{
    HAL_BUS::FPGA::Write16(WR::PRED_LO, pr);
    HAL_BUS::FPGA::Write16(WR::POST_LO, po);
    HAL_BUS::FPGA::Write8(WR::START, 0xff);
}
