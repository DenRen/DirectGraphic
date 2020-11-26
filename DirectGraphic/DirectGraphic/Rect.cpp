#include "Widget.h"
#include "Rectangle.h"

class Rect : public Widget, public RectTex
{
public:

	virtual void Draw () = 0;
	virtual void Update () = 0;
	virtual void HandleNews (News news);

private:

};

void Rect::HandleNews (News news)
{

}
