#pragma once
#include "Osci/ParametersOsci.h"


// ����� �������� ���������, ������� ������������ ��� ���������� � �� ���������������� ��� ���������� �������


struct SettingsNRST
{
    /*
        �������� !!! ��� ���������� ������ ������ ��������� ������ ���� ���������
    */

    uint   size;                                // ������ ���������. �� ���� ��� �������� �� ������ ����� ����������, ��� ��������� ����� - ����� ����� �������� 0xFFFFFFFF
    int8   balanceShiftADC[Chan::Count];        // ���������� �������� ��� ������������ ���
    int16  numAveForRand;                       // �� �������� ���������� ��������� ������ � ������ �������������.
    int16  numSmoothForRand;                    // ����� ����� ��� ����������� ������ � �������������.
    int16  correctionTime;                      // ����������� ��������� �������.
    int16  enumGameMax;                         // ����������� ����� � ������������� ������
    int16  enumGameMin;                         // ����������� ����� � ������������� �����
    int8   exShift[Chan::Count][Range::Count];  // �������������� ��������
    float  exStretch[Chan::Count];              // �������������� �������� �� ������
    int8   enumAverageRand;                     // ���������� �������������� ���������� � �������������
    // ������������� ��� ���������. ��������� ���������� ������� �������� � ROM � �� �������� � ������, ���� ��������� ����. ���� �������� ���� - ������������� ���������� �� ���������
    void Init();
    // ���������� �������� � ROM. ���������� ������ ���� ��������� � setNRST �� ��������� � ����������� � ROM
    void Save();

    void Reset();

    bool operator!=(const SettingsNRST &rhs);

    // �������� �������������� ��������� ���
    void ResetExtraShift();

    // �������� �������������� �������� ���
    void ResetExtraStretch();
};


extern SettingsNRST setNRST;
