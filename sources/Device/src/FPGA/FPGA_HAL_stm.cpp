#include "defines.h"
#include "globals.h"
#include "FPGA/FPGA.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL.h"


static uint timeFireTrig = 0;   // ����� ��������� �������� �������������

extern uint16 flagFPGA;

void FPGA::ReadFlag()
{
    flagFPGA = static_cast<uint16>(HAL_BUS::FPGA::Read(RD::FLAG_LO) | (HAL_BUS::FPGA::Read(RD::FLAG_HI) << 8));

    if (Flag::TrigReady() && !forcedStart)
    {
        timeFireTrig = TIME_MS;
        Trig::pulse = true;
        OsciStateWork::triggered = true;
    }

    if(!Flag::TrigReady() && TIME_MS - timeFireTrig > 1000)
    {
        Trig::pulse = false;
    }

    FreqMeter::Update();
}
