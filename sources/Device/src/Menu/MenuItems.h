#pragma once
#include "Display/Display.h"
#include "Display/Colors.h"
#include "MenuItemsDefs.h"


class Page;


struct DataItem
{
    uint8               type;       ///< ��� �����
    const char         *title;      ///< ��������� �����
    const char         *hint;       ///< ��������� ��� ������ ������
    const Page * const *keeper;     ///< ����� ��������, ������� �����������. ��� Page_Main = 0
    pFuncBV             funcActive; ///< ��������� �� �������, ������� ����������, ������� �� ������ ����
    const void         *ad;         ///< ��������� �� ��������� � �������, �������������� ��� ������� ��������� Item
};


class Item
{
public:
    /// ������ ���� ������� ����
    struct Type
    {
        enum E
        {
            None,
            Choice,         ///< ����� ������ - ��������� ������� ���� �� ���������� �������� ��������.
            Button,         ///< ������.
            Page,           ///< ��������.
            Governor,       ///< ��������� - ��������� ������� ����� ����� �������� �������� �� ������� ��������� ����������. �������� �� ����� ��������� [ -(1 << 16) / 2 , (1 << 16) / 2]
            GovernorColor,  ///< ��������� ������� ����.
            GraphButton,    ///< ������ ��� ������ ����� ������
            Number
        } value;

        explicit Type(E v) : value(v) {};
    };

    const DataItem *data;
    
    Item(const DataItem * const data = nullptr);
    /// ���������� ������� ����, ������������ �� ������
    static const int NUM_ON_DISPLAY = 5;
    /// ���������� true, ���� ������, ��������������� �������� ���� item, ��������� � ������� ���������
    bool IsPressed() const;
    /// �������/��������� �������
    void SetCurrent(bool active) const;
    /// ���������� true, ���� ������� ���� �� ������ item ������
    bool IsOpened() const;

    void Open(bool open) const;
    /// ���������� �������� ��������, ��� ��� �������� �� ������� �������
    String Title() const;
    /// ���������� true, ���� ������� ��������� � �������� ��������� (��������� �� ������ ����������)
    bool IsActive() const { return data->funcActive(); };

    bool IsCurrentItem() const;
    /// ���������� ����� ��������
    const Page *Keeper() const { if (data->keeper == nullptr) { return nullptr; } return *data->keeper; }
    /// ���������� true, ���� � ����� ������� ����� keeper
    bool ExistKeeper(const Page *keeper) const;
    /// ����� �������� - �� �������� ������� ��������� ����
    bool HaveParent() const { return Keeper() != nullptr; };
    /// ������� ����� �� ����������� - ��������� ���� ����������.
    int PositionOnScreenX() const;
    /// ���������� ���� ������� � ������ ��������
    int PositionInKeeperList() const;
    /// ������ �����
    int Height() const;
    /// ������ �����. pos - ������� ����� �� ������.
    int Width(int pos = -1) const;
    /// ���������� ���� ���� ��������� �����
    Color ColorTitleBackground() const;
    /// ���������� ����, ������� ����� �������� �� ��������� �����
    Color ColorTitleDraw() const;
    /// ���� ������� �����
    Color ColorFrame() const;

    void DrawCommonHiPart(int x, int y, bool opened) const;

    struct Value
    {
        static const int HEIGHT = 13;
    };

    bool Is(Type::E t) const { return data->type == t; };

    virtual void Draw(int /*x*/, int /*y*/, bool /*opened*/) const {};

    virtual void HandlerFX(TypePress::E type) const;
    /// ��������� ������� ������
    virtual bool HandlerKey(const KeyEvent &) { return false; };
    /// ���������� ������ � �������� ��������� �������� Choice ��� Page::Name
    virtual int HeightOpened() const;

    static Item empty;

