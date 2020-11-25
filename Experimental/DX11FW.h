struct RectShape
{};

class Sprite
{
public:
    void Draw (float coorX, float coorY);

private:
};

class Rectangle : public Sprite
{
public:
    void Draw (float coorX, float coorY);
private:
    RectShape m_recrShape;
};
