#include "defines.h"
#include "Display/Colors.h"
#include "Display/Painter.h"
#include "Settings/Settings.h"
#include "Settings/SettingsDisplay.h"
#include "Utils/Math.h"



const uint8 Color::COLOR_BLACK              = 0;
const uint8 Color::COLOR_WHITE              = 1;
const uint8 Color::COLOR_GRID               = 2;
const uint8 Color::COLOR_DATA_A             = 3;
const uint8 Color::COLOR_DATA_B             = 4;
const uint8 Color::COLOR_MENU_FIELD         = 5;
const uint8 Color::COLOR_MENU_TITLE         = 6;
const uint8 Color::COLOR_MENU_TITLE_DARK    = 7;
const uint8 Color::COLOR_MENU_TITLE_BRIGHT  = 8;
const uint8 Color::COLOR_MENU_ITEM          = 9;
const uint8 Color::COLOR_MENU_ITEM_DARK     = 10;
const uint8 Color::COLOR_MENU_ITEM_BRIGHT   = 11;
const uint8 Color::COLOR_DATA_WHITE_ACCUM_A = 12;
const uint8 Color::COLOR_DATA_WHITE_ACCUM_B = 13;
const uint8 Color::COLOR_GRID_WHITE         = 14;
const uint8 Color::COLOR_EMPTY              = 15;
const uint8 Color::COLOR_NUMBER             = 16;
const uint8 Color::COLOR_FLASH_10           = 17;
const uint8 Color::COLOR_FLASH_01           = 18;
const uint8 Color::COLOR_INVERSE            = 19;



Color Color::BLACK(COLOR_BLACK);
Color Color::WHITE(COLOR_WHITE);
Color Color::MENU_FIELD(COLOR_MENU_FIELD);
Color Color::MENU_TITLE_DARK(COLOR_MENU_TITLE_DARK);
Color Color::MENU_TITLE_BRIGHT(COLOR_MENU_ITEM_BRIGHT);
Color Color::MENU_ITEM_DARK(COLOR_MENU_ITEM_DARK);
Color Color::MENU_ITEM_BRIGHT(COLOR_MENU_ITEM_BRIGHT);
Color Color::DATA_WHITE_ACCUM_A(COLOR_DATA_WHITE_ACCUM_A);
Color Color::DATA_WHITE_ACCUM_B(COLOR_DATA_WHITE_ACCUM_B);
Color Color::NUMBER(COLOR_NUMBER);
Color Color::FLASH_10(COLOR_FLASH_10);
Color Color::FLASH_01(COLOR_FLASH_01);

Color Color::CHAN[4] = {Color(COLOR_DATA_A), Color(COLOR_DATA_B), Color(COLOR_WHITE), Color(COLOR_WHITE)};
Color Color::FILL(COLOR_WHITE);
Color Color::BACK(COLOR_BLACK);
Color Color::GRID(COLOR_GRID);


#define BACKGROUND_BLACK true



void Color::InitGlobalColors()
{
    Color::BACK.value = BACKGROUND_BLACK ? Color::BLACK.value : Color::WHITE.value;
    Color::FILL.value = BACKGROUND_BLACK ? Color::WHITE.value : Color::BLACK.value;
    Color::GRID.value = BACKGROUND_BLACK ? Color(COLOR_GRID).value : Color(COLOR_GRID_WHITE).value;
    Color::CHAN[A].value = BACKGROUND_BLACK ? Color::CHAN[A].value : Color::DATA_WHITE_ACCUM_A.value;
    Color::CHAN[B].value = BACKGROUND_BLACK ? Color::CHAN[B].value : Color::DATA_WHITE_ACCUM_B.value;
//    Color::CHAN[A_B].value = Color::CHAN[MathCh].value = BACKGROUND_BLACK ? Color::WHITE.value : Color::BLACK.value;
}


void Color::Log(Color color)
{
#define colorVal (COLOR(color.value))
}


Color Color::Cursors(Channel ch)
{
    return CHAN[ch];
}


Color Color::BorderMenu(bool shade)
{
    return MenuTitle(shade);
}


Color Color::MenuTitle(bool shade)
{
    return shade ? Color(COLOR_MENU_ITEM) : Color(COLOR_MENU_TITLE);
}


Color Color::LightShadingText()
{
    return MenuTitle(false);
}


Color Color::MenuItem(bool shade)
{
    return shade ? Color(COLOR_MENU_ITEM_DARK) : Color(COLOR_MENU_ITEM);
}

