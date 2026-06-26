#pragma once

class Button
{
public:
    float x;
    float y;
    float width;
    float height;

    bool contains(double mouseX, double mouseY) const;
};