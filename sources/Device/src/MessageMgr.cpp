#include "defines.h"
#include "MessageMgr.h"
#include "Osci/Osci_Averager.h"



void MessageMgr::OsciSettingsEffectOnAverageChanged()
{
    Osci::Averager::SettingChanged();
}
