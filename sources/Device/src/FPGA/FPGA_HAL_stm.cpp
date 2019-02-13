#include "defines.h"
#include "FPGA/FPGA_HAL.h"
#include "Hardware/HAL/HAL.h"
#include "Osci/Osci_Settings.h"
#include "Osci/FrequencyCounter.h"


using namespace HAL::ADDRESSES::FPGA;
using namespace Osci::Settings;


using HAL::FSMC;


extern bool givingStart;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FPGA::HAL::ReadFlag()
{
    flag = (uint16)(FSMC::ReadFromFPGA(RD::FLAG_LO) | (FSMC::ReadFromFPGA(RD::FLAG_HI) << 8));

    if (GetFlag::TRIG_READY() && !givingStart)
    {
        Trig::pulse = true;
    }

    FrequencyCounter::Update();
}
