#include "defines.h"
#include "Data/Reader.h"
#include "Data/DataSettings.h"
#include "Display/Grid.h"
#include "Display/Primitives.h"
#include "FPGA/ContextOsci.h"
#include "Hardware/HAL/HAL.h"
#include "Osci/Display/DisplayOsci.h"
#include "Osci/Measurements/AutoMeasurements.h"
#include "Osci/Measurements/CursorsMeasurements.h"
#include "Settings/Settings.h"
#include "Utils/Values.h"
#include <cmath>
#include <cstring>
#include <cstdio>


class Separator
{
private:
    VLine *line;
public:
    Separator()
    {
        line = new VLine(17);
    }
    ~Separator()
    {
        delete line;
    }
    void Draw(int x, int y)
    {
        line->Draw(x, y, Color::FILL);
    }
};



/// �������� ��������� ������������� ������ ��������� ������
static void WriteTextVoltage(Chan::E ch, int x, int y);

static void WriteStringAndNumber(const char *text, int x, int y, int number);

static void DrawTime(int x, int y);
/// ���������� �������������� �����
static void DrawSeparators();
/// ���������� ������� ��������� � ��������� �������. ���������� �-���������� ������� �������� ���� ����������� �����������
static int DrawMainParameters(int x, int y);
/// ���������� ������ ����� - ������������� � ����� ������
static void DrawRightPart(int x, int y);

static void WriteCursors();
/// ���������� ������ �������� ���������
static void DrawPeakDet(int x, int y);



void DisplayOsci::HiPart::Draw()
{
    const int y0 = 0;

    int x = -1;

    DrawSeparators();

    x = DrawMainParameters(x, y0 + 1); //-V2007

    x += 82;

    x += 42;

    Font::SetCurrent(TypeFont::_8);

    Separator().Draw(x + 1, y0);

    if (set.mem.modeWork == ModeWork::Dir)
    {
        char mesFreq[20] = "\x7c=";
        float freq = FrequencyCounter::GetFreq();
        if (freq == -1.0F) //-V550 //-V2550
        {
            std::strcat(mesFreq, "******");
        }
        else
        {
            std::strcat(mesFreq, Frequency(freq).ToString().CString());
        }

        String(mesFreq).Draw(x + 3, y0 + 1, Color::FILL); //-V2007
    }

    DrawTime(x + 3, y0 + 10); //-V2007

    DrawRightPart(271, y0);

    WriteCursors();

    DrawPeakDet(x + 37, y0 + 10); //-V2007
}


static void DrawSeparators()
{
    HLine line(Grid::Left() - TableMeasures::GetDeltaGridLeft() - 1);

    line.Draw(1, Grid::ChannelBottom(), Color::SEPARATOR);
    line.Draw(1, Grid::FullBottom());

    HLine line2(::Display::WIDTH - Grid::Right() - 4);

    line2.Draw(Grid::Right() + 2, Grid::Bottom(), Color::FILL);
    line2.Draw(Grid::Right() + 2, Grid::ChannelBottom());
}


static int DrawMainParameters(int _x, int _y)
{
    /*
        ���� ������� ������� ������ ���������, �� ����� �������������� ��������� ������
    */

    if (CursorsOsci::NecessaryDraw())
    {
        _y = Grid::Bottom() + 3;
    }

    int x = _x;
    const int y0 = _y;
    int y1 = _y + 8;

    WriteTextVoltage(Chan::A, x + 2, y0);
    WriteTextVoltage(Chan::B, x + 2, y1);

    x += 98;

    Separator().Draw(x - 3, _y - 1);

    const int SIZE = 100;
    char buffer[SIZE] = { 0 };

    std::snprintf(buffer, SIZE, "�\xa5%s", TBase(set.time.base).ToString());

    String(buffer).Draw(x, y0, Color::FILL);

    buffer[0] = 'a';
    buffer[1] = 0;
    std::snprintf(buffer, SIZE, "\xa5%s", TShift::ToString(set.time.base).CString());
    String(buffer).Draw(x + 35, y0);

    buffer[0] = 0;

    if (set.mem.modeWork == ModeWork::Dir)
    {
        pString source[3] = { "1", "2", "\x82" };
        std::snprintf(buffer, 100, "�\xa5\x10%s", source[(uint8)set.trig.source]);
    }

    String(buffer).Draw(x, y1, Color::Trig());

    buffer[0] = 0;
    static pString couple[] =
    {
        "\x92",
        "\x91",
        "\x92",
        "\x92"
    };
    static pString polar[] =
    {
        "\xa7",
        "\xa6"
    };
    static pString filtr[] =
    {
        "\xb5\xb6",
        "\xb5\xb6",
        "\xb3\xb4",
        "\xb1\xb2"
    };
    if (set.mem.modeWork == ModeWork::Dir)
    {
        std::snprintf(buffer, SIZE, "\xa5\x10%s\x10\xa5\x10%s\x10\xa5\x10", couple[set.trig.input], polar[set.trig.polarity]);
        String(buffer).Draw(x + 18, y1);

        Char(filtr[set.trig.input][0]).Draw(x + 45, y1);
        Char(filtr[set.trig.input][1]).Draw(x + 53, y1);
    }

    buffer[0] = '\0';
    const char mode[] =
    {
        '\xb7',
        '\xa0',
        '\xb0'
    };
    if (set.mem.modeWork == ModeWork::Dir)
    {
        std::snprintf(buffer, 100, "\xa5\x10%c", mode[set.trig.startMode]);
        String(buffer).Draw(x + 63, y1);
    }

    y1 = y1 - 6;
    int y2 = y1 + 6;
    Font::SetCurrent(TypeFont::_5);

    x += 77;

    Separator().Draw(x - 2, y0 - 1);

    if (set.mem.modeWork == ModeWork::Dir)
    {
        WriteStringAndNumber("������", x, y0 - 4, NUM_ACCUM);
        WriteStringAndNumber("������", x, y1, NUM_AVE);
        WriteStringAndNumber("��\x93���", x, y2, NUM_MIN_MAX);
    }

    Separator().Draw(x + 43, y0 - 1);

    return _x + 93;
}


