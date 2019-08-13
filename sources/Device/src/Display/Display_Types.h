#pragma once


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MOSI_HEIGHT         9
#define MOI_HEIGHT_TITLE    19
#define MOI_WIDTH_D_IP      34      /* ���������� ������ ��������� ip-������ � ������ ������� ����� */
#define WIDTH_GRAPH_BTN     60
#define HEIGHT_GRAPH_BTN    19
#define GRID_DELTA          20      /* ���������� ����� � ������ */

#define BACKGROUND                  (set.disp_background)
#define BACKGROUND_BLACK            (BACKGROUND == Display::Background::Black)

#define SHOW_STRING_NAVI            (set.disp_showStringNavigation)
#define SHOW_STRING_NAVI_TEMP       (SHOW_STRING_NAVI == Display::ShowStrNavi::Temp)
#define SHOW_STRING_NAVI_ALL        (SHOW_STRING_NAVI == Display::ShowStrNavi::All)

#define MODE_DRAW_SIGNAL            (set.disp_modeDrawSignal)
#define MODE_DRAW_SIGNAL_IS_LINES   (MODE_DRAW_SIGNAL == Display::ModeDrawSignal::Lines)
#define MODE_DRAW_SIGNAL_IS_POINTS  (MODE_DRAW_SIGNAL == Display::ModeDrawSignal::Points)

//#define THICKNESS_SIGNAL            (set.disp_thickness)
//#define THICKNESS_SIGNAL_IS_3       (THICKNESS_SIGNAL == Display::ThicknessSignal::_3)

#define ENUM_MIN_MAX                (set.disp_ENumMinMax)
#define MIN_MAX_ENABLED             (ENUM_MIN_MAX != Display::ENumMinMax::_1)
#define NUM_MIN_MAX                 (1 << (int)ENUM_MIN_MAX)        /* ���������� ���������� ��������� �������� ��� ������� ��������� � ����������. */

#define ENUM_SMOOTHING              (set.disp_ENumSmoothing)
#define SMOOTHING_ENABLED           (ENUM_SMOOTHING != Display::ENumSmoothing::Disable)

#define ACCUMULATION                (set.disp_modeAccumulation)
#define ACCUMULATION_IS_ENABLED     (ACCUMULATION == ::Display::ModeAccumulation::Reset)


#define ENUM_ACCUM                  (set.disp_ENumAccum)
#define NUM_ACCUM                   (1 << (int)ENUM_ACCUM)                   /* ���������� ����� ���������� */

#define MODE_AVE                    (set.disp_modeAveraging)
#define ENUM_AVE                    (set.disp_ENumAverage)
#define NUM_AVE                     (1 << (int)ENUM_AVE)
#define NUM_AVE_MAX                 256
#define IN_AVERAGING_MODE           (ENUM_AVE > Display::ENumAverage::_1 && (!IN_P2P_MODE))

#define TIME_MESSAGES               (set.disp_timeMessages)

#define ENUM_SIGNALS_IN_SEC         (set.disp_ENumSignalsInSec)

#define LAST_AFFECTED_CH            (set.disp_lastAffectedChannel)
#define LAST_AFFECTED_CH_IS_A       (LAST_AFFECTED_CH == Chan::A)
#define DISPLAY_ORIENTATION         (set.dbg_Orientation)
#define DISPLAY_ORIENTATION_IS_NORMAL (DISPLAY_ORIENTATION == Display::Orientation::Normal)

#define ALT_MARKERS                 (set.disp_altMarkers)
#define ALT_MARKERS_SHOW            (ALT_MARKERS == AltMarkers::Show)
#define ALT_MARKERS_HIDE            (ALT_MARKERS == AltMarkers::Hide)
#define ALT_MARKERS_AUTO            (ALT_MARKERS == AltMarkers::AutoHide)

#define LINKING_RSHIFT              (set.disp_linkingRShift)

#define MENU_AUTO_HIDE              (set.disp_menuAutoHide)

#define BRIGHTNESS_DISPLAY          (set.disp_brightness)

#define BRIGHTNESS_GRID             (set.disp_brightnessGrid)

#define SET_NUM_BYTES_ON_DISPLAY    (SET_PEAKDET_EN ? 281 * 2 : 281)

#define SHIFT_IN_MEMORY_IN_POINTS   Display::ShiftInMemoryInPoints()


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Display
{
    struct DrawMode
    {
        enum E
        {
            Auto,
            Hand
        } value;
    };

    /// ����� ����� ����.
    struct Background
    {
        enum E
        {
            Black,
            White
        } value;
    };

    struct ModeDrawSignal
    {
        enum E
        {
            Lines,
            Points
        } value;
    };

    /// ������� ��������� �������
    struct ThicknessSignal
    {
        enum E
        {
            _1,         ///< ������ �������� ������ �������� ���� �����
            _3          ///< ������ �������� ������ �������� ��� �����
        } value;
    };

    /// ����� ������ ������ ���������
    struct ShowStrNavi
    {
        enum E
        {
            Temp,   ///< ���������� �� ��������� ������
            All,    ///< ������ ����������
            None    ///< ������� �� ����������
        } value;
    };

    /// ���������� ��������� ��� ������� ������������ � ������������� ��������.
    struct ENumMinMax
    {
        enum E
        {
            _1,
            _2,
            _4,
            _8,
            _16,
            _32,
            _64,
            _128
        } value;
        explicit ENumMinMax(E v) : value(v) {};
    };

    struct Orientation
    {
        enum E
        {
            Normal,
            Reverse
        } value;
        explicit Orientation(E v) : value(v) {};
    };
    /// ����� ����������� �������������� ������� �������� �������� �� ����������.
    struct AltMarkers
    {
        enum E
        {
            Hide,        /// ������ �� ��������.
            Show,        /// ������ ��������.
            AutoHide     /// �������� � ������� ����� timeShowLevels.
        } value;
        explicit AltMarkers(E v) : value(v) {};
    };

    /// ��� �������� � �������� �� ���������
    struct LinkingRShift
    {
        enum E
        {
            Voltage,      ///< �������� ��������� � ����������
            Position      ///< �������� ��������� � �������
        } value;
    };

    /// ����������� FPS.
    struct ENumSignalsInSec
    {
        enum E
        {
            _25,
            _10,
            _5,
            _2,
            _1
        } value;
        explicit ENumSignalsInSec(E v) : value(v) { };
        /// ���������� ���������� ������������ ����� �������
        uint TimeBetweenFramesMS() const;
    };

    /// ���������� ����� ��� ������� �����������.
    struct ENumSmoothing
    {
        enum E
        {
            Disable,
            _2points,
            _3points,
            _4points,
            _5points,
            _6points,
            _7points,
            _8points,
            _9points,
            _10points
        } value;
        explicit ENumSmoothing(E v) : value(v) { };
        uint ToNumber() const;
    };

    struct ModeAccumulation
    {
        enum E
        {
            NoReset,   /// � ���� ������ ������������ ������ N ���������.
            Reset      /// � ���� ������ ���������� N ��������� � ����� ������������.
        } value;
    };

    /// ���������� ����������.
    struct ENumAccum
    {
        enum E
        {
            _1,
            _2,
            _4,
            _8,
            _16,
            _32,
            _64,
            _128,
            _Infinity
        } value;
    };

    /// ���������� ���������� �� ����������.
    struct ENumAverage
    {
        enum E
        {
            _1,
            _2,
            _4,
            _8,
            _16,
            _32,
            _64,
            _128,
            _256
        } value;
    };
}
