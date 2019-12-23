#pragma once
#include "Data/DataSettings.h"
#include "Hardware/Memory/RAM.h"
#include "Menu/Pages/Include/PageMemory.h"


extern const DataSettings *pDS;     ///< ��������� �� ��������� �������� ��������� �������. ���������� � ���� ������� ����� ������ DS.
extern uint8 *dataOUT[2];           ///< ��������� ������ ������� ������
extern const uint8 *dataIN[2];
extern uint16 *ave[2];

#define DS          pDS             ///< ��������� �� ��������� �������� ��������� �������.

#define IN(ch)  (dataIN[static_cast<int>(ch)])
#define IN_A    IN(Chan::A)
#define IN_B    IN(Chan::B)
#define OUT(ch) (dataOUT[static_cast<int>(ch)])
#define OUT_A   OUT(Chan::A)
#define OUT_B   OUT(Chan::B)

#define AVE_DATA(ch) ave[static_cast<int>(ch)]
#define AVE_1        AVE_DATA(Chan::A)
#define AVE_2        AVE_DATA(Chan::B)


#define RANGE_DS(ch)    (RANGE(DS, ch))
#define RSHIFT_DS(ch)   (RSHIFT(DS, ch))
#define RSHIFT_DS_A     (RSHIFT(DS, Chan::A))
#define RSHIFT_DS_B     (RSHIFT(DS, Chan::B))
#define TBASE_DS        (TBASE(DS))


#define TIME_TIME_DS    (TIME_TIME(DS))
#define TIME_DAY_DS     (TIME_DAY(DS))
#define TIME_HOURS_DS   (TIME_HOURS(DS))
#define TIME_MINUTES_DS (TIME_MINUTES(DS))
#define TIME_SECONDS_DS (TIME_SECONDS(DS))
#define TIME_MONTH_DS   (TIME_MONTH(DS))
#define TIME_YEAR_DS    (TIME_YEAR(DS))

#define BYTES_IN_CHANNEL_DS    (BYTES_IN_CHANNEL(DS))


/// � ���� ��������� ����� ��������� �����, �������������� ��� ������ �� �����
struct StructDataDrawing
{
    uint8       data[Chan::Count][281 * 2];    ///< ������ ����� �������. ����� � ��� ���� ������, ��� �� ������, ��� �������� ���������
    bool        needDraw[Chan::Count];         ///< ���� true, �� ����� 1 ���� ��������
    uint8       notUsed0[2];
    int         posBreak;                      ///< ������� � ����������� �����, �� ������� ����� �������� ����� ������� ����������� ������
    ModeWork::E forMode;                       ///< ��� ������ ������ ����������� ������
    uint8       notUsed1[3];
};



class Reader
{
public:
    /// ������ ������ �� ���������
    static void ReadDataFromRAM();

    static void ReadDataFromROM();
private:
    /// ����� ������ �������������, ���� ���������� �������������� ����� ������
    static void FindTrigLevelIfNeed();
};
