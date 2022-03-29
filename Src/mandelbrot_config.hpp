#ifndef MANDELBROT_CONFIG_H_
#define MANDELBROT_CONFIG_H_

#include "mandelbrot.hpp"

namespace Mandelbrot
{
    enum WindowSettings
    {
        windowWidth  = 1600,
        windowHeight =  900,
    };

    enum Errors
    {
        PixelsAreNullptr = 1,

    };

    int maxCounters = 256;

    float x0 = -2;
    float y0 = -1;

    float radiusSquaredMax = 100.f;

    float dx = 4.f / windowWidth;
    float dy = 2.f / windowHeight;

} // namespace Mandelbrot

#endif // MANDELBROT_CONFIG_H_
