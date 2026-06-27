#include "DrawTableroEngine.h"

#include "Tablero.h"
#include "Renderer.h" // solo por struct, NO uso directo
#include "DrawTableroEngine.h"

#include "Tablero.h"
#include "Renderer.h"
#include "Shader.h"

void DrawTableroEngine::draw(
    const Tablero& t,
    Renderer& renderer,
    const Shader& shader
)
{
    int ancho = t.getAncho();
    int alto  = t.getAlto();

    float cellW = t.getCellWidth();
    float cellH = t.getCellHeight();

    float startX = t.getX();
    float startY = t.getY();

    for (int y = 0; y < alto; y++)
    {
        for (int x = 0; x < ancho; x++)
        {
            DrawRectCommand cmd;

            cmd.x = startX + x * cellW;
            cmd.y = startY + y * cellH;
            cmd.w = cellW;
            cmd.h = cellH;

            bool dark = ((x + y) % 2 == 0);

            cmd.r = dark ? 0.2f : 0.8f;
            cmd.g = dark ? 0.2f : 0.8f;
            cmd.b = dark ? 0.2f : 0.8f;

            renderer.drawRect(cmd, shader);
        }
    }
}