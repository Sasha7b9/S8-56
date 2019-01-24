#pragma once

#include "Osci/Osci_Settings.h"
#include "Osci/Measurements/Measures.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Osci
{
    namespace Processing
    {
        /// ���������������� ��������� ��������� ������ ������������� �������� sinX/X
        void InterpolationSinX_X(uint8 *data, int numPoints, Osci::Settings::TBase::E tBase);
        /// ���������� ������ ��������������� ���������
        String GetStringMeasure(Measurements::Measure::Type::E measure, Chan::E ch, char *buffer, int lenBuf);
        /// ��������� ��� �������������� ���������
        void CalculateMeasures();

        extern int markerTime[Chan::Size][2];

        extern int markerVoltage[Chan::Size][2];
    };
};