    static DataItem emptyData;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Page ///
struct DataPage
{
    uint8               name;               ///< ��� �� ������������ Page::Name
    const Item * const *items;              ///< ����� ��������� �� ������ ���� ��������
    pFuncVB             funcOnOpenClose;    ///< ����� ���������� ��� ��������/�������� ��������. ��� �������� � �� ��������� true, ��� �������� - false
    pFuncVV             funcBeforeDraw;     ///< ����� ���������� ����� ��������� ��������
    pFuncBKE            handlerArrows;      ///< ���������� ��� ������� �������
};

/// ��������� �������� ����
class Page : public Item
{
public:
    Page(const DataItem * const data) : Item(data) {};
    /// ���������� true, ���� ������� ������� �������� ������
    bool CurrentItemIsOpened() const;
    /// D��������� ����� ���������� � �������� �� ������ page
    int NumSubPages() const;        
    /// ���������� ���������� ��������� � �������� �� ������ page
    int NumItems() const;
    /// ���������� ������� ������ ��������.
    void SetAsCurrent() const;
    /// ���������� ����� ������� ����������� (���, ������� ������������ � ������ ������)
    int8 CurrentSubPage() const;
    /// ���������� ������� ������ �����������
    void SetCurrentSubPage(int8 pos) const;
    ///< ������������� ������� ��������� ������ ����
    void SetPosActItem(int8 pos) const;
    ///< ���������� ��������� �� �������� ������� ��������
    Item *GetItem(int numItem) const;
    /// \todo ���������� ������� ������� �������� �������� �� ������ page �� ������. ���� ������� ����������� 0, ��� ����� 0, ���� ������� 
    /// ����������� 1, ��� ����� 5 � �.�.
    int PosItemOnLeft() const;
    /// ���������� ������� �������� �������� ������� page
    int8 PosCurrentItem() const;
    /// �������� ����� ������� ����������� �� �������� delta
    void ChangeSubPage(int delta);

    void DrawTitle(int x, int y) const;

    void DrawItems(int x, int y) const;

    void DrawPagesUGO(int right, int bottom) const;