Color Color::Contrast(Color color)
{
    col_val colorValue = COLOR(color.value);
    if (R_FROM_COLOR(colorValue) > 16 || G_FROM_COLOR(colorValue) > 32 || B_FROM_COLOR(colorValue) > 16)
    {
        return Color(COLOR_BLACK);
    }
    return Color(COLOR_WHITE);
}


bool operator!=(const Color &left, const Color &right)
{
    return left.value != right.value;
}


bool operator==(const Color &left, const Color &right)
{
    return left.value == right.value;
}


bool operator>(const Color &left, const Color &right)
{
    return left.value > right.value;
}


void ColorType::Init(bool forced)
{
    if (forced)
    {
        alreadyUsed = false;
    }

    if (!alreadyUsed)
    {
        alreadyUsed = true;                  // ������� ����, ��� ��������� ��������� ��� �����������

        col_val colorValue = COLOR(color.value);

        red = (float)R_FROM_COLOR(colorValue);
        green = (float)G_FROM_COLOR(colorValue);
        blue = (float)B_FROM_COLOR(colorValue);

        SetBrightness();
        
        if (red == 0.0F && green == 0.0F && blue == 0.0F) //-V550 //-V2550
        {
            stepRed = 0.31F;
            stepGreen = 0.63F;
            stepBlue = 0.31F;
        }
    }
}


void ColorType::SetBrightness(float bright)
{
    if (IsEquals(bright, -1.0F))
    {
        brightness = MaxFloat(red / 31.0F, green / 63.0F, blue / 31.0F);

        CalcSteps();
    }
    else
    {
        int delta = static_cast<int>((bright + 0.0005F) * 100.0F) - static_cast<int>(brightness * 100.0F);

        if (delta > 0)
        {
            for (int i = 0; i < delta; i++)
            {
                BrightnessChange(1);
            }
        }
        else
        {
            for (int i = 0; i < -delta; i++)
            {
                BrightnessChange(-1);
            }
        }
    }
}


/*
�������� ��������� �������.
1. �������������.
�. ���������� ������� �� �������� - ������� ����� ������������� ������������� ������ ������ ��������� ������
�. ���������� ��� ��������� �������� ������������ ������� ������ �� 1% ������� �� �������:
��� = ������������� ������ * �������, ��� ������� - ������������� �������� ����� �������
�. ���� ������������� ���� ������� == 0, �� ���� ������ ��� ������� ������
2. ��� ���������� ������� �� 1% ������ ������������� ������� ������ �� ���, ����������� � ���������� ������.
3. ��� ��������� ������������� ��������� ������ ������������� ������� � ��� ��������� ������� ������.
*/


void ColorType::BrightnessChange(int delta)
{
    if ((delta > 0 && brightness == 1.0F) || (delta < 0 && brightness == 0.0F)) //-V550 //-V2550
    {
        return;
    }

    int sign = Sign(delta);

    brightness += sign * 0.01F;
    LIMITATION(brightness, 0.0F, 1.0F); //-V2516

    red += sign * stepRed;
    green += sign * stepGreen;
    blue += sign * stepBlue;

    SetColor();

    if (stepRed < 0.01F && stepGreen < 0.01F && stepBlue < 0.01F)
    {
        stepRed = 0.31F;
        stepGreen = 0.63F;
        stepBlue = 0.31F;
    }
}


void ColorType::CalcSteps()
{
    stepRed = red / (brightness * 100.0F);
    stepGreen = green / (brightness * 100.0F);
    stepBlue = blue / (brightness * 100.0F);
}


void ColorType::SetColor()
{
    COLOR(color.value) = MAKE_COLOR(red, green, blue);
    Painter::SetPalette(color);
}


void ColorType::ComponentChange(int delta)
{
    static const float maxs[4] = {0.0F, 31.0F, 63.0F, 31.0F};
    float * const pointers[4] = {0, &blue, &green, &red};
    int8 index = currentField;

    if (index >= 1 && index <= 3)
    {
        *(pointers[index]) += static_cast<float>(Sign(delta));
        Limitation<float>(pointers[index], 0.0F, maxs[index]);
    }

    SetColor();

    SetBrightness();
}


Color& Color::operator=(const Color &color)
{
    value = color.value;
    return *this;
}

#ifdef OSCI


Color Color::Trig()
{
    if (TRIGSOURCE_IS_EXT)
    {
        return FILL;
    }
    return CHAN[(Channel)TRIGSOURCE];
}


Color Color::ChanAccum(Channel ch)
{
    return (ch == A) ? Color(COLOR_DATA_WHITE_ACCUM_A) : Color(COLOR_DATA_WHITE_ACCUM_B);
}

#endif
