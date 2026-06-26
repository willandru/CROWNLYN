#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Input.h"
#include "ScreenManager.h"
#include "ImagenManager.h"

int main()
{
    Window window(
        1280,
        720,
        "RENDER_WINDOW"
    );

    glViewport(0, 0, 1280, 720); 

    Renderer renderer;
    Input input;
    ScreenManager screenManager;

    Shader shader(
        "Debug/basic.vert",
        "Debug/basic.frag"
    );

    Shader textureShader(
        "Debug/texture.vert",
        "Debug/texture.frag"
    );

    ImagenManager imagen(
    "Debug/image.png"
);

    screenManager.setShader(&shader);

    while (!window.shouldClose() && !screenManager.shouldExit())
    {
        window.pollEvents();

        input.update(window.getNativeWindow());
        screenManager.update(input);

        renderer.begin();

        screenManager.render(renderer);

        if (screenManager.currentScreen() == ScreenType::OneVsAI)
    {
        DrawImageCommand cmd;

        cmd.x = 0.2f;
        cmd.y = 0.2f;
        cmd.w = 0.6f;
        cmd.h = 0.6f;
        cmd.imagen = &imagen;

        renderer.drawImage(
            cmd,
            textureShader
        );
    }

        renderer.end();

        window.display();
    }

    return 0;
}