#include "defines.h"
#include "FPGA/ContextOsci.h"
#include "FPGA/FPGA.h"


uint16 &ContextOsci::pred = FPGA::pred;
uint16 &ContextOsci::post = FPGA::post;
uint &ContextOsci::timeStart = FPGA::timeStart;
bool &ContextOsci::isRunning = FPGA::isRunning;


void ContextOsci::LoadRegUPR()
{
    FPGA::LoadRegUPR();
}

void ContextOsci::LoadCalibratorMode()
{
    FPGA::LoadCalibratorMode();
}

void ContextOsci::OnPressStart()
{
    FPGA::OnPressStart();
}

bool ContextOsci::IsRunning()
{
    return FPGA::IsRunning();
}

void ContextOsci::ReadFlag()
{
    FPGA::ReadFlag();
}

void ContextOsci::GiveStart()
{
    FPGA::GiveStart();
}

void ContextOsci::ReadData()
{
    FPGA::ReadData();
}

void ContextOsci::Reset()
{
    FPGA::Reset();
}

bool ContextOsci::InStateStop()
{
    return FPGA_IN_STATE_STOP;
}

bool ContextOsci::InStateWait()
{
    return FPGA_IN_STATE_WAIT;
}

void ContextOsci::SetValueADC(uint16 value)
{
    FPGA::SetValueADC(value);
}

uint ContextOsci::BytesInChannel()
{
    return FPGA::BytesInChannel();
}

bool ContextOsci::GetFlag::PRED()
{
    return FPGA::GetFlag::PRED();
}

bool ContextOsci::GetFlag::HOLD_OFF()
{
    return FPGA::GetFlag::HOLD_OFF();
}

bool ContextOsci::GetFlag::TRIG_READY()
{
    return FPGA::GetFlag::TRIG_READY();
}

bool ContextOsci::GetFlag::DATA_READY()
{
    return FPGA::GetFlag::DATA_READY();
}