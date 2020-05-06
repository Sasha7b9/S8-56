#include "defines.h"
#include "Menu/Pages/Include/PageMemory.h"
#include "Settings/Settings.h"


DEF_CHOICE_2(cSaveAs,                                                                                                                             //--- ������ - ����� �� - ��������� ��� ---
    "��������� ���"
    ,
    "���� ������ ������� \"�����������\", ������ ����� �������� � ������� �������� � ����������� ����� � ����������� BMP\n"
    "���� ������ ������� \"�����\", ������ ����� �������� � ������� �������� � ��������� ���� � ����� � ���������� TXT"
    ,
    "�����������",
    "�����",
    S_MEM_MODE_SAVE_SIGNAL, &PageDrive::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


DEF_CHOICE_2(cName,                                                                                                                                   //--- ������ - ����� �� - ��� ����� ---
    "��� �����"
    ,
    "����� ����� ������������ ������ ��� ���������� �� ������� ����������:\n"
    "\"�� �����\" - ����� ��������� ������������� �� ������� �������� ����� (����. ����� ����),\n"
    "\"�������\" - ������ ��� ��� ����� ����� �������� �������"
    ,
    "�� �����",
    "�������",
    S_MEM_FILE_NAMING_MODE, &PageDrive::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


DEF_CHOICE_2(cModeBtnMemory,                                                                                                                      //--- ������ - ����� �� - ��� �� ������ ---
    "��� �� ������",
    "",
    "����",
    "����������",
    S_MEM_MODE_BTN_MEMORY, &PageDrive::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


DEF_CHOICE_2(cAutoconnect,                                                                                                                      //--- ������ - ����� �� - ��������������� ---
    "���������.",
    "E��� \"���\", ��� ����������� �������� ���������� ���������� �������������� ������� �� �������� ������ - ����� ��",
    DISABLE_RU,
    ENABLE_RU,
    S_MEM_FLASH_AUTO_CONNECT, &PageDrive::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


DEF_PAGE_6(pDrive,   //-V1027                                                                                                                                     //--- ������ - ����� �� ---
    "����� ��",
    "������ � ������� ������������ �����������.",
    PageDrive::Manager::self,
    &cName,
    PageDrive::Mask::self,
    &cSaveAs,
    &cModeBtnMemory,
    &cAutoconnect,
    PageName::Memory_Drive,
    &PageMemory::self, Item::Active, Page::NormalTitle, Page::OpenClose, Page::BeforeDraw, Page::HandlerKeyEvent
)

const Page *const PageDrive::self = static_cast<const Page *>(&pDrive);
