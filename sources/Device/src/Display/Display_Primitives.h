#pragma once


namespace Display
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Primitive
    {
    public:
        Primitive(int x, int y);
        void Draw();

    protected:
        int x;
        int y;
        Color color;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Region
    {
    public:
        Region(int width, int height);
        void Draw(int x, int y, Color color = Color::NUMBER);
    private:
        int width;
        int height;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Rectangle
    {
    public:
        Rectangle(int width, int height);
        void Draw(int x, int y, Color color = Color::NUMBER);
    private:
        int width;
        int height;
    };


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class HLine
	{
	public:
		HLine(int width);
		void Draw(int x, int y, Color = Color::NUMBER);
	private:
	};


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class VLine
    {
    public:
        VLine(int height);
        void Draw(int x, int y, Color = Color::NUMBER);
    private:
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Line
    {
    public:
        Line(int x0, int y0, int x1, int y2);
        void Draw(Color = Color::NUMBER);
    private:
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Char
    {
    public:
        Char(char ch);
        int Draw(int x, int y, Color = Color::NUMBER);
    private:
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Point
    {
    public:
        Point();
        int Draw(int x, int y, Color = Color::NUMBER);
    private:
    };
}
