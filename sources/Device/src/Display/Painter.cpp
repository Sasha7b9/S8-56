#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Display_Primitives.h"
#include "Painter.h"
#include "Keyboard/DecoderDevice.h"
#include "Utils/Math.h"
#include "Hardware/FSMC.h"
#include "Hardware/Timer.h"
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using Display::Char;
using Display::HLine;
using Display::Point;
using Display::Rectangle;
using Display::Region;
using Display::Text;
using Display::VLine;
using Display::VPointLine;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Painter::DrawMultiVPointLine(int numLines, int y0, const uint16 *x0, int delta, int count, Color color)
{
    Color::SetCurrent(color);

    for(int i = 0; i < numLines; i++)
    {
        int x = x0[i];
        for(int numPoint = 0; numPoint < count; numPoint++)
        {
            int y = y0 + numPoint * delta;
            //SetPoint(x, y);
            Point().Draw(x, y);
        }
    }
}
