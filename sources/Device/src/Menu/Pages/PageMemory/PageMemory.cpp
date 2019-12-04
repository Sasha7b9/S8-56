#include "defines.h"
#include "Tables.h"
#include "Display/Grid.h"
#include "Display/Primitives.h"
#include "Display/Symbols.h"
#include "FlashDrive/FileManager.h"
#include "FlashDrive/FlashDrive.h"
#include "Hardware/Beeper.h"
#include "Osci/Osci.h"
#include "Settings/Settings.h"
#include "Utils/Math.h"


bool ModeWork::IsRAM()
{
    return (set.mem.modeWork == ModeWork::RAM);
}


bool ModeWork::IsDir()
{
    return (set.mem.modeWork == ModeWork::Dir);
}


static void DrawSetMask();  // ��� ������� ������, ����� ������ ����� ������� �����.
static void DrawFileMask(int x, int y);
static void DrawSetName();  // ��� ������� ������, ����� ����� ������ ��� ����� ��� ����������
       void OnMemExtSetMaskNameRegSet(int angle, int maxIndex);



static bool IsActive_Points()
{
    return !PeakDetMode().IsEnabled();
}

void PageMemory::OnChanged_Points(bool active)
{
    // ���� ������� ������� ��������, �� �� ����� ����������� ������
    if (PeakDetMode().IsEnabled() && !active)
    {
        Display::ShowWarning("����� �������� ����� ������, ��������� ������� ��������");
        return;
    }

    Osci::OnChangedPoints();
}

static pString namesLengthMemory[] = {"512", "1k", "2k", "4k", "8k", "16k", "32k"};

DEF_CHOICE_5( cPoints,                                                                                                                                               //--- ������ - ����� ---
    "����� ������",
    "����� ���������� �������� ��� ����������� ��������. ��� ���������� ���������� �������� ����������� ���������� ����������� � ������ ��������.",
    namesLengthMemory[0],
    namesLengthMemory[1],
    namesLengthMemory[2],
    namesLengthMemory[3],
    namesLengthMemory[4],
    set.mem.enumPoints, &PageMemory::self, IsActive_Points, PageMemory::OnChanged_Points, Choice::AfterDraw
)


static void Draw_Manager_Tab(int x, int y)
{
    Char(SymbolUGO2::TAB).Draw4SymbolsInRect(x + 2, y + 1);
}

DEF_GRAPH_BUTTON( bManager_Tab,                                                                                                                   //--- ������ - ����� �� - ������� - Tab ---
    "Tab",
    "������� ����� ���������� � �������",
    &PageDrive::PageManager::self, Item::Active, FileManager::Press_Tab, Draw_Manager_Tab
)


static void Draw_Manager_LevelUp(int x, int y)
{
    Char(SymbolUGO2::LEAVE).Draw4SymbolsInRect(x + 2, y + 1);
}

DEF_GRAPH_BUTTON( bManager_LevelUp,                                                                                                 //--- ������ - ����� �� - ������� - ����� �� �������� ---
    "����� �� ��������",
    "������� � ������������ �������",
    &PageDrive::PageManager::self, Item::Active, FileManager::Press_LevelUp, Draw_Manager_LevelUp
)


static void Draw_Manager_LevelDown(int x, int y)
{
    Char(SymbolUGO2::ENTER).Draw4SymbolsInRect(x + 2, y + 2);
}

DEF_GRAPH_BUTTON( bManager_LevelDown,                                                                                                 //--- ������ - ����� �� - ������� - ����� � ������� ---
    "����� � �������",
    "������� � ��������� �������",
    &PageDrive::PageManager::self, Item::Active, FileManager::Press_LevelDown, Draw_Manager_LevelDown
)


static bool IsActive_Drive_Manager()
{
    return FDrive::IsConnected();
}

void PageMemory::OnOpenClose_Drive_Manager(bool)
{
    if (FDrive::IsConnected())
    {
        FDrive::Mount();
        Display::SetDrawMode(DrawMode::Auto, FileManager::Draw);
        FM_NEED_REDRAW = FM_REDRAW_FULL;
    }
    else
    {
        Display::ShowWarning("������� ���������� ����-����");
    }
}

DEF_PAGE_3( pManager,                                                                                                                                   //--- ������ - ����� �� - ������� ---
    "�������",
    "��������� ������ � �������� ������� ������������� ����������",
    &bManager_Tab,
    &bManager_LevelUp,
    &bManager_LevelDown,
    PageName::Memory_Drive_Manager,
    &PageDrive::self, IsActive_Drive_Manager, Page::NormalTitle, PageMemory::OnOpenClose_Drive_Manager, Page::BeforeDraw, FileManager::HandlerKey
)

