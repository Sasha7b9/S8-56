#include "defines.h"
#include "Menu/pages/Include/PageDisplay.h"
#include "Menu/MenuItems.h"
#include "Settings/Settings.h"
#include "Display/Painter.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageSettings;

const PageBase *PageDisplay::PageSettings::pointer = &pageSettings;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnChanged_Settings_Brightness()
{
}

DEF_GOVERNOR( gBrightness,                                                                                                                            //--- ������� - ��������� - ������� ---
    "�������",
    "��������� ������� �������� �������",
    BRIGHTNESS_DISPLAY, 0, 100, pageSettings, FuncActive, OnChanged_Settings_Brightness, FuncBeforeDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_GOVERNOR( gLevels,                                                                                                                                 //--- ������� - ��������� - ������ ---
    "������",
    "����� �����, � ������� �������� ����� �������� ����� ������� ���������� �� ������ ������� ��������������� ����� ������ ��������",
    TIME_SHOW_LEVELS, 0, 125, pageSettings, FuncActive, FuncChanged, FuncBeforeDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_GOVERNOR( gTime,                                                                                                                                    //--- ������� - ��������� - ����� ---
    "�����",
    "��������� �������, � ������� �������� ��������� ����� ���������� �� ������",
    TIME_MESSAGES, 1, 99, pageSettings, FuncActive, FuncChanged, FuncBeforeDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_3( cStringNavigation,                                                                                                                  //--- ������� - ��������� - ������ ���� ---
    "������ ����",
    "��� ������ \n����������\n ����� ������ ������ ��������� ������ ���� �� ������� �������� ����",
    "��������",
    "������",
    "�������",
    SHOW_STRING_NAVI, pageSettings, FuncActive, Choice::FuncChange, Choice::FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_Settings_AltMarkers(bool active)
{
    Display::ChangedRShiftMarkers(active);
}

DEF_CHOICE_3( cAltMarkers,                                                                                                                       //--- ������� - ��������� - ���. ������� ---
    "���. �������",
    "������������� ����� ����������� �������������� �������� ������� �������� � �������������:\n"
    "\"��������\" - �������������� ������� �� ������������,\n"
    "\"����������\" - �������������� ������� ������������ ������,\n"
    "\"����\" - �������������� ������� ������������ � ������� 5 ��� ����� �������� ����� �������� ������ �� ���������� ��� ������ �������������"
    ,
    "��������",
    "����������",
    "����",
    ALT_MARKERS, pageSettings, FuncActive, OnChanged_Settings_AltMarkers, Choice::FuncDraw
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
    MENU_AUTO_HIDE, pageSettings, FuncActive, OnChanged_Settings_AutoHide, Choice::FuncDraw
)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_7( pageSettings, // -V641 // -V1027                                                                                                                    //--- ������� - ��������� ---
    "���������",
    "�������������� ��������� �������",
    PageDisplay::PageSettings::PageColors::pointer,     ///< ������� - ��������� - �����
    &gBrightness,                                       ///< ������� - ��������� - �������
    &gLevels,                                           ///< ������� - ��������� - ������
    &gTime,                                             ///< ������� - ��������� - �����
    &cStringNavigation,                                 ///< ������� - ��������� - ������ ����
    &cAltMarkers,                                       ///< ������� - ��������� - ���. �������
    &cAutoHide,                                         ///< ������� - ��������� - ��������
    Page::Name::Display_Settings, PageDisplay::pointer, FuncActive, FuncPressPage, Page::FuncDraw, FuncRegSetPage
)
