#include "defines.h"
#include "Menu/pages/Include/PageDisplay.h"
#include "Menu/MenuItems.h"
#include "Settings/Settings.h"
#include "Display/Painter.h"


extern const PageDef pageSettings;

const Page * const PageDisplay::PageSettings::self = (const Page *)&pageSettings;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnChanged_Settings_Brightness()
{
}

DEF_GOVERNOR( gBrightness,                                                                                                                            //--- ������� - ��������� - ������� ---
    "�������",
    "��������� ������� �������� �������",
    BRIGHTNESS_DISPLAY, 0, 100, &PageDisplay::PageSettings::self, 0, OnChanged_Settings_Brightness, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_GOVERNOR( gTime,                                                                                                                                    //--- ������� - ��������� - ����� ---
    "�����",
    "��������� �������, � ������� �������� ��������� ����� ���������� �� ������",
    TIME_MESSAGES, 1, 99, &PageDisplay::PageSettings::self, 0, 0, 0
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
    MENU_AUTO_HIDE, &PageDisplay::PageSettings::self, 0, OnChanged_Settings_AutoHide, 0
)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_4( pageSettings, // -V641 // -V1027                                                                                                                    //--- ������� - ��������� ---
    "���������",
    "�������������� ��������� �������",
    PageDisplay::PageSettings::PageColors::self,     ///< ������� - ��������� - �����
    &gBrightness,                                       ///< ������� - ��������� - �������
    &gTime,                                             ///< ������� - ��������� - �����
    &cAutoHide,                                         ///< ������� - ��������� - ��������
    Page::Name::Display_Settings, &PageDisplay::self, 0, 0, 0, 0
)
