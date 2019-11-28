#include "defines.h"
#include "AdvancedFont.h"


struct NativeSymbol
{
    uint8 width;    // ������ ������� � ��������
    uint8 height;   // ������ ������� � ��������
//    uint8 data;     // ������ ���� ������ ������ �������

    /// ���������� ���������� ���� � ������
    int BytesInRow();
    /// ���������� ��������� �� ������ ���� ������
    uint8 *GetRow(int row);
    /// ���������� ��������� �� ������ ���� ������
    uint8 *Data();
};

/// ���������� ���������
struct HeaderFont
{
    uint         offsets[256];  // �������� 256 �������� �������. 0 ��������, ��� ������ �����������
    NativeSymbol symbol;        // ������ ������ � ������� ��� �������� 256

    /// ���������� ��������� �� ������, ���� �� ������������ � ������� � nullptr � �������� ������
    NativeSymbol *GetSymbol(uint8 num);

    static HeaderFont *Sefl();
};


extern unsigned char fontGOST28[9158];


TypeFont::E AdvancedFont::currentType = TypeFont::None;


static uint8 *fonts[TypeFont::Count] =
{
    nullptr,        // _5
    nullptr,        // _8
    nullptr,        // _UGO
    nullptr,        // _UGO2
    fontGOST28      // _GOST28
};

static uint8 *font = nullptr;


void AdvancedFont::Set(TypeFont::E t)
{
    currentType = t;
    font = fonts[currentType];
}


bool AdvancedFont::RowNotEmpty(uint8 s, int r)
{
    HeaderFont *header = HeaderFont::Sefl();

    NativeSymbol *symbol = header->GetSymbol(s);

    if (symbol)
    {
        uint8 *row = symbol->GetRow(r);

        for (int i = 0; i < symbol->BytesInRow(); i++)
        {
            if (row[i] != 0)
            {
                return true;
            }
        }
    }

    return false;
}


uint8 AdvancedFont::GetWidth(uint8 num)
{
    NativeSymbol *symbol = HeaderFont::Sefl()->GetSymbol(num);

    return symbol ? symbol->width : 0U;
}

uint8 AdvancedFont::GetHeight(uint8 num)
{
    NativeSymbol *symbol = HeaderFont::Sefl()->GetSymbol(num);

    return symbol ? symbol->height : 0U;
}


uint8 AdvancedFont::GetHeight()
{
    uint8 result = 0;

    for (int i = 0; i < 256; i++)
    {
        NativeSymbol *symbol = HeaderFont::Sefl()->GetSymbol(static_cast<uint8>(i));

        if (symbol && symbol->height > result)
        {
            result = symbol->height;
        }
    }

    return result;
}


int NativeSymbol::BytesInRow()
{
    int result = width / 8;

    if (width % 8)
    {
        result++;
    }

    return result;
}


uint8 *NativeSymbol::GetRow(int row)
{
    if (row > height - 1)
    {
        return nullptr;
    }

    return Data() + row * BytesInRow();
}


NativeSymbol *HeaderFont::GetSymbol(uint8 num)
{
    HeaderFont *header = HeaderFont::Sefl();

    if (header->offsets[num] == 0)
    {
        return nullptr;
    }

    uint8 *offset = reinterpret_cast<uint8 *>(header) + header->offsets[num];

    return reinterpret_cast<NativeSymbol *>(offset);
}


HeaderFont *HeaderFont::Sefl()
{
    return reinterpret_cast<HeaderFont *>(font);
}


uint8 *NativeSymbol::Data()
{
    return reinterpret_cast<uint8 *>(this) + sizeof(*this);
}
