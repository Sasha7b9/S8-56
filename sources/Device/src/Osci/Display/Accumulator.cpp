#include "defines.h"
#include "Data/Reader.h"
#include "Osci/Display/DisplayOsci.h"
#include "Settings/Settings.h"



/// Количество отрисованных сигналов
static int numFrames = 0;



/// Возвращает номер выводимого сигнала
static uint CurrentFrame();



void DisplayOsci::Accumulator::NextFrame()
{
    if (set.disp.modeAccumulation == ModeAccumulation::Reset)
    {
        static uint prevFrame = 0;

        LOG_WRITE("%d", CurrentFrame());

        if (CurrentFrame() == prevFrame)
        {
            return;
        }

        prevFrame = CurrentFrame();

        numFrames++;
        if (numFrames >= set.disp.ENumAccum)
        {
            DisplayOsci::SetFlagRedraw();
            numFrames = 0;
        }
    }
    else
    {
        DisplayOsci::SetFlagRedraw();
    }
}


void DisplayOsci::Accumulator::Reset()
{
    numFrames = 0;
}


static uint CurrentFrame()
{
    return (DATA) ? DATA->Number() : 0;
}