static void WriteTextVoltage(Chan::E ch, int x, int y)
{
    if (!set.ch[ch].enabled)
    {
        return;
    }

    Color color = Color::CHAN[ch];

    bool inverse = set.ch[ch].inverse;
    //int8 divider = (int8)SET_DIVIDER(ch);
    Range::E range = set.ch[ch].range;

    const int widthField = 91;
    const int heightField = 8;
    Color colorDraw = inverse ? Color::WHITE : color;
    if (inverse)
    {
        Region(widthField, heightField).Fill(x, y, color);
    }
    const int SIZE = 100;

    char buffer[SIZE];
    std::snprintf(buffer, SIZE, "%s\xa5%s\xa5%s", Chan(ch).IsA() ? "1�" : "2�", ModeCouple(set.ch[ch].couple).UGO(), Range(range).ToString(static_cast<int8>(set.ch[ch].divider)));
    String(buffer).Draw(x + 1, y, colorDraw);

    char bufferTemp[SIZE];
    std::snprintf(bufferTemp, SIZE, "\xa5%s", RShift::ToString((uint16)SET_RSHIFT(ch), range, static_cast<int8>(set.ch[ch].divider)).CString());
    String(bufferTemp).Draw(x + 46, y);
}


static void WriteStringAndNumber(const char *text, int x, int y, int number)
{
    String(text).Draw(x, y, Color::FILL);

    const int SIZE = 100;
    char buffer[SIZE];

    if (number == 0)
    {
        std::snprintf(buffer, SIZE, "-");
    }
    else
    {
        std::snprintf(buffer, SIZE, "%d", number);
    }
    Text(buffer).DrawRelativelyRight(x + 41, y);
}


static void DrawTime(int x, int y)
{
    int dField = 10;
    int dSeparator = 2;

    PackedTime time = HAL_RTC::GetPackedTime();

    Color::FILL.SetAsCurrent();

    if ((set.mem.modeWork == ModeWork::ROM) || (set.mem.modeWork == ModeWork::RAM))
    {
        if (DS)
        {
            y -= 9;
            time.day = TIME_DAY_DS;
            time.hours = TIME_HOURS_DS;
            time.minutes = TIME_MINUTES_DS;
            time.seconds = TIME_SECONDS_DS;
            time.month = TIME_MONTH_DS;
            time.year = TIME_YEAR_DS;
            Integer((int)time.day).ToString(false, 2).Draw(x, y);
            String(':').Draw(x + dField, y);
            Integer((int)time.month).ToString(false, 2).Draw(x + dField + dSeparator, y);
            String(':').Draw(x + 2 * dField + dSeparator, y);
            Integer((int)time.year + 2000).ToString(false, 4).Draw(x + 2 * dField + 2 * dSeparator, y);

            y += 9;
        }
        else
        {
            return;
        }
    }

    Integer((int)time.hours).ToString(false, 2).Draw(x, y);
    String(':').Draw(x + dField, y);
    Integer((int)time.minutes).ToString(false, 2).Draw(x + dField + dSeparator, y);
    String(':').Draw(x + 2 * dField + dSeparator, y);
    Integer((int)time.seconds).ToString(false, 2).Draw(x + 2 * dField + 2 * dSeparator, y);
}


