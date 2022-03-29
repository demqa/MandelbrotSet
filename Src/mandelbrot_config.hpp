#ifndef MANDELBROT_CONFIG_H_
#define MANDELBROT_CONFIG_H_

#include "mandelbrot.hpp"

namespace Mandelbrot
{
    enum WindowSettings
    {
        windowWidth  = 640,
        windowHeight = 360,
    };

    int maxCounters  = 512;

    float radiusSquaredMax = 100.f;

} // namespace Mandelbrot

#endif // MANDELBROT_CONFIG_H_
