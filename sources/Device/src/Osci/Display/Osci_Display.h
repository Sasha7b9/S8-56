#pragma once



namespace Osci
{
    namespace Display
    {
        void Update();

        void DrawCursorTrigLevel();

        void DrawScaleLine(int x, bool forTrigLev);
        /// ���������� ������� ����, ��� ������� ��������� � �����������
        void SetFlagRedraw();
    }
}
