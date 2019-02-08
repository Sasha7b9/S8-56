#pragma once


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MULTI_MEASURE           (set.multi_meas)
#define MULTI_RANGE_AC          (set.multi_rangeAC)
#define MULTI_RANGE_DC          (set.multi_rangeDC)
#define MULTI_RANGE_RESISTANCE  (set.multi_rangeResist)
#define MULTI_AVP               (set.multi_avp)

namespace Display
{
    class MultimeterWorker;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Multimeter
{
    class DisplayWorker;

    /// �������������
    void Init();

    void DeInit();

    void Update();
    /// �������� �����������, ��� ��������� ��������� ������ � ����� ��������� ���������� ��������� ����� �������
    void ChangeMode();

    void ChangeAVP();

    void LoadZero();
    /// ������� ����������
    void Calibrate0();
    void Calibrate1();

    /// ����� ��������� �����������
    struct Measure
    {
        enum E
        {
            VoltageDC,
            VoltageAC,
            CurrentDC,
            CurrentAC,
            Resistance,
            TestDiode,
            Bell,
            Number
        } value;
        explicit Measure(E v) : value(v) { };
        char Symbol() const
        {
            static const char symbols[Number] = {'U', 'V', 'I', 'J', 'R', 'Y', 'W' };
            return symbols[value]; //-V2006
        }
        static Measure::E ForSymbol(char symbol);
    };

    /// ������������ ��� ���������
    class Display
    {
    friend class DisplayWorker;
    friend class ::Display::MultimeterWorker;
    private:
        static void Update();
        /// ����� ��� ������� ��������� ��������� �� �������
        static void SetMeasure(const uint8 buffer[10]);

        static void ChangedMode();
    };
    /// ��������� ����������� "����"
    extern uint8 zero;
};
