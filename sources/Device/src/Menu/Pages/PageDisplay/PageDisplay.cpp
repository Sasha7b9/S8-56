#include "defines.h"
#include "Menu/Pages/Include/PageDisplay.h"
#include "Osci/Osci.h"
#include "Settings/Settings.h"


MenuAutoHide::E &MenuAutoHide::Ref()
{
    return set.disp.menuAutoHide;
}


void ENumAverage::Set(ENumAverage::E v)
{
    set.disp.enumAverage = v;
    AveragerOsci::SettingChanged();
}


int ENumAverage::Number()
{
    return (1 << set.disp.enumAverage);
}

int ENumAccum::Number()
{
    return (1 << set.disp.enumAccum);
};


DEF_CHOICE_10( cSmoothing,                                                                                                                                    //--- ������� - ����������� ---
    "�����.",
    "������������� ���������� ����� ��� ������� ����������� �� �������� ������ �������.",
    DISABLE_RU,
    "2 �����",
    "3 �����",
    "4 �����",
    "5 �����",
    "6 �����",
    "7 �����",
    "8 �����",
    "9 �����",
    "10 �����",
    set.disp.enumSmoothing, &PageDisplay::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


DEF_CHOICE_5( cRefreshFPS,                                                                                                                                 //--- ������� - ������� ������ ---
    "������� ������",
    "����� ������������ ����� ��������� � ������� ������.",
    "25",
    "10",
    "5",
    "2",
    "1",
    set.disp.enumSignalsInSec, &PageDisplay::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


DEF_CHOICE_4( cType, // -V206                                                                                                                                       //--- ������� - ����� ---
    "�����",
    "����� ���� �����",
    "��� 1",
    "��� 2",
    "��� 3",
    "��� 4",
    set.disp.typeGrid, &PageDisplay::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


static void OnChange_AverageNum(bool)
{
    AveragerOsci::SettingChanged();
}

DEF_CHOICE_9( cAverage_Num,                                                                                                                       //--- ������� - ���������� - ���������� ---
    "����������",
    "����� ���������� ��������� ���������, �� ������� ������������ ����������.",
    DISABLE_RU,
    "2",
    "4",
    "8",
    "16",
    "32",
    "64",
    "128",
    "256",
    set.disp.enumAverage, &PageDisplay::self, Item::Active, OnChange_AverageNum, Choice::AfterDraw
)


DEF_CHOICE_2( cViewMode,                                                                                                                                      //--- ������� - ����������� ---
    "�������",
    "����� ����� ����������� �������",
    "������",
    "�����",
    set.disp.mapping, &PageDisplay::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


DEF_PAGE_7( pDisplay,                                                                                                                                                       //--- ������� ---
    "�������",
    "�������� ��������� ����������� �������.",
    &cViewMode,
    PageDisplay::Accumulation::self,
    &cAverage_Num,
    &cSmoothing,
    &cType,
    &cRefreshFPS,
    PageDisplay::Settings::self,
    PageName::Display, nullptr, Item::Active, Page::NormalTitle, Page::OpenClose, Page::BeforeDraw, Page::HandlerKeyEvent
)

const Page * const PageDisplay::self = static_cast<const Page *>(&pDisplay);
