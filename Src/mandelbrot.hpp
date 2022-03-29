#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#include <SFML/Graphics.hpp>
#include <immintrin.h>
#include <cmath>
#include <cstdlib>

namespace Mandelbrot
{

    enum Errors
    {
        PixelsAreNullptr     = 1,
        FailedLoadingTexture = 2,
    };

    struct Config
    {
        sf::RenderWindow &window;

        unsigned int     *pixels;

        // current settings of Mandelbrot

        // unsigned int colorscheme(unsigned int number);

        float xCurrentCenter = 0;
        float yCurrentCenter = 0;

        // initial scale to see almost full mandelbrot
        float scale          = 0.25f;

        float x0_init = 0;
        float y0_init = 0;

        // dx = -dy = delta
        float delta   = 0;
    };

} // namespace Mandelbrot

#endif // MANDELBROT_H_
