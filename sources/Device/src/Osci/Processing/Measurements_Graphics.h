#pragma once


namespace Osci
{
    namespace Measurements
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        namespace Graphics
        {
            /// ���������� ���������� �������������� ���������
            void Draw();

            int NumCols();

            int NumRows();
            /// �� ������� ������� ����� �� �����������
            int GetDeltaGridLeft();
            /// �� ������� ������� ����� �� ���������
            static int GetDeltaGridBottom();
            /// ���������� ������ ���� ��� ������ ��������������� ���������
            static int DY();
            /// ���������� ������ ���� ��� ������ ��������������� ���������
            static int DX();
        };
    }
}
