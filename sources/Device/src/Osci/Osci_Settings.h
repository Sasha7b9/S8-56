#pragma once


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SET_RSHIFT(ch)          (Osci::Settings::RShift::Value(ch))
#define SET_RSHIFT_A            (SET_RSHIFT(Chan::A))
#define SET_RSHIFT_B            (SET_RSHIFT(Chan::B))


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Osci
{
    namespace Settings
    {
        /// ���������� �������� ��������� �������������
        void LoadHoldfOff();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        struct Range
        {
            static void Change(Chan::E ch, int delta);

            static void LoadBoth();

            enum E
            {
                _2mV,
                _5mV,
                _10mV,
                _20mV,
                _50mV,
                _100mV,
                _200mV,
                _500mV,
                _1V,
                _2V,
                _5V,
                _10V,
                _20V,
                Size
            } value;
            explicit Range(E v) : value(v) {};
            pString Name() const;

            pString ToString(Divider::E divider);

        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        struct RShift
        {
            /// ��� �������� ������������� �������� ��������
            static const int MIN = 20;
            /// ��� �������� ������������ ��������� ��������
            static const int MAX = 980;
            /// ��� �������� ������������� �������� ������
            static const int ZERO = 500;
            /// �������� �� delta
            static void Change(Chan::E ch, int delta);
            /// ���������� ��������
            static void Set(Chan::E ch, uint16 rShift);
            /// ��������� � ����������
            static void Load(Chan::E ch);
            /// ���������� ��� �� ������
            static void DrawBoth();
            /// ������������� � ������
            static String ToString(uint16 rShiftRel, Osci::Settings::Range::E range, Divider::E divider);
            /// ���������� ������ �� ��������
            static uint16 &Value(Chan::E ch);

        private:

            static void Draw(Chan::E ch);
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        struct TBase
        {
            enum E
            {
                _2ns,
                _5ns,
                _10ns,
                _20ns,
                _50ns,
                _100ns,
                _200ns,
                _500ns,
                _1us,
                _2us,
                _5us,
                _10us,
                _20us,
                _50us,
                _100us,
                _200us,
                _500us,
                _1ms,
                _2ms,
                _5ms,
                _10ms,
                _20ms,
                _50ms,
                _100ms,
                _200ms,
                _500ms,
                _1s,
                _2s,
                _5,
                _10s,
                Size
            } value;
            explicit TBase(E v) : value(v) {};

            pString Name() const;

            pString ToString() const;

            static void Load();

            static void Change(int delta);

            /// � ����� �������� ������ ���������� ����� ����������� ������
            static const E MIN_P2P = _50ms;
            /// ����������� ������� �� �������, ��� ������� ��� �������� ��������� ������ �������� ���������
            static const E MIN_PEAK_DET = _200ns;
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        namespace Trig
        {
            static const int MIN = 20;
            static const int MAX = 980;
            static const int ZERO = 500;
            /// ���������� true � ������ ������� ��������������
            bool SyncPulse();
            /// ������� ������� ������������� ������ �����
            void DrawOnGrid();
            /// ����� ������ ���� ������� ������� ������������� ����� �������������� ������ ������� � ������� timMS �����������
            static void NeedForDraw(uint timeMS);

            /// �������� �������������
            struct Source
            {
                enum E
                {
                    A,    /// ����� 1
                    B     /// ����� 2
                } value;

                static void Load();
            };

            struct Level
            {
                static void Load();

                static void Change(int delta);
            };

            /// ����� �������.
            struct StartMode
            {
                enum E
                {
                    Auto,     ///< ��������������.
                    Wait,     ///< ������.
                    Single    ///< �����������.
                } value;
            };

            struct ModeFind
            {
                enum E
                {
                    Hand,      ///< ������� ������������� ��������������� ������� ��� ������������� - ����������� ��������� ������.
                    Auto       ///< ���������� ������ ������������� ������������ ������������� ����� ������� ������ ���������� �������.
                } value;
            };

            struct Input
            {
                enum E
                {
                    Full,
                    HF,
                    LF
                } value;

                /// ���������� � �������������� ��������� ������, ���������� �� �������� � ���� �������������
                static void Load();
            };

            struct Polarity
            {
                enum E
                {
                    Rising,
                    Falling
                } value;

                static void Load();
            };

            extern bool pulse;
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        namespace Memory
        {
            /// ����� ����� �������, � ������� ��� ������.
            struct ENumPointsFPGA
            {
                enum E
                {
                    _512,
                    _1k,
                    _2k,
                    _4k,
                    _8k,
                    Size
                } value;
                explicit ENumPointsFPGA(E v) : value(v) {};
            };
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        class TShift
        {
        public:
            static int Min();
            static int Zero();
            static int Max();

            TShift(int tshift);

            int InPoints();

            static void Set(int tShift);

            static void Load();

            static void Change(int delta);

            operator int() const { return value; };

            String ToString(Osci::Settings::TBase::E tBase) const;

        private:

            static int value;
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        struct PeakDetMode
        {
            enum E
            {
                Disabled,
                Enabled,
                Average
            } value;
            explicit PeakDetMode(E v) : value(v) {};
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// ��������� ����� ������������� �� �������.
        struct TPos
        {
            enum E
            {
                Left,          ///< �������� � ������ ����.
                Center,        ///< �������� � ������.
                Right          ///< �������� � ������� ����.
            } value;
            explicit TPos(E v) : value(v) {};
            /// ������ �������� ���������� ������ ������������� � ������
            int InBytes();
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// ��� ������� ��� ������ �������������.
        struct SampleType
        {
            enum E
            {
                Real,    ///< �������� ����� - � ���������� ��������� ������ ������� ��������� �����, ������ �� ��������������.
                Equal    ///< ������������� - ������ �������� �� ��������� ������, ���������� �� �������������.
            } value;
            explicit SampleType(E v) : value(v) {};
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// ������� ��/���.
        struct FunctionTime
        {
            enum E
            {
                Time,
                ShiftInMemory
            } value;
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// ��� �������� � �������� �� �����������
        struct LinkingTShift
        {
            enum E
            {
                Time,     ///< �������� ��������� � �������
                Position  ///< �������� ��������� � �������
            } value;
        };
    }
}
