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
    {
        config.pixels[pixelIndex] = 0xFF | (char) rint(100 * (1 + sinf(2 + color))) << 8 | (char) rint(100 * (1 + sinf(4 + color))) << 16 |  (char) rint(100 * (1 + sinf(6 + color))) << 24;
    }
    else
    {
        config.pixels[pixelIndex] = 0xFF000000; // black
    }
}

int GetMandelbrotSet(Mandelbrot::Config &config)
{
    if (config.pixels == nullptr) return Mandelbrot::PixelsAreNullptr;

    float x0_init = config.x0_init;
    float y0_init = config.y0_init;

    __m256 _76543210 = _mm256_set_ps(7, 6, 5, 4, 3, 2, 1, 0);

    __m256 dx          = _mm256_set1_ps(config.delta);
    __m256 _76543210dx = _mm256_mul_ps(_76543210, dx);

    __m256 r2Max       = _mm256_set1_ps(Mandelbrot::radiusSquaredMax);

    float dy = - config.delta;
    float y0_single = y0_init;

    for (int i = 0; i < Mandelbrot::windowHeight; ++i)
    {
        __m256 x0 = _mm256_add_ps(_mm256_set1_ps(x0_init), _76543210dx);
        __m256 y0 = _mm256_set1_ps(y0_single);

        for (int j = 0; j < Mandelbrot::windowWidth; j += 8)
        {
            __m256i N = _mm256_setzero_si256();

            int n = 0;

            __m256  x = x0, y = y0;

            do
            {
                __m256  x2 = _mm256_mul_ps(x, x);
                __m256  y2 = _mm256_mul_ps(y, y);

                __m256  r2 = _mm256_add_ps(x2, y2);

                __m256 cmp = _mm256_cmp_ps(r2, r2Max, _CMP_LE_OQ);
                int   mask = _mm256_movemask_ps(cmp);
                if (mask  == 0) break;       // all points are out

                N = _mm256_sub_epi32(N, _mm256_castps_si256(cmp));
                // this command returns negative value ^

                __m256 xy = _mm256_mul_ps(x, y);

                x = _mm256_add_ps(_mm256_sub_ps(x2, y2), x0);
                y = _mm256_add_ps(_mm256_add_ps(xy, xy), y0);
            }
            while (++n < Mandelbrot::maxCounter);

            for (int nColor = 0; nColor < 8; nColor++)
            {
                int *colors = (int *) &N;

                ConfigPixel(config, Mandelbrot::windowWidth * i + j + nColor, colors[nColor]);
            }

            x0 = _mm256_add_ps(x0, _mm256_mul_ps(_mm256_set1_ps(8), dx));
        }

        y0_single += dy;
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
