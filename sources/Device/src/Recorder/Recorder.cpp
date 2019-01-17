#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Osci/Osci_Settings.h"
#include "Recorder/Recorder.h"
#include "Recorder/Recorder_Settings.h"

#include "FPGA/FPGA_HAL.h"
#include "Hardware/FSMC.h"
#include "FPGA/FPGA_Types.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������ ����� �� ���������� �� FPGA
static void ReadPoint();


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Recorder::Init()
{
    Osci::Settings::Range::LoadBoth();
    Osci::Settings::RShift::Load(Chan::A);
    Osci::Settings::RShift::Load(Chan::B);
    Osci::Settings::Trig::Input::Load();
    Settings::ScaleX::Load();
    Osci::Settings::TShift::Load();
    Osci::Settings::LoadHoldfOff();

    FPGA::HAL::Interrupt::P2P::Init(ReadPoint);

    Stop();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Recorder::DeInit()
{
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Recorder::Update()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void ReadPoint()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Recorder::Start()
{
    FSMC::WriteToFPGA16(WR_PRED_LO, 0);
    FSMC::WriteToFPGA16(WR_POST_LO, 0);
    FSMC::WriteToFPGA8(WR_START, 0xff);

    FPGA::HAL::Interrupt::P2P::Enable();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Recorder::Stop()
{
    FPGA::HAL::Interrupt::P2P::Disable();
}
