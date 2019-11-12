#include "defines.h"
#include "Data/DataSettings.h"
#include "Data/Heap.h"
#include "Data/Reader.h"
#include "Hardware/Memory/RAM.h"
#include "Hardware/Memory/ROM.h"
#include "Hardware/Memory/Sector.h"
#include "Settings/Settings.h"
#include "Test/Test.h"
#include <cstdlib>


static void FillData(uint8 *data, uint numPoints)
{
    for (uint i = 0; i < numPoints; i++)
    {
        data[i] = static_cast<uint8>(i);
    }
}

static bool CheckData(uint8 *data, uint numPoints)
{
    for (uint i = 0; i < numPoints; i++)
    {
        if (data[i] != static_cast<uint8>(i))
        {
            return false;
        }
    }

    return true;
}

static void PrepareDS(DataSettings *ds)
{
    ds->Fill(0, 0);

    ds->peackDet = static_cast<uint>(PeakDetMode::Disabled);
    ds->enumPoints = static_cast<uint>(std::rand() % ENumPointsFPGA::Count);

    uint8 *dataA = OUT_A;
    uint8 *dataB = OUT_B;
    
    FillData(dataA, ds->SizeChannel());
    FillData(dataB, ds->SizeChannel());

    ds->dataA = dataA;
    ds->dataB = dataB;
}


bool Test::RAM::Test()
{
    Display::StartTest("���� RAM");

    int numRecord = 8192;

    for (int i = 0; i < numRecord; i++)
    {
        static int line = -1;
        
        line = Display::AddMessage(String("������ %d �� %d, %3.1f%%", i, numRecord, 100.0F * i / numRecord).CString(), line);

        DataSettings ds;

        PrepareDS(&ds);

        ::RAM::Save(&ds);

        DataSettings *read;

        ::RAM::Read(&read);

        if (!CheckData(read->dataA, read->SizeChannel()))
        {
            return false;
        }

        if (!CheckData(read->dataB, read->SizeChannel()))
        {
            return false;
        }

        continue;
    }

    return true;
}


bool Test::ROM::Data::Test()
{
    Display::StartTest("���� ROM");

    Display::AddMessage("������ ������");

    static uint totalMemory = 0;

    ::ROM::Data::EraseAll();

    int numRecord = 128;

    for (int i = 0; i < numRecord; i++)
    {
        static int num = -1;

        num = Display::AddMessage(String("������ %d �� %d, %3.1f%%", i, numRecord, 100.0F * i / numRecord).CString(), num);

        DataSettings ds;

        PrepareDS(&ds);

        uint numInROM = std::rand() % ::ROM::Data::MAX_NUM_SAVED_WAVES;

        ::ROM::Data::Save(numInROM, &ds);

        totalMemory += sizeof(PacketROM) + sizeof(DataSettings) + ds.SizeChannel() + ds.SizeChannel();

        DataSettings *dsRead = nullptr;

        ::ROM::Data::Read(numInROM, &dsRead);

        if (!CheckData(dsRead->dataA, dsRead->SizeChannel()))
        {
            return false;
        }

        if (!CheckData(dsRead->dataB, dsRead->SizeChannel()))
        {
            return false;
        }

        continue;
    }
    
    Display::AddMessage("C����� ������");

    ::ROM::Data::EraseAll();

    Display::AddMessage("��������� �������");

    return true;
}
