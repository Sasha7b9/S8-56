#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Include/PageFunction.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageOperations;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnPress_Rename()
{

}

DEF_BUTTON( bRename,                                                                                                    //--- ������� - ����������� - �������� - �������� - ������������� ---
    "�������������", "Rename",
    "",
    "",
    pageOperations, FuncActive, OnPress_Rename, FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Copy()
{

}

DEF_BUTTON( bCopy,                                                                                                         //--- ������� - ����������� - �������� - �������� - ���������� ---
    "����������", "Copy",
    "",
    "",
    pageOperations, FuncActive, OnPress_Copy, FuncDraw
)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_2( pageOperations,                                                                                                             //--- ������� - ����������� - �������� - �������� ---
    "��������", "OPERATIONS",
    "",
    "",
    &bRename,   ///< ������� - ����������� - �������� - �������� - �������������
    &bCopy,     ///< ������� - ����������� - �������� - �������� - ����������
    Page::Name::Function_Recorder_Show_Operations, PageFunction::PageRecorder::PageShow::pointer, FuncActive, EmptyPressPage, FuncDrawPage, FuncRegSetPage
)

const PageBase *PageFunction::PageRecorder::PageShow::PageOperations::pointer = &pageOperations;
