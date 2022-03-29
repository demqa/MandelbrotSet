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

    int maxCounter   = 500;

    double radiusSquaredMax = 4;

    const char *  fontSrc   = "Src/Ubuntu-Monospace.ttf";
    const char *formatStr   = "%3.2lf  ";
} // namespace Mandelbrot

#endif // MANDELBROT_CONFIG_H_
