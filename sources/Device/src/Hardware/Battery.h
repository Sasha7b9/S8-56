#pragma once






class Battery
{
public:
    /// �������������
    static void Init();

    static void Draw(int x, int y);
    /// �������� �������� ���������� �������
    static float GetVoltageAKK(uint *adc);
    /// �������� �������� ���������� ��������� ��������� ����������
    static float GetVoltagePOW(uint *adc);
};
