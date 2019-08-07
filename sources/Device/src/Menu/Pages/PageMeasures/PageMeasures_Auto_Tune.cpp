#include "defines.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Include/Definition.h"
#include "Display/Display_Primitives.h"
#include "Display/Painter.h"
#include "Settings/SettingsTime.h"
#include "Osci/Measurements/Measures.h"
#include "Settings/Settings.h"
#include "Menu/Pages/Include/PageMeasures.h"
#include "Utils/Math.h"
#include "Hardware/Beeper.h"

#include "Osci/Measurements/Measurements.h"


using namespace Display::Primitives;
using namespace Osci;
using namespace Osci::Measurements;

extern const PageBase pageTune;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PageBase *PageMeasures::PageAuto::PageTune::pointer = &pageTune;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void Draw_Tune_Markers(int x, int y)
{
    Font::SetCurrent(Font::Type::_UGO2);
    Char('\x60').Draw4SymbolsInRect(x + 2, y + 2);
    Font::SetCurrent(Font::Type::_8);
}

DEF_SMALL_BUTTON( bTune_Markers,                                                                                                                     //--- ��������� - ��������� - ������ ---
    "������",
    "��������� ���������� ������� ��� ����������� �������� ���������",
    pageTune, FuncActive, Measure::ShortPressOnSmallButonMarker, Draw_Tune_Markers
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void Draw_Tune_Settings(int x, int y)
{
    Font::SetCurrent(Font::Type::_UGO2);

    Char('\x62').Draw4SymbolsInRect(x + 2, y + 1);

    Font::SetCurrent(Font::Type::_8);
}

DEF_SMALL_BUTTON( bTune_Settings,                                                                                                                 //--- ��������� - ��������� - ��������� ---
    "���������",
    "��������� ������� ����������� ���������",
    pageTune, FuncActive, Measurements::PageChoice::ChangeState, Draw_Tune_Settings
)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool IsActive_Tune()
{
    return SHOW_MEASURES;
}

static bool HandlerKey_Tune(KeyEvent event)
{
    Osci::Measurements::PageChoice::OnKeyEvent(event);

    return true;
}

DEF_PAGE_2( pageTune, // -V641 // -V1027
    "���������",
    "������� � ����� ������ ��������� ���������� � ����� ���������",
    &bTune_Markers,
    &bTune_Settings,
    Page::Name::Measures_Auto_Tune, PageMeasures::PageAuto::pointer, IsActive_Tune, FuncPressPage, Page::FuncDraw, HandlerKey_Tune
)
