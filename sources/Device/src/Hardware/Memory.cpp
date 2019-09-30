#include "defines.h"
#include "Memory.h"
#include "Hardware/Beeper.h"
#include <cstring>

#include "Hardware/HAL/HAL.h"


using HAL::EEPROM_;
using HAL::OTP_;



/// ���������� ����� ������� ���������� ����� � ������� ��������
static uint FirstFreeAddressForSettings();
/// \brief ���������� ����� ����������� �������� ��� 0, ���� ��������� �� �����������. fromEnd ���������, ����� ��������� �� �����
/// ����� ��������� - 0 - ���������, 1 - ������������� � ��� �����
static uint AddressSavedSettings(int fromEnd);

static void ReadBytes(uint address, void *data, uint size);

static uint ReadDoubleWord(uint address);



#define SIZE_SECTOR_128         (128 * 1024)

#define READ_BYTE(address)      (*((uint8 *)address))



void Memory::SaveSettings()
{
    /*
        �������� ���������� ������� ���������� �����
        1. ������� ����� = (uint*)ADDR_SECTOR_SETTINGS_1.
        2. �������, ��� �������� �� �������� ������
        2. ���� ��� 0xffffffff, �� ��� ������ ��������� ����� - �������.
        3. ���������� � �������� ������ �������� *((uint*)ADDR_SECTOR_SETTINGS_1).
        4. ��������� � 2
    */
    /*
        1. ���������� � Settings.size �������� sizeof(Settings)
        2. ������� ����� ������� ���������� ����� (�������� ����)
        3. ������� ������_���������_������ = ADDR_SECTOR_SETTINGS_1 + (128 * 1024) - �����_�������_����������_�����
        4. ���� ������_���������_������ > ������_���������_��������, �� ��������� �� ���������� ������ ��������� Settings � �������.
        5. ����� ������� ������ �������� � ���������� � ��� ������ ��������� Settings
    */

    /// \todo ������ ������� ��� �������� �������� ������������, ������ ��� ����� �������� ����� ����������� ������� � ����� �������� ��� ���������

    set.size = sizeof(set);

    uint address = FirstFreeAddressForSettings();

    uint freeMemory = ADDR_SECTOR_SETTINGS_1 + SIZE_SECTOR_128 - address;

    if((address == MAX_UINT) || (freeMemory <= sizeof(Settings)) || (address < ADDR_SECTOR_SETTINGS_1))
    {
        EraseSector(ADDR_SECTOR_SETTINGS_1);
        address = ADDR_SECTOR_SETTINGS_1;
    }

    set.size = sizeof(set);

    WriteData(address, &set, sizeof(set));
}


void Memory::EraseSector(uint address)
{
    EEPROM_::EraseSector(address);
}


void Memory::WriteData(uint address, const void *data, int size)
{
    EEPROM_::WriteBytes(address, (const uint8 *)data, size);
}


static uint FirstFreeAddressForSettings() //-V2506
{
    uint address = ADDR_SECTOR_SETTINGS_1;

    do
    {
        uint value = ReadDoubleWord(address);

        if (value == MAX_UINT)              // ��� ������� ��������, ��� �� ����� ������ ��� ������ �� ������������, ����� ����� ��� �� �������
        {                                   // ������ ��������� (Settings), ���� ������ ������ �������� �� ��� �����
            return address;
        }

        address += value;                   // ��������� �� ������ ��������� ���� �� ����������

    } while(address < (ADDR_SECTOR_SETTINGS_1 + SIZE_SECTOR_128));
    
    
    return MAX_UINT;        // ������-�� �� ���� ����� ����� ����� �� �����. ���� �� ��������� �����, ��������� ������
}


static uint AddressSavedSettings(int)
{
    uint addrPrev = 0;

    uint address = ADDR_SECTOR_SETTINGS_1;

    while (ReadDoubleWord(address) != MAX_UINT)
    {
        addrPrev = address;
        address += ReadDoubleWord(address);
    }

    return addrPrev;
}


static void ReadBytes(uint address, void *data, uint size)
{
    uint8 *buffer = (uint8 *)data;

    for (uint i = 0; i < size; i++)
    {
        buffer[i] = READ_BYTE(address++);
    }
}


bool Memory::GetData(int /*num*/, DataSettings * /*ds*/, uint8 * /*dataA*/, uint8 * /*dataB*/)
{
    return false;
}


void Memory::DeleteData(int /*num*/)
{
}


void Memory::GetDataInfo(bool /*existData*/[MAX_NUM_SAVED_WAVES])
{
}


void Memory::SaveData(int /*num*/, const DataSettings * /*ds*/, uint8 * /*dataA*/, uint8 * /*dataB*/)
{
}


void Memory::DeleteAllData()
{
}


String OTPmem::GetSerialNumber(int *freeForWrite)
{
    char buffer[20];
    *freeForWrite = OTP_::GetSerialNumber(buffer);
    return String(buffer);
}


bool OTPmem::SaveSerialNumber(char *servialNumber) //-V2506
{
    return OTP_::SaveSerialNumber(servialNumber);
}


static uint ReadDoubleWord(uint address)
{
    return (*((uint *)address));
}


bool Memory::LoadSettings()
{
    uint address = AddressSavedSettings(0);

    if (address && ReadDoubleWord(address) == sizeof(set))
    {
        ReadBytes(address, &set, ReadDoubleWord(address));
        return true;
    }

    return false;
}
