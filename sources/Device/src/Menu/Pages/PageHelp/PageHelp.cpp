#include "defines.h"
#include "Display/Display_Primitives.h"
#include "Display/Painter.h"
#include "Menu/MenuItems.h"
#include "Utils/CommonFunctions.h"
#include "Menu/Menu.h"
#include "Menu/Pages/Include/PageHelp.h"
#include "Menu/Pages/Include/HelpContent.h"


using namespace Display::Primitives;

extern const Page pHelp;

const Page * const PageHelp::self = (const Page *)&pHelp;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void DrawSB_Help_ParagraphEnter(int x, int y)
{
    Font::SetCurrent(Font::Type::_UGO2);
    Char('\x4a').Draw4SymbolsInRect(x + 2, y + 2);
    Font::SetCurrent(Font::Type::_8);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawSB_Help_ParagraphLeave(int x, int y)
{
    Font::SetCurrent(Font::Type::_UGO2);
    Char('\x48').Draw4SymbolsInRect(x + 2, y + 1);
    Font::SetCurrent(Font::Type::_8);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawSB_Help_ParagraphPrev(int x, int y)
{
    Font::SetCurrent(Font::Type::_UGO2);
    Char('\x4c').Draw4SymbolsInRect(x + 2, y + 5);
    Font::SetCurrent(Font::Type::_8);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawSB_Help_ParagraphNext(int x, int y)
{
    Font::SetCurrent(Font::Type::_UGO2);
    Char('\x4e').Draw4SymbolsInRect(x + 2, y + 5);
    Font::SetCurrent(Font::Type::_8);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool HandlerKey_Help(KeyEvent)
{
    return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_GRAPH_BUTTON( sbHelpParagraphEnter,                                                                                                                            //--- ������ - ������� ---
    "�������",
    "��������� ������ �������",
    &PageHelp::self, HelpContent_EnterParagraphIsActive, HelpContent_EnterParagraph, DrawSB_Help_ParagraphEnter
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_GRAPH_BUTTON( sbHelpParagraphLeave,                                                                                                                            //--- ������ - ������� ---
     "�������",
     "��������� ������ �������",
    &PageHelp::self, HelpContent_LeaveParagraphIsActive, HelpContent_LeaveParagraph, DrawSB_Help_ParagraphLeave
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_GRAPH_BUTTON( sbHelpParagraphPrev,                                                                                                                   //--- ������ - ���������� ������ ---
    "���������� ������",
    "������� ���������� ������ �������",
    &PageHelp::self, E_BtV, HelpContent_PrevParagraph, DrawSB_Help_ParagraphPrev
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_GRAPH_BUTTON( sbHelpParagraphNext,                                                                                                                    //--- ������ - ��������� ������ ---
    "��������� ������",
    "������� ��������� ������ �������",
    &PageHelp::self, E_BtV, HelpContent_NextParagraph, DrawSB_Help_ParagraphNext
)

/*
static void PressSB_Help_Exit()
{

}
*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
DEF_GRAPH_BUTTON_EXIT(  sbExitHelp,                                                                                                                                  //--- ������ - ����� ---
    pHelp, 0, PressSB_Help_Exit, DrawSB_Help_ParagraphNext
)
*/

/*
DEF_PAGE_SB(        pHelp,                                                                                                                                                   //--- ������ ---
    "������", "HELP",
    "������� ������� ������",
    "To open sections of the help",
    &sbExitHelp,
    &sbHelpParagraphEnter,
    &sbHelpParagraphLeave,
    0,
    &sbHelpParagraphPrev,
    &sbHelpParagraphNext,
    Page::Name::SB_Help, Menu::pageMain, 0, 0, HelpContent_Draw, HandlerKey_Help
)
*/

DEF_PAGE_4( pHelp, // -V641 // -V1027                                                                                                                                        //--- ������ ---
    "������",
    "������� ������� ������",
    &sbHelpParagraphEnter,
    &sbHelpParagraphLeave,
    &sbHelpParagraphPrev,
    &sbHelpParagraphNext,
    PageName::Help, nullptr, E_BtV, E_VB, HelpContent_Draw, HandlerKey_Help
)
