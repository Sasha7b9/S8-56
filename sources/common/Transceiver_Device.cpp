#include "defines.h"
#include "Transceiver.h"


namespace Transceiver
{
    namespace Transmitter
    {
        void Init();
        void InitPinsSend();
        int Read_MODE_PANEL();
        void Set_MODE_CONFIRM();
        void Reset_MODE_CONFIRM();
        void Set_BYTE_SET();
        void Reset_BYTE_SET();
        void WriteData(uint8 data);
    }

    namespace Receiver
    {
        void Init();
        void InitPinsReceive();
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Transceiver::Init()
{
    Transmitter::Init();
    Receiver::Init();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Transceiver::Transmitter::Init()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Transceiver::Receiver::Init()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Transceiver::Transmitter::InitPinsSend()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Transceiver::Receiver::InitPinsReceive()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Transceiver::Transmitter::Send(uint8 *data, uint size)
{
    while (Read_MODE_PANEL() == 0)
    {
        Receiver::Update();
    }

    InitPinsSend();

    Set_BYTE_SET();

    Set_BYTE_SET();

    for (uint i = 0; i < size; i++)
    {
        WriteData(data[i]);

        Reset_BYTE_SET();
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Transceiver::Transmitter::Read_MODE_PANEL()
{
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Transceiver::Transmitter::Set_MODE_CONFIRM()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Transceiver::Transmitter::Reset_MODE_CONFIRM()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Transceiver::Transmitter::Set_BYTE_SET()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Transceiver::Transmitter::Reset_BYTE_SET()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Transceiver::Transmitter::WriteData(uint8)
{

}
