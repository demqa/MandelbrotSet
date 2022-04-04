#include "mandelbrot_config.hpp"

namespace Mandelbrot
{

inline void ZoomIn   (Mandelbrot::Config &config){ config.scale *= 0.5f;  }
inline void ZoomOut  (Mandelbrot::Config &config){ config.scale *= 2.f;   }
inline void Close    (Mandelbrot::Config &config){ config.window.close(); }

inline void MoveLeft (Mandelbrot::Config &config){ config.xCurrentCenter -= 10 * config.delta; }
inline void MoveRight(Mandelbrot::Config &config){ config.xCurrentCenter += 10 * config.delta; }
inline void MoveUp   (Mandelbrot::Config &config){ config.yCurrentCenter += 10 * config.delta; }
inline void MoveDown (Mandelbrot::Config &config){ config.yCurrentCenter -= 10 * config.delta; }

inline int ProceedKeyboard(Mandelbrot::Config &config, sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        using namespace Mandelbrot;
        switch (event.key.code)
        {
            case sf::Keyboard::Key::H:
            case sf::Keyboard::Key::Left:  MoveLeft (config); break;
            case sf::Keyboard::Key::J:
            case sf::Keyboard::Key::Down:  MoveDown (config); break;
            case sf::Keyboard::Key::K:
            case sf::Keyboard::Key::Up:    MoveUp   (config); break;
            case sf::Keyboard::Key::L:
            case sf::Keyboard::Key::Right: MoveRight(config); break;

            case sf::Keyboard::Key::A:     ZoomIn   (config); break;
            case sf::Keyboard::Key::S:     ZoomOut  (config); break;
            case sf::Keyboard::Key::Q:     Close    (config); break;

            default:                                          break;
        }
    }

    return 0;
}

int WindowDraw(Mandelbrot::Config &config)
{
    if (config.pixels == nullptr) return Mandelbrot::PixelsAreNullptr;

    sf::Image     image;
    sf::Sprite   sprite;
    sf::Texture texture;

    image.create(Mandelbrot::windowWidth, Mandelbrot::windowHeight, (unsigned char *) config.pixels);
    if (!texture.loadFromImage(image)) return Mandelbrot::FailedLoadingTexture;
    sprite.setTexture(texture);

    sf::Text text(config.string, config.font);

    config.window.draw(sprite);
    config.window.draw(text);

    return 0;
}

inline void UpdateMandelbrotConfig(Mandelbrot::Config &config)
{
    config.x0_init = config.xCurrentCenter -   8 * config.scale;
    config.y0_init = config.yCurrentCenter + 4.5 * config.scale;

    config.delta   = config.scale * 16 / Mandelbrot::windowWidth;
}

inline void GetMandelbrotFPS(Mandelbrot::Config &config)
{
    // fuck my life
    sf::Time time = config.clock.getElapsedTime();

    config.FPS = 1.f / time.asSeconds();

    sprintf(config.string, formatStr, config.FPS);

    config.clock.restart();
}

inline void ConfigPixel(Mandelbrot::Config &config, int pixelIndex, int color)
{
    if (color != Mandelbrot::maxCounter)
        config.pixels[pixelIndex] = 0xFF | color << 24 | color * 3 << 16 | color / 2 << 8;
    else
        config.pixels[pixelIndex] = 0xFF000000;
}

int GetMandelbrotSet(Mandelbrot::Config &config)
{
    if (config.pixels == nullptr) return Mandelbrot::PixelsAreNullptr;

    double x0_init = config.x0_init;
    double y0_init = config.y0_init;

    double dx =   config.delta;
    double dy = - config.delta;

    for (int i = 0; i < Mandelbrot::windowHeight; ++i)
    {
        double y0 = y0_init + dy * i;
        for (int j = 0; j < Mandelbrot::windowWidth; ++j)
        {
            double x0 = x0_init + dx * j;
            int n = 0;

            double x = x0 * x0 - y0 * y0 + x0;
            double y = x0 * y0 + x0 * y0 + y0;

            while (++n < Mandelbrot::maxCounter && x*x + y*y < Mandelbrot::radiusSquaredMax)
            {
                double x2 = x * x;
                double y2 = y * y;
                double xy = x * y;

                x = x2 - y2 + x0;
                y = xy + xy + y0;
            }

            ConfigPixel(config, j + Mandelbrot::windowWidth * i, n);
        }
    }

    return 0;
}

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(Mandelbrot::windowWidth, Mandelbrot::windowHeight), "Manbelbrot Set");

    sf::Clock clock;
    clock.restart();

    sf::Font   font;
    if (!font.loadFromFile(Mandelbrot::fontSrc)) return -3;

    unsigned int *pixels = (unsigned int *) calloc(Mandelbrot::windowWidth * Mandelbrot::windowHeight, 4);
    if (pixels == nullptr) return -1;

    char *string = (char *) calloc(strlen(Mandelbrot::formatStr), sizeof(char));
    if (string == nullptr) return -2;

    Mandelbrot::Config config = {window, clock, font, pixels, string};

    while (window.isOpen())
    {
        sf::Event event;
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            Mandelbrot::ProceedKeyboard(config, event);
        }

        Mandelbrot::UpdateMandelbrotConfig(config);

        Mandelbrot::GetMandelbrotSet(config);

        Mandelbrot::GetMandelbrotFPS(config);

        window.clear();

        Mandelbrot::WindowDraw(config);

        window.display();
    }

    free(pixels);
    free(string);

    return 0;
}
