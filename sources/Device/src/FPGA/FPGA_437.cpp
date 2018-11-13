#include "defines.h"
#include "FPGA.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FPGA::LoadSettings()
{
    LoadRanges();
    LoadRShift(Chan::A);
    LoadRShift(Chan::B);
    LoadTrigSourceInput();
    LoadTrigLev();
    LoadTBase();
    LoadTShift();

    isRunning = false;
}
