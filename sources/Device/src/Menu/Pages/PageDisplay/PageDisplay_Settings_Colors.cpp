#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Menu/Pages/Include/PageDisplay.h"
#include "Menu/MenuItems.h"
#include "Settings/Settings.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageColors;

const PageBase *PageDisplay::PageSettings::PageColors::pointer = &pageColors;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnPress_ResetColors()
{
}

DEF_BUTTON( bReset,                                                                                                                          //--- ������� - ��������� - ����� - �������� ---
    "��������", "Reset",
    "����� ���� ������ �� �������� �� ���������",
    "Reset all colors to default values",
    pageColors, EmptyFuncBtV, OnPress_ResetColors, EmptyFuncVII
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cScheme,                                                                                                                 //--- ������� - ��������� - ����� - �������� ����� ---
    "���� �����", "Color scheme",
    "��������� �������� �����",
    "Changing the color scheme",
    "����� 1", "Scheme 1",
    "����� 2", "Scheme 2",
    set.serv_colorScheme, pageColors, FuncActive, Choice::EmptyChange, FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ColorType PageDisplay::PageSettings::PageColors::colorTypeA = COLOR_TYPE(0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, Color::Channel(Chan::A))

DEF_GOVERNOR_COLOR( gcChannelA,                                                                                                               //--- ������� - ��������� - ����� - ����� 1 ---
    "����� 1", "Chan 1",
    "����� ����� ������ 1",
    "Choice of channel 1 color",
    PageDisplay::PageSettings::PageColors::colorTypeA, pageColors
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ColorType PageDisplay::PageSettings::PageColors::colorTypeB = COLOR_TYPE(0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, Color::Channel(Chan::B))

DEF_GOVERNOR_COLOR( gcChannelB,                                                                                                               //--- ������� - ��������� - ����� - ����� 2 ---
    "����� 2", "Chan 2",
    "����� ����� ������ 1",
    "Choice of channel 2 color",
    PageDisplay::PageSettings::PageColors::colorTypeB, pageColors
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ColorType PageDisplay::PageSettings::PageColors::colorTypeGrid = COLOR_TYPE(0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, Color::GRID)

DEF_GOVERNOR_COLOR( gcGrid,                                                                                                                     //--- ������� - ��������� - ����� - ����� ---
    "�����", "Grid",
    "������������� ���� �����",
    "Sets the grid color",
    PageDisplay::PageSettings::PageColors::colorTypeGrid, pageColors
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_Settings_Colors_Background(bool)
{
    Color::InitGlobalColors();

    gcChannelA.ct->color = Color::Channel(Chan::A);
    gcChannelB.ct->color = Color::Channel(Chan::B);
    gcGrid.ct->color = Color::GRID;

    gcChannelA.ct->ReInit();
    gcChannelB.ct->ReInit();
    gcGrid.ct->ReInit();
}

DEF_CHOICE_2( cBackground,                                                                                                                        //--- ������� - ��������� - ����� - ��� ---
    "���", "Background",
    "����� ����� ����",
    "Choice of color of a background",
    "׸����", "Black",
    "�����", "White",
    BACKGROUND, pageColors, FuncActive, OnChanged_Settings_Colors_Background, FuncDraw
)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PageDisplay::PageSettings::PageColors::Init()
{
    OnChanged_Settings_Colors_Background(true);
}


/// \todo �������� �������������� ����� 1-�� � 2-�� �������
DEF_PAGE_6( pageColors, // -V641 // -V1027                                                                                                              //--- ������� - ��������� - ����� ---
    "�����", "COLORS",
    "����� ������ �������",
    "The choice of colors display",
    &bReset,              ///< ������� - ��������� - ����� - ��������
    &cScheme,             ///< ������� - ��������� - ����� - �������� �����
    &gcChannelA,          ///< ������� - ��������� - ����� - ����� 1
    &gcChannelB,          ///< ������� - ��������� - ����� - ����� 2
    &gcGrid,              ///< ������� - ��������� - ����� - �����
    &cBackground,         ///< ������� - ��������� - ����� - ���
    Page::Name::Display_Settings_Colors, PageDisplay::PageSettings::pointer, FuncActive, FuncPressPage, FuncDrawPage, FuncRegSetPage
)
