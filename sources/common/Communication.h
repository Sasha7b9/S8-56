#pragma once

/*
    ���������������� �������������� ����� ������������
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Communicator
{

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    namespace Transmitter
    {
        void SetCallbacks(
            void(*InitSendPin)(),
            void(*InitPins)(),
            bool(*ReadALLOW_SEND)(),
            bool(*ReadCONF_DATA)(),
            void(*WriteREQ_SEND)(int),
            void(*WriteCLK)(int),
            void(*WriteDATA)(int)
        );
        /// �������� size ����, ������� � ������ data
        void Send(uint8 *data, uint size);
        void Send(uint8 data);
        void Send(uint8 byte0, uint8 byte1);
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    namespace Receiver
    {
        void SetCallbacks(
            void(*InitPins)(),
            bool(*ReadREQ_SEND)(),
            bool(*ReadCLK)(),
            void(*WriteALLOW_SEND)(int),
            void(*WriteCONF_DATA)(int),
            void(*FuncRead)(uint8)
        );
        /// ������� ������������ ������. ��������� ������, ���� ������� �������, � ������� �� ����� �������, ������������� � SetCallbackReceive.
        void Update();
    };

};

