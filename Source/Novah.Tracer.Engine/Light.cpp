#include "NovahTracerEngine.h"

Light::Light(const Color3& color)
    : _color(color), _random(Random())
{

}

Color3 Light::GetColor() const
{
    return _color;
}

void Light::SetColor(const Color3& color)
{
    _color = color;
}