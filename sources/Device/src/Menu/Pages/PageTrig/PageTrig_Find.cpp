#include "defines.h"
#include "FPGA/FPGA_Settings.h"
#include "Menu/Pages/Include/PageTrig.h"
#include "Settings/Settings.h"


using namespace Osci::Settings;


extern const PageBase pageFind;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PageBase *PageTrig::PageFind::pointer = &pageFind;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char *hintsSearch_Mode[] = { "������", "Hand", "��������������",  "Auto" };

static const ChoiceBase cMode =                                                                                                                               //--- ����� - ����� - ����� ---
{
    Control::Type::Choice, 2, false, Page::Name::NoPage, &pageFind, 0,
    {
        "�����"
        ,
        "����� ������ ��������������� ������ �������������:\n"
        "1. \"������\" - ����� ������������ �� ������� ������ \"�����\" ��� �� ��������� � ������� 0.5� ������ �����, ���� ����������� "
        "\"������\x99��� ���� �����\x99�����������\".\n"
        "2. \"��������������\" - ����� ������������ �������������."
    },
    (int8 *)&TRIG_MODE_FIND, // -V206
    hintsSearch_Mode, 0, 0
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Search()
{
    Osci::Settings::Trig::Level::Find();
}

DEF_BUTTON( bSearch,                                                                                                                                          //--- ����� - ����� - ����� ---
    "�����",
    "���������� ����� ������ �������������.",
    pageFind, 0, OnPress_Search, 0
)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_2( pageFind, // -V641 // -V1027                                                                                                                              //--- ����� - ����� ---
    "�����",
    "���������� �������������� ������� ������ �������������.",
    &cMode,                         ///< ����� - ����� - �����
    &bSearch,                       ///< ����� - ����� - �����
    Page::Name::Trig_Search, PageTrig::pointer, 0, Page::FuncPress, Page::FuncDraw, FuncRegSetPage
)
