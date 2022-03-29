#ifndef MANDELBROT_CONFIG_H_
#define MANDELBROT_CONFIG_H_

#include "mandelbrot.hpp"

namespace Mandelbrot
{
    enum WindowSettings
    {
        windowWidth  = 1280,
        windowHeight = 720,
    };

    int maxCounter   = 300;

    float radiusSquaredMax = 4.f;

} // namespace Mandelbrot

#endif // MANDELBROT_CONFIG_H_
