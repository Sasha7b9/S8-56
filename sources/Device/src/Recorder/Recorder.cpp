#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Osci/Osci_Settings.h"
#include "Recorder/Recorder.h"
#include "Recorder/Recorder_Settings.h"

#include "FPGA/FPGA_HAL.h"
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
    FPGA::HAL::Interrupt::P2P::Enable();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Recorder::DeInit()
{
    FPGA::HAL::Interrupt::P2P::Disable();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Recorder::Update()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void ReadPoint()
{

}