    void DrawNestingPage(int left, int bottom) const;
    /// true, ���� �������� ��������� ������������ �������� parent
    bool IsSubPage(const Page *parent);
    /// ��������� ������� ������
    virtual bool HandlerKey(const KeyEvent &event);
    /// ������� �� ������� �������������� �������, �������������� ����
    virtual void HandlerFX(TypePress::E type) const;
    /// ���������� � �������� �����������
    virtual void Draw(int x, int y, bool opened) const;
    /// ���������� ��������� �� ������, ����������� ��� ����� ������
    DataPage *OwnData() const { return (DataPage *)data->ad; }
    /// ���������� ����� ��������, ���������������� �������������� �������
    const Item *ItemForFuncKey(Key::E key) const;
    /// ���������� ��� �������� page
    PageName::E GetName() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Button ///
struct DataButton
{
    pFuncVV     handlerPress;   ///< �������, ������� ���������� ��� ������� �� ������.
};

class Button : public Item
{
public:
    Button(const DataItem * const data) : Item(data) {};
    virtual void Draw(int x, int y, bool opened) const;
    virtual void HandlerFX(TypePress::E type) const;
    DataButton *OwnData() const { return (DataButton *)data->ad; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// GraphButton ///
struct StructHelpDrawButton
{
    pFuncVII    funcDrawUGO;    ///< ��������� �� ������� ��������� ����������� �������� ������
    pString     helpUGO;        ///< ������� � ������� �����������.
};

struct DataGraphButton
{
    pFuncVV                     handlerPress;   ///< ��� ������� ��������� ��� ��������� ������� ������.
    pFuncVII                    funcDraw;       ///< ��� ������� ���������� ��� ��������� ������ � ����� � ������������ x, y.
    const StructHelpDrawButton *hintUGO;
};

/// ��������� ������ ��� ��������������� ������ ����.
class GraphButton : public Item
{
public:
    GraphButton(const DataItem * const data) : Item(data) {};

    virtual void Draw(int x, int y, bool opened) const;
    void DrawHints(int x, int y, int width) const;
    virtual void HandlerFX(TypePress::E type) const;
    DataGraphButton *OwnData() const { return (DataGraphButton *)data->ad; }
    int NumHints() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Governor ///
struct DataGovernor
{
    int16  *cell;
    int16   min;            ///< ���������� ��������, ������� ����� ��������� ���������.
    int16   max;            ///< ������������ ��������.
    pFuncVV handlerChange;  ///< �������, ������� ����� �������� ����� ����, ��� �������� ���������� ����������.
};

/// ��������� ���������.
class Governor : public Item
{
public:
    Governor(const DataItem * const data) : Item(data) {};
    /// ���������� ��������� ������� ��������, ������� ����� ������� governor.
    int16 NextValue() const;
    /// ���������� ��������� ������� ��������, ������� ����� ������� governor.
    int16 PrevValue() const;
    /// ������������ ��������� ���� ��������.
    float Step() const;
    /// �������� �������� � ������� ������� ��� ��������� ��������.
    void ChangeValue(int16 delta);
    /// ��� �������� �������� ������������ ������ �� ��������� �������.
    void NextPosition() const;
    /// ��� �������� �������� ������������ ������ �� ���������� �������
    void PrevPosition();
    /// ���������� � ��������� ����
    void DrawOpened(int x, int y) const;
    /// ���������� � �������� ���� (� ������ ����)
    void DrawClosed(int x, int y) const;
    /// ���������� ��������
    void DrawValue(int x, int y) const;
    /// ���������� ������ �����, ��������������� �������� ��������
    char GetSymbol() const;
    /// ���������� ��������, ������������� � ����������
    int16 GetValue() const;
    /// ����� ����� ��������
    void SetValue(int16 v) const;
    /// ��������� ������� ������
    virtual bool HandlerKey(const KeyEvent &event);
    /// ��������� ������� �������������� ������, ��������������� ������� �����
    virtual void HandlerFX(TypePress::E type) const;

    virtual void Draw(int x, int y, bool opened) const;

    DataGovernor *OwnData() const { return (DataGovernor *)data->ad; }

private:

    void DrawLowPart(int x, int y) const;
    /// ���������� ����� ��������� � ���� ��� ����� �������� governor. ������� �� ������������� ��������, ������� ����� ��������� governor.
    uint  NumDigits() const;

    static int8 currentDigit;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Choice ///
struct DataChoice
{
    int8       *cell;
    pString    *names;          ///< �������� ������.
    pFuncVB     handlerChange;  ///< ������� ������ ���������� ����� ��������� �������� ��������.
    pFuncVII    funcAfterDraw;  ///< ������� ���������� ����� ��������� ��������. 
};

class Choice : public Item
{
public:
    Choice(const DataItem * const data) : Item(data) {};
    /// ��������� ������� ��������� �������� �� delta
    void  StartChange(int delta) const;
    /// ������������ ��������� ���� ��������.
    float Step() const;
    /// �������� �������� choice � ����������� �� �������� � ����� delta.
    void  ChangeIndex(int delta) const;
    /// ���������� ���������� ��������� ������ � �������� �� ������ choice
    int   NumChoices() const;

    void  DrawOpened(int x, int y) const;

    void  DrawClosed(int x, int y) const;
    /// ���������� ��� �������� �������� ������ �������� choice, ��� ��� �������� � �������� ���� ���������
    String NameCurrentSubItem() const;
    /// ���������� ��� ���������� �������� ������ �������� choice, ��� ��� �������� � �������� ���� ���������
    const char *NameNextSubItem() const;

    const char *NamePrevSubItem() const;
    /// ���������� ��� �������� ������ �������� choice � ������� i ��� ��� �������� � �������� ���� ���������
    String NameSubItem(int i) const;
    /// ���������� ����, ������� ����� ��������� ������� ������
    static Color ColorMenuField(const Choice *choice);

    char GetSymbol();

    virtual void Draw(int x, int y, bool opened) const;
    /// ��������� ������� ������
    virtual bool HandlerKey(const KeyEvent &event);
    /// ��������� ������� �������������� ������, ��������������� ������� �����
    virtual void HandlerFX(TypePress::E type) const;

    virtual int HeightOpened() const;

    DataChoice *OwnData() const { return (DataChoice *)data->ad; }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// GovernorColor ///
struct DataGovernorColor
{
    ColorType  *ct;                 ///< ��������� ��� �������� �����.
};

class GovernorColor : public Item
{
public:
    GovernorColor(const DataItem * const data) : Item(data) {};
    virtual void Draw(int x, int y, bool opened) const;
    /// ��������� ������� �������������� ������, ��������������� ������� ����� �� ��������
    virtual void HandlerFX(TypePress::E type) const;
    virtual int HeightOpened() const { return 27; };
    DataGovernorColor *OwnData() const { return (DataGovernorColor *)data->ad; }
private:
    void DrawOpened(int x, int y) const;
    void DrawClosed(int x, int y) const;
    void DrawValue(int x, int y) const;
    static const int widthOpened = 129;
    static const int heightOpened = 27;
};
