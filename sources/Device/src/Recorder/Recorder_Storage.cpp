#include "defines.h"
#include "Recorder/Recorder_Storage.h"

#include "Hardware/Timer.h"
#include "Data/Heap.h"


using namespace Recorder::Storage;


/// ������ ��� Heap()
namespace Stack
{
    static Frame frame;

    static void Push(const Frame &_frame)
    {
        frame = _frame;
        frame.SetDataAddress((uint16 *)Heap::Data());
    }

    static Frame &Top()
    {
        return frame;
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Recorder::Storage::Init()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint Recorder::Storage::Frame::NumPoints()
{
    return numPoints;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Recorder::Storage::Frame::AddPoint(BitSet16 dataA, BitSet16 /*dataB*/)
{
    start[numPoints] = dataA;
    numPoints++;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Recorder::Storage::Frame &Recorder::Storage::CurrentFrame()
{
    return Stack::Top();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Recorder::Storage::CreateNewFrame()
{
    Frame frame;
    Stack::Push(frame);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Recorder::Storage::Frame::SetDataAddress(uint16 *address)
{
    start = (BitSet16 *)address;
    numPoints = 0;
    pointer = MAX_UINT;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Point Frame::GetPoint(uint position)
{
    pointer = position - 1;

    return NextPoint();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Point Frame::NextPoint()
{
    pointer++;

    if (pointer >= NumPoints())
    {
        return Point::CreateEmpty();
    }

    return Point(start[pointer]);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Point::Max()
{
    return data.byte0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Point::Min()
{
    return data.byte1;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Point::IsEmpty()
{
    return (data.halfWord == 0);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Point Point::CreateEmpty()
{
    return Point(BitSet16(0));
}
