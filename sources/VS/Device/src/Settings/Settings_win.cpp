#include "defines.h"
#include "Settings/Settings.h"
#include "Hardware/Memory.h"
#include "FPGA/FPGA.h"
#include "Osci/Osci.h"



void Settings::Load(bool)
{
    set = Settings::defaultSettings;
}


void Settings::Save()
{
}
