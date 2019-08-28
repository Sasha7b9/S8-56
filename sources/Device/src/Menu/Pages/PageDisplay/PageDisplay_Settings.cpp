#include "defines.h"
#include "Menu/pages/Include/PageDisplay.h"
#include "Menu/MenuItems.h"
#include "Settings/Settings.h"
#include "Display/Painter.h"


extern const Page pageSettings;

const Page * const PageDisplay::PageSettings::self = (const Page *)&pageSettings;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnChanged_Settings_Brightness()
{
}

DEF_GOVERNOR( gBrightness,                                                                                                                            //--- ������� - ��������� - ������� ---
    "�������",
    "��������� ������� �������� �������",
    BRIGHTNESS_DISPLAY, 0, 100, &PageDisplay::PageSettings::self, E_BtV, OnChanged_Settings_Brightness
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_Settings_AutoHide(bool autoHide)
{
    Menu::SetAutoHide(autoHide);
}

DEF_CHOICE_6( cAutoHide,                                                                                                                             //--- ������� - ��������� - �������� ---
    "��������",
    "��������� ����� ���������� ������� ������ ��� �������� �����, �� ��������� �������� ���� ������������� ��������� � ������",
    "�������",
    "����� 5 ���",
    "����� 10 ���",
    "����� 15 ���",
    "����� 30 ���",
    "����� 60 ���",
    MENU_AUTO_HIDE, &PageDisplay::PageSettings::self, E_BtV, OnChanged_Settings_AutoHide, E_VII
)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_3( pageSettings, // -V641 // -V1027                                                                                                                    //--- ������� - ��������� ---
    "���������",
    "�������������� ��������� �������",
    PageDisplay::PageSettings::PageColors::self,        ///< ������� - ��������� - �����
    &gBrightness,                                       ///< ������� - ��������� - �������
    &cAutoHide,                                         ///< ������� - ��������� - ��������
    PageName::Display_Settings, &PageDisplay::self, E_BtV, E_VB, E_VV, E_BfKE
)
