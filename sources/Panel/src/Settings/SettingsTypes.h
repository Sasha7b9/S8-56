#pragma once



struct Chan
{
    enum E
    {
        A,
        B,
        Number
    } value;
    operator uint8() const { return (uint8)value; }
};
