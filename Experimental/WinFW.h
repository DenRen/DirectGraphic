#include <vector>
#include "DX11FW.h"

class WidgetCoor
{
public:
    WidgetCoor () :
        WidgetCoor (0, 0)
    {}
    WidgetCoor (float x, float y) :
        x (x), y(y)
    {}

    WidgetCoor operator + (WidgetCoor &rhs)
    {
        return WidgetCoor (x + rhs.x, y + rhs.y);
    }

    float x;
    float y;
};

class Widget
{
public:

private:
    int m_id;
    static int counterId;

protected:
    WidgetCoor m_coor;
};

class WinMgr
{
public:

private:
    std::vector <Widget *> m_child;
};

class RectTex : public Widget, public Rectangle
{
public:
    void Draw (WidgetCoor parentCoor = WidgetCoor ());

private:
};

void RectTex::Draw (WidgetCoor parentCoor)
{
    WidgetCoor coor = m_coor + parentCoor;

    Rectangle::Draw (coor.x, coor.y);
};