#include "defines.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Include/PageRecorder.h"



static void OnPress_Rename()
{

}

DEF_BUTTON( bRename,                                                                                                    //--- ������� - ����������� - �������� - �������� - ������������� ---
    "�������������",
    "",
    &PageRecorder::PageShow::PageOperations::self, Item::Active, OnPress_Rename
)


static void OnPress_Copy()
{

}

DEF_BUTTON( bCopy,                                                                                                         //--- ������� - ����������� - �������� - �������� - ���������� ---
    "����������",
    "",
    &PageRecorder::PageShow::PageOperations::self, Item::Active, OnPress_Copy
)


static void OnPress_Move()
{

}

DEF_BUTTON( bMove,                                                                                                        //--- ������� - ����������� - �������� - �������� - ����������� ---
    "�����������",
    "",
    &PageRecorder::PageShow::PageOperations::self, Item::Active, OnPress_Move
)


static void OnPress_Delete()
{

}

DEF_BUTTON( bDelete,                                                                                                          //--- ������� - ����������� - �������� - �������� - ������� ---
    "�������",
    "",
    &PageRecorder::PageShow::PageOperations::self, Item::Active, OnPress_Delete
)


DEF_PAGE_4( pOperations, // -V641 // -V1027                                                                                             //--- ������� - ����������� - �������� - �������� ---
    "��������",
    "",
    &bRename,   ///< ������� - ����������� - �������� - �������� - �������������
    &bCopy,     ///< ������� - ����������� - �������� - �������� - ����������
    &bMove,     ///< ������� - ����������� - �������� - �������� - �����������
    &bDelete,   ///< ������� - ����������� - �������� - �������� - �������
    PageName::Function_Recorder_Show_Operations, &PageRecorder::PageShow::self, Item::Active, Page::Changed, Page::BeforeDraw, E_BfKE
)

const Page * const PageRecorder::PageShow::PageOperations::self = (const Page *)&pOperations;
