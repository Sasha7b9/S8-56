#include "defines.h"
#include "Menu/Pages/Include/PageMemory.h"
#include "Menu/Pages/Include/PageTime.h"
#include "FPGA/FPGA.h"
#include "FPGA/FPGA_Settings.h"
#include "Menu/MenuItems.h"
#include "Utils/CommonFunctions.h"
#include "Settings/Settings.h"
#include "Osci/Osci.h"


using namespace Osci::Settings;


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool IsActive_Sample()
{
    return Osci::InModeRandomizer() && !START_MODE_IS_SINGLE;
}

DEF_CHOICE_2( cSample,                                                                                                                                          //--- ��������� - ������� ---
    "�������"
    ,
    "\"��������\" - \n"
    "\"�������������\" -"
    ,
    "�������� �����",
    "�������������",
    SAMPLE_TYPE, &PageTime::self, IsActive_Sample, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool IsActive_PeakDet()
{
    return (SET_TBASE >= TBase::MIN_PEAK_DET);
}

void PageTime::OnChanged_PeakDet(bool active)
{
    if (active)
    {
        Osci::OnChangedPoints();
    }
    else
    {
        Display::ShowWarning(Warning::TooSmallSweepForPeakDet);
    }
}

DEF_CHOICE_2( cPeakDet,                                                                                                                                         //--- ��������� - ��� ��� ---
    "��� ���",
    "��������/��������� ������� ��������."
    ,
    DISABLE_RU,
    ENABLE_RU,
    SET_PEAKDET, &PageTime::self, IsActive_PeakDet, PageTime::OnChanged_PeakDet, E_VII
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PageTime::OnChanged_TPos(bool active)
{
    PageMemory::OnChanged_Points(active);
    TShift::Set(SET_TSHIFT);
}

DEF_CHOICE_3( cTPos,                                                                                                                                                 //--- ��������� - �� ---
    "\x7b",
    "����� ����� �������� �������� �������� �� ������� � ������ - ����� ����, �����, ������ ����."
    ,
    "����",
    "�����",
    "�����",
    TPOS, &PageTime::self, E_BtV, PageTime::OnChanged_TPos, E_VII
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//DEF_CHOICE_2(cDivRole,                                                                                       //--- ��������� - �-��� ��/��� ---
//    "�-��� ��/���"
//    ,
//    "����� ������� ��� ����� �����/���: � ������ ����� ���������� (����/���� � ��������� ����):\n"
//    "1. \"�����\" - ��������� �������� �� �������.\n"
//    "2. \"������\" - ����������� �� ������."
//    ,
//    "�����",
//    "������",
//    TIME_DIV_XPOS, PageTime::self, 0, 0, 0
//)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cShiftXtype,                                                                                                                                     //--- ��������� - �������� ---
    "��������",
    "����� ����� ��������� �������� �� �����������\n1. \"�����\" - ����������� ���������� �������� � ��������.\n2. \"�������\" - ����������� ��������� ������� �� ������."
    ,
    "�����",
    "�������",
    LINKING_TSHIFT, &PageTime::self, E_BtV, E_VB, E_VII
)

DEF_PAGE_4( pTime, // -V641 // -V1027                                                                                                                                     //--- ��������� ---
    "����",
    "�������� ��������� ��������",
    &cSample,           ///< ��������� - �������
    &cPeakDet,          ///< ��������� - ��� ���
    &cTPos,             ///< ��������� - ��
    //&cDivRole,          ///< ��������� - �-��� ��/���
    &cShiftXtype,       ///< ��������� - ��������
    PageName::Time, nullptr, E_BtV, E_VB, E_VV, E_BfKE
)

const Page * const PageTime::self = (const Page *)&pTime;
