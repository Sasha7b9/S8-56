#pragma once
#include "Colors.h"
#include "Display_Types.h"
#include "Display/Font/Font.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Painter
{
    void Init();

    void BeginScene(Color color);

    void EndScene();
    /// ���� �� ���������� �������� �����, �� ���� ��������� �������
    void SetColor(Color color = Color::NUMBER);

    void SetColorValue(Color color, uint value);

    void SetFont(Font::Type::E typeFont);

    void Draw4SymbolsInRect(int x, int y, char eChar, Color color = Color::NUMBER);

    void ResetFlash();
    /// ����� ����� � ����������
    int DrawTextInRectWithTransfers(int x, int y, int width, int height, const char *text);

    int DrawStringInCenterRectAndBoundItC(int x, int y, int width, int height, const char *text, Color colorBackground, Color colorFill);
    /// ���������� ������ ���������� ��������������
    int DrawTextInBoundedRectWithTransfers(int x, int y, int width, const char *text, Color colorBackground, Color colorFill);
    /// ����� ������ ������ � ������ �������(x, y, width, height)������ ColorText �� �������������� � ������� ������� widthBorder ����� colorBackground
    void DrawStringInCenterRectOnBackgroundC(int x, int y, int width, int height, const char *text, Color colorText, int widthBorder,
                                                    Color colorBackground);
    /// ���������� ������� �������.
    void SetBrightnessDisplay(int16 brightness);

    static int DrawTextInRectWithTransfersC(int x, int y, int width, int height, const char *text, Color color);

    void Draw10SymbolsInRect(int x, int y, char eChar);

    void DrawTextRelativelyRight(int xRight, int y, const char *text, Color color = Color::NUMBER);
    /// ���������� ������� ���� ���������
    Color GetColor();
    /// ���������� ������ ������������ �����. ����� �������� ���� �� ������. y0y1 - ������ ������������ ���������.
    void DrawVLineArray(int x, int numLines, uint8 *y0y1, Color color);
    /// \brief ���������� numLines ������������ �����, ��������� �� count ����� ������ � ����������� ����� ������� delta. �������������� ����������
    /// ������ ����� ������ ����� ������������� ���������� �������� ������� x[]
    void DrawMultiVPointLine(int numLines, int y, const uint16 *x, int delta, int count, Color color = Color::NUMBER);
    /// \brief ���������� numLines �������������� �����, ��������� �� count ����� ������ � ����������� ����� ������� delta. ������������ ����������
    /// ������ ����� ������ ����� ������������� ���������� �������� ������� y[]
    void DrawMultiHPointLine(int numLines, int x, const uint8 *y, int delta, int count, Color color = Color::NUMBER);
    /// ���������� �������������� ����� �� x0 �� x1 ������� ����� ������ delta ��������
    void DrawHPointLine(int y, int x0, int x1, float delta);
    /// ���������� ������������ ����� �� y0 �� y1 ������� ����� ������ delta ��������
    void DrawVPointLine(int x, int y0, int y1, float delta);

    void DrawTesterData(uint8 mode, Color color, const uint8 *x, const uint8 *y);

    void DrawDashedVLine(int x, int y0, int y1, int deltaFill, int deltaEmtpy, int deltaStart);

    void DrawDashedHLine(int y, int x0, int x1, int deltaFill, int deltaEmpty, int deltaStart);

    void SaveScreenToDrive();

    static int DrawCharWithLimitation(int eX, int eY, char symbol, int limitX, int limitY, int limitWidth, int limitHeight);

    static bool ByteFontNotEmpty(uint eChar, int byte);

    static bool BitInFontIsExist(int eChar, int numByte, int bit);

    void OnTimerFlashDisplay();
    /// ���������� ������� ���� � �������. ���������� false, ���� ������� ���� ����������
    bool WriteFlashColor();
    /// ���������� ���� � �������
    void WriteColor(Color color);

    extern Color currentColor;
};
