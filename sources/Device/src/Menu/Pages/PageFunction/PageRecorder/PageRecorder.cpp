#include "defines.h"
#include "Menu/Pages/Include/PageFunction.h"
#include "Settings/Settings.h"
#include "Recorder/Recorder.h"
#include "Device.h"


extern const Page pageRecorder;

const Page * const PageRecorder::self = (const Page *)&pageRecorder;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DEF_CHOICE_2( cShow,                                                                                                                                 //--- ������� - ����������� - ������ ---
//    "����������",
//    "��������� �������� ������ ������������ ��� ����������� ���� �����������",
//    "� ������",
//    "������",
//    RECORDER_VIEW_ALLWAYS, &PageRecorder::self, 0, 0, 0
//)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnOpenClose_Recorder(bool enter)
{
    Device::State::SetMode(enter ? Device::Mode::Recorder : Device::Mode::Osci);
}


DEF_PAGE_2( pageRecorder, // -V641 // -V1027                                                                                                                  //--- ������� - ����������� ---
    "�����������",
    "������ � ��������������� �������� ������ � ��������",
    //&cShow,                                             ///< ������� - ����������� - ����������
    PageRecorder::PageSource::self,    ///< ������� - ����������� - ��������
    //PageRecorder::PageRecord::self,    ///< ������� - ����������� - ������
    PageRecorder::PageShow::self,      ///< ������� - ����������� - ��������
    PageName::Function_Recorder, &PageFunction::self, E_BtV, OnOpenClose_Recorder, E_VV, E_BfKE
)