const Page * const PageDrive::PageManager::self = static_cast<const Page *>(&pManager);


DEF_CHOICE_2( cDrive_Name,                                                                                                                            //--- ������ - ����� �� - ��� ����� ---
    "��� �����"
    ,
    "����� ����� ������������ ������ ��� ���������� �� ������� ����������:\n"
    "\"�� �����\" - ����� ��������� ������������� �� ������� �������� ����� (����. ����� ����),\n"
    "\"�������\" - ������ ��� ��� ����� ����� �������� �������"
    ,
    "�� �����",
    "�������",
    set.mem.fileNamingMode, &PageDrive::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


static void OnPress_Mask_Delete()
{
    set.mem.fileNameMask[0] = '\0';
}

static void Draw_Delete(int x, int y)
{
    Char(SymbolUGO2::DELETE).Draw4SymbolsInRect(x + 2, y + 1);
}

DEF_GRAPH_BUTTON( bMask_Delete,                                                                                                                 //--- ������ - ����� �� - ����� - ������� ---
    "�������",
    "������� ��� �������� �������",
    &PageDrive::PageMask::self, Item::Active, OnPress_Mask_Delete, Draw_Delete
)


static void OnPress_Mask_Backspace()
{
    int size = static_cast<int>(std::strlen(set.mem.fileNameMask));
    if (size > 0)
    {
        if (size > 1 && set.mem.fileNameMask[size - 2] == 0x07)
        {
            set.mem.fileNameMask[size - 2] = '\0';
        }
        else
        {
            set.mem.fileNameMask[size - 1] = '\0';
        }
    }
}

static void Draw_Backspace(int x, int y)
{
    Char(SymbolUGO2::ARROW_LEFT).Draw(x + 2, y + 1);
}

DEF_GRAPH_BUTTON( bMask_Backspace,                                                                                                      //--- ������ - ����� �� - ����� - Backspace ---
    "Backspace",
    "������� ��������� �������� ������",
    &PageDrive::PageMask::self, Item::Active, OnPress_Mask_Backspace, Draw_Backspace
)


static void OnPress_Mask_Insert()
{
    int index = set.mem.indexCurSymbolNameMask;
    int size = static_cast<int>(std::strlen(set.mem.fileNameMask));
    if (size == MAX_SYMBOLS_IN_FILE_NAME - 1)
    {
        return;
    }
    if (index < 0x41)
    {
        set.mem.fileNameMask[size] = Tables::Get(index)[0];
        set.mem.fileNameMask[size + 1] = '\0';
    }
    else
    {
        index -= 0x40;
        if (index == 0x07)  // ��� %nN - ��������� ������
        {
            if (size < MAX_SYMBOLS_IN_FILE_NAME - 2 && size > 0)
            {
                if (set.mem.fileNameMask[size - 1] >= 0x30 && set.mem.fileNameMask[size - 1] <= 0x39) // ���� ����� ������� �����
                {
                    set.mem.fileNameMask[size] = set.mem.fileNameMask[size - 1] - 0x30;
                    set.mem.fileNameMask[size - 1] = 0x07;
                    set.mem.fileNameMask[size + 1] = '\0';
                }
            }
        }
        else
        {
            set.mem.fileNameMask[size] = static_cast<char>(index);
            set.mem.fileNameMask[size + 1] = '\0';
        }
    }
}

static void Draw_Insert(int x, int y)
{
    Char(SymbolUGO2::INSERT).Draw4SymbolsInRect(x + 2, y + 2);
}

DEF_GRAPH_BUTTON( bMask_Insert,                                                                                                                //--- ������ - ����� �� - ����� - �������� ---
    "��������",
    "��������� ��������� ������",
    &PageDrive::PageMask::self, Item::Active, OnPress_Mask_Insert, Draw_Insert
)


DEF_CHOICE_2( cDrive_SaveAs,                                                                                                                      //--- ������ - ����� �� - ��������� ��� ---
    "��������� ���"
    ,
    "���� ������ ������� \"�����������\", ������ ����� �������� � ������� �������� � ����������� ����� � ����������� BMP\n"
    "���� ������ ������� \"�����\", ������ ����� �������� � ������� �������� � ��������� ���� � ����� � ���������� TXT"
    ,
    "�����������",
    "�����",
    set.mem.modeSaveSignal, &PageDrive::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


DEF_CHOICE_2( cDrive_ModeBtnMemory,                                                                                                               //--- ������ - ����� �� - ��� �� ������ ---
    "��� �� ������",
    "",
    "����",
    "����������",
    set.mem.modeBtnMemory, &PageDrive::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


static bool IsActive_Mask()
{
    return (set.mem.fileNamingMode == FileNamingMode::Mask);
}

static void OnOpenClose_Mask(bool)
{
    Display::SetAddDrawFunction(DrawSetMask);
}

static void DrawSetMask()
{
    int x0 = Grid::Left() + 40;
    int y0 = Grid::Top() + 20;
    int width = Grid::Width() - 80;
    int height = 160;

    Rectangle(width, height).Draw(x0, y0, Color::FILL);
    Region(width - 2, height - 2).Fill(x0 + 1, y0 + 1, Color::BACK);

    int index = 0;
    int position = 0;
    int deltaX = 10;
    int deltaY0 = 5;
    int deltaY = 12;

    // ������ ������� ����� ����������� ��������
    while (Tables::Get(index)[0] != ' ')
    {
        Tables::DrawStr(index, x0 + deltaX + position * 7, y0 + deltaY0);
        index++;
        position++;
    }

    // ������ ������ ����� � ������
    position = 0;
    while (Tables::Get(index)[0] != 'a')
    {
        Tables::DrawStr(index, x0 + deltaX + 50 + position * 7, y0 + deltaY0 + deltaY);
        index++;
        position++;
    }

    // ������ ������ ����� ����� ��������
    position = 0;
    while (Tables::Get(index)[0] != '%')
    {
        Tables::DrawStr(index, x0 + deltaX + position * 7, y0 + deltaY0 + deltaY * 2);
        index++;
        position++;
    }

    // ������ ������ �����������
    position = 0;
    while (index < (Tables::Size() / 4))
    {
        Tables::DrawStr(index, x0 + deltaX + 26 + position * 20, y0 + deltaY0 + deltaY * 3);
        index++;
        position++;
    }

    DrawFileMask(x0 + deltaX, y0 + 65);

    static pString strings[] =
    {
        "%y - ���, %m - �����, %d - ����",
        "%H - ����, %M - ������, %S - �������",
        "%nN - ���������� �����, ���",
        "n - ����������� ���������� ������ ��� N"
    };

    deltaY--;
    Color::FILL.SetAsCurrent();
    for (int i = 0; i < static_cast<int>(sizeof(strings)) / 4; i++)
    {
        String(strings[i]).Draw(x0 + deltaX, y0 + 100 + deltaY * i);
    }
}

static void DrawFileMask(int x, int y)
{
    char *ch = set.mem.fileNameMask;

    Color::FILL.SetAsCurrent();
    while (*ch != '\0')
    {
        if (*ch >= 32)
        {
            Char(*ch).Draw(x, y);
        }
        else
        {
            if (*ch == 0x07)
            {
                x = Char('%').Draw(x, y);
                x = Char(0x30 | *(ch + 1)).Draw(x, y);
                x = Char('N').Draw(x, y);
                ch++;
            }
            else
            {
                x = String(Tables::Get(*ch + 0x40)).Draw(x, y);
            }
        }
        ch++;
    }
    Region(5, 8).Fill(x, y, Color::FLASH_10);
}

static bool HandlerKey_Mask(const KeyEvent &event)
{
    int angle = (event.IsUp() || event.IsRight()) ? 1 : -1;

    OnMemExtSetMaskNameRegSet(angle, Tables::Size() / 4);

    return true;
}


/*
DEF_PAGE_SB( pMask,                                                                                                                                       //--- ������ - ����� �� - ����� ---
    "�����", "MASK",
    "����� ����� ����� ��� ��������������� ���������� ������",
    "Input mode mask for automatic file naming",
    &bDrive_Mask_Exit,      // ������ - ����� �� - ����� - �����
    &bMask_Delete,    // ������ - ����� �� - ����� - �������
    0,
    0,
    &bMask_Backspace, // ������ - ����� �� - ����� - Backspace
    &bMask_Insert,    // ������ - ����� �� - ����� - ��������
    Page::Name::SB_Memory_Drive_Mask, &pDrive, IsActive_Mask, OnPress_Drive_Mask, FuncDrawPage, OnRegSet_Drive_Mask
)
*/


DEF_PAGE_3( pMask,                                                                                                                                        //--- ������ - ����� �� - ����� ---
    "�����",
    "����� ����� ����� ��� ��������������� ���������� ������",
    &bMask_Delete,
    &bMask_Backspace,
    &bMask_Insert,
    PageName::Memory_Drive_Mask,
    &PageDrive::self, IsActive_Mask, Page::NormalTitle, OnOpenClose_Mask, Page::BeforeDraw, HandlerKey_Mask
)

const Page * const PageDrive::PageMask::self = static_cast<const Page *>(&pMask);


DEF_CHOICE_2( cDrive_Autoconnect,                                                                                                               //--- ������ - ����� �� - ��������������� ---
    "���������.",
    "E��� \"���\", ��� ����������� �������� ���������� ���������� �������������� ������� �� �������� ������ - ����� ��",
    DISABLE_RU,
    ENABLE_RU,
    set.mem.flashAutoConnect, &PageDrive::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


       DEF_PAGE_6( pDrive,   //-V1027                                                                                                                             //--- ������ - ����� �� ---
    "����� ��",
    "������ � ������� ������������ �����������.",
    PageDrive::PageManager::self,
    &cDrive_Name,
    PageDrive::PageMask::self,
    &cDrive_SaveAs,
    &cDrive_ModeBtnMemory,
    &cDrive_Autoconnect,
    PageName::Memory_Drive,
    &PageMemory::self, Item::Active, Page::NormalTitle, Page::OpenClose, Page::BeforeDraw, Page::HandlerKeyEvent
)

const Page * const PageDrive::self = static_cast<const Page *>(&pDrive);


DEF_PAGE_4( pMemory,                                                                                                                                                         //--- ������ ---
    "������",
    "������ � ������� � ���������� �������.",
    &cPoints,
    PageRAM::self,
    PageROM::self,
    PageDrive::self,  PageName::Memory, nullptr, Item::Active, Page::NormalTitle, Page::OpenClose, Page::BeforeDraw, Page::HandlerKeyEvent
)

const Page * const PageMemory::self = static_cast<const Page *>(&pMemory);


void PageMemory::SaveSignalToFlashDrive()
{
    if (FDrive::IsConnected())
    {
        if (set.mem.fileNamingMode == FileNamingMode::Manually)
        {
            Display::SetAddDrawFunction(DrawSetName);
        }
        else
        {
            NEED_SAVE_TO_FLASHDRIVE = 1;
        }
    }
    else
    {
        EXIT_FROM_SETNAME_TO = 0;
    }
}

static void DrawSetName()
{
    int x0 = Grid::Left() + 40;
    int y0 = Grid::Top() + 60;
    int width = Grid::Width() - 80;
    int height = 80;

    Rectangle(width, height).Draw(x0, y0, Color::FILL);
    Region(width - 2, height - 2).Fill(x0 + 1, y0 + 1, Color::BACK);

    int index = 0;
    int position = 0;
    int deltaX = 10;
    int deltaY0 = 5;
    int deltaY = 12;

    // ������ ������� ����� ����������� ��������
    while (Tables::Get(index)[0] != ' ')
    {
        Tables::DrawStr(index, x0 + deltaX + position * 7, y0 + deltaY0);
        index++;
        position++;
    }

    // ������ ������ ����� � ������
    position = 0;
    while (Tables::Get(index)[0] != 'a')
    {
        Tables::DrawStr(index, x0 + deltaX + 50 + position * 7, y0 + deltaY0 + deltaY);
        index++;
        position++;
    }

    // ������ ������ ����� ����� ��������
    position = 0;
    while (Tables::Get(index)[0] != '%')
    {
        Tables::DrawStr(index, x0 + deltaX + position * 7, y0 + deltaY0 + deltaY * 2);
        index++;
        position++;
    }

    int x = String(set.mem.fileName).Draw(x0 + deltaX, y0 + 65, Color::FILL);

    Region(5, 8).Fill(x, y0 + 65, Color::FLASH_10);
}


static void OnPress_SetName_Exit()
{
    if (EXIT_FROM_SETNAME_TO == RETURN_TO_DISABLE_MENU)
    {
        //Menu::PagePointerFromName(Page::Name::SB_Memory_SetName)->ShortPressOnItem(0);
    }
    else if (EXIT_FROM_SETNAME_TO == RETURN_TO_LAST_MEM)
    {
    }
    else if (EXIT_FROM_SETNAME_TO == RETURN_TO_INT_MEM)
    {
    }
    else
    {
        //
    }

    EXIT_FROM_SETNAME_TO = RETURN_TO_DISABLE_MENU;
}


static void OnPress_SetName_Delete()
{
    set.mem.fileName[0] = '\0';
}

DEF_GRAPH_BUTTON( bSetName_Delete,                                                                                                                              //--- ��� ����� - ������� ---
    "�������",
    "������� ��� �������� �������",
    &PageSetName::self, Item::Active, OnPress_SetName_Delete, Draw_Delete
)


static void OnPress_SetName_Backspace()
{
    int size = static_cast<int>(std::strlen(set.mem.fileName));
    if (size > 0)
    {
        set.mem.fileName[size - 1] = '\0';
    }
}

DEF_GRAPH_BUTTON( bSetName_Backspace,                                                                                                                         //--- ��� ����� - Backspace ---
    "Backspace",
    "������� ��������� ������",
    &PageSetName::self, Item::Active, OnPress_SetName_Backspace, Draw_Backspace
)


static void OnPress_SetName_Insert()
{
    int size = static_cast<int>(std::strlen(set.mem.fileName));
    if (size < MAX_SYMBOLS_IN_FILE_NAME - 1)
    {
        set.mem.fileName[size] = Tables::Get(set.mem.indexCurSymbolNameMask)[0];
        set.mem.fileName[size + 1] = '\0';
    }
}

DEF_GRAPH_BUTTON( bSetName_Insert,                                                                                                                             //--- ��� ����� - �������� ---
    "��������",
    "������ ��������� ������",
    &PageSetName::self, Item::Active, OnPress_SetName_Insert, Draw_Insert
)


static void OnPress_SetName_Save()
{
    if (FDrive::IsConnected())
    {
        OnPress_SetName_Exit();
        NEED_SAVE_TO_FLASHDRIVE = 1;
    }
}

static void Draw_SetName_Save(int x, int y)
{
    if (FDrive::IsConnected())
    {
        Char(SymbolUGO2::FLASH_DRIVE_BIG).Draw4SymbolsInRect(x + 2, y + 1);
    }
}

DEF_GRAPH_BUTTON( bSetName_Save,                                                                                                                              //--- ��� ����� - ��������� ---
    "���������",
    "���������� �� ���� ��� �������� ������",
    &PageSetName::self, Item::Active, OnPress_SetName_Save, Draw_SetName_Save
)


static bool HandlerKey_SetName(const KeyEvent &event)
{
    OnMemExtSetMaskNameRegSet(event.Delta(), Tables::Size() / 4 - 7);

    return true;
}

void OnMemExtSetMaskNameRegSet(int angle, int maxIndex)
{
    typedef void (*pFuncVpI8I8I8)(int8 *, int8, int8);

    static const pFuncVpI8I8I8 func[3] =
    {
        Math::CircleDecrease<int8>,
        Math::CircleDecrease<int8>,
        Math::CircleIncrease<int8>
    };

    Color::ChangeFlash(true);

    if (set.mem.indexCurSymbolNameMask > maxIndex)
    {
        set.mem.indexCurSymbolNameMask = static_cast<int8>(maxIndex - 1);
    }
    func[Math::Sign(angle) + 1](&set.mem.indexCurSymbolNameMask, 0, static_cast<int8>(maxIndex - 1));
    Beeper::RegulatorSwitchRotate();
}

DEF_PAGE_4( pSetName,                                                                                                             //--- �������� ���������� ��� ����� ����� ����� ---
    "",
    "",
    &bSetName_Delete,
    &bSetName_Backspace,
    &bSetName_Insert,
    &bSetName_Save,
    PageName::Memory_SetName, nullptr, Item::Active, Page::NormalTitle, Page::OpenClose, Page::BeforeDraw, HandlerKey_SetName
)

const Page * const PageSetName::self = static_cast<const Page *>(&pSetName);


ENumPointsFPGA::E NumPoints_2_ENumPoints(int numPoints)
{
    if (numPoints == 8192) { return ENumPointsFPGA::_8k; }
    else if (numPoints == 4096) { return ENumPointsFPGA::_4k; }
    else if (numPoints == 2048) { return ENumPointsFPGA::_2k; }
    else if (numPoints == 1024) { return ENumPointsFPGA::_1k; }
    else
    {
        LOG_ERROR("");
    }
    return ENumPointsFPGA::_512;
}



int ENumPoints_2_NumPoints(ENumPointsFPGA::E numPoints)
{
    static const int n[ENumPointsFPGA::Count] =
    {
        512,
        1024,
        2048,
        4096,
        8192
    };
    return n[static_cast<uint>(numPoints)];
}
