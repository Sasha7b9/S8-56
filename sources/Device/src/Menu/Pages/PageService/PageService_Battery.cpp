#include "defines.h"
#include "Hardware/Battery.h"
#include "Menu/Pages/Include/PageService.h"
#include "Settings/Settings.h"


extern const Page pageBattery;

const Page * const PageService::PageBattery::self = (const Page *)&pageBattery;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2( cShow,                                                                                                                                  //--- ������ - ������� - ���������� ---  
    "����������",
    "��������/��������� ����� ����������� � ���������� ������� �� �����",
    DISABLE_RU,
    ENABLE_RU,
    BAT_SHOW_ON_DISPLAY, &PageService::PageBattery::self, E_BtV, E_VB, E_VII
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_1( pageBattery, // -V641 // -V1027                                                                                                                        //--- ������ - ������� ---
    "�������",
    "������� ������ � ��������������",
    &cShow,                     ///< ������ - ������� - ����������
    PageName::Service_Battery, &PageService::self, E_BtV, E_VB, E_VV, E_BfKE
)