static void DrawRightPart(int x0, int y0)
{
    // �������������

    Separator().Draw(x0 - 1, y0);

    static const int xses[3] = { 280, 271, 251 };
    int x = xses[set.mem.modeWork];

    if (set.mem.modeWork != ModeWork::RAM)
    {
        x += 2;

        if (Trig::SyncPulse())
        {
            Region(26, 16).Fill(x0 + 1, y0 + 1, Color::FILL);
            String("��").Draw(x0 + 9, y0 + 5, Color::BACK);
        }
    }

    // ����� ������
    static pString strs[] =
    {
        "���",
        "����",
        "����"
    };

    if (set.mem.modeWork != ModeWork::Dir)
    {
        x += 18;

        VLine(Grid::Top() - 3).Draw(x, 1, Color::FILL);

        x += 2;
        String("�����").Draw(x, -1);
        Text(strs[set.mem.modeWork]).DrawInCenterRect(x + 1, 9, 25, 8);
    }
    else
    {
        x -= 9;
    }

    if (set.mem.modeWork != ModeWork::RAM)
    {
        x += 27;

        VLine(Grid::Top() - 3).Draw(x, 1, Color::FILL);

        x += 2;
        int y = y0 + 1;

        if (ContextOsci::IsRunning())       // ������� �����
        {
            Char(Symbol8::PLAY).Draw4SymbolsInRect(x, 1);
        }
        else if (ContextOsci::InStateStop())  // ����� ���������
        {
            Region(10, 10).Fill(x + 3, y + 3);
        }
        else if (ContextOsci::InStateWait())  // ����� �������� �������
        {
            int w = 4;
            int h = 14;
            int delta = 4;
            x = x + 2;
            Region(w, h).Fill(x, y + 1);
            Region(w, h).Fill(x + w + delta, y + 1);
        }
        else
        {
            // ������ ������ �� ������������
        }
    }
}


static void WriteCursors()
{
    int x = 0;
    int y1 = 0;
    int y2 = 0 + 9;

    if (CursorsOsci::NecessaryDraw())
    {
        VLine separator(Grid::Top() - 3);

        separator.Draw(x, 1, Color::FILL);
        separator.Draw(102, 1);
        separator.Draw(203, 1);

        x += 3;
        Chan::E source = set.curs.source;
        Color colorText = Color::CHAN[source];
        if (set.curs.cntrlU[set.curs.source] == CursorsControl::Disable)
        {
            String("1:").Draw(x, y1, colorText);
            String("2:").Draw(x, y2);
            x += 7;
            CursorsOsci::Voltage(source, 0).Draw(x, y1);
            CursorsOsci::Voltage(source, 1).Draw(x, y2);
            x = 49;
            float pos0 = MathFPGA::VoltageCursor(CursorsOsci::PosU(source, 0), set.ch[source].range, SET_RSHIFT(source));
            float pos1 = MathFPGA::VoltageCursor(CursorsOsci::PosU(source, 1), set.ch[source].range, SET_RSHIFT(source));
            float delta = std::fabsf(pos1 - pos0) * DIVIDER_ABS(source);
            String(":dU=").Draw(x, y1);
            Voltage(delta).ToString(false).Draw(x + 17, y1);
            String(':').Draw(x, y2);
            CursorsOsci::PercentsU(source).Draw(x + 10, y2);
        }

        x = 101;
        x += 3;
        if (set.curs.cntrlT[set.curs.source] == CursorsControl::Disable)
        {
            colorText.SetAsCurrent();
            String("1:").Draw(x, y1);
            String("2:").Draw(x, y2);
            x += 7;
            CursorsOsci::Time(source, 0).Draw(x, y1);
            CursorsOsci::Time(source, 1).Draw(x, y2);
            x = 153;

            float pos0 = MathFPGA::TimeCursor(CursorsOsci::PosT(source, 0), set.time.base);
            float pos1 = MathFPGA::TimeCursor(CursorsOsci::PosT(source, 1), set.time.base);
            float delta = std::fabsf(pos1 - pos0);
            String(":dT=").Draw(x, y1);
            Time(delta).ToString(false).Draw(x + 17, y1);
            String(':').Draw(x, y2);
            CursorsOsci::PercentsT(source).Draw(x + 8, y2);

            if (set.curs.showFreq)
            {
                int width = 65;
                x = Grid::Right() - width;
                Rectangle(width, 12).Draw(x, Grid::Top(), Color::FILL);
                Region(width - 2, 10).Fill(x + 1, Grid::Top() + 1, Color::BACK);
                String("1/dT=").Draw(x + 1, Grid::Top() + 2, colorText);
                if (delta != 0.0F) //-V550 //-V2550
                {
                    Frequency(1.0F / delta).ToString().Draw(x + 25, Grid::Top() + 2);
                }
            }
        }
    }
}


static void DrawPeakDet(int x, int y)
{
    if (set.time.peakDet == PeakDetMode::Enabled)
    {
        Char(SymbolUGO2::PEAK_DET_LEFT).Draw(x, y, Color::FILL);
        Char(SymbolUGO2::PEAK_DET_RIGHT).Draw(x + 8, y);
    }
}
