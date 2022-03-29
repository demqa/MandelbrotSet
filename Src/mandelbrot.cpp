#include "mandelbrot_config.hpp"

int ProceedKeyboard(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Key::Left:
            case sf::Keyboard::Key::H:     break;
            case sf::Keyboard::Key::Down:
            case sf::Keyboard::Key::J:     break;
            case sf::Keyboard::Key::Up:
            case sf::Keyboard::Key::K:     break;
            case sf::Keyboard::Key::Right:
            case sf::Keyboard::Key::L:     break;

            case sf::Keyboard::Key::A:     break;
            case sf::Keyboard::Key::S:     break;

            case sf::Keyboard::Key::Q:     break;

            default:
              break;
        }
    }

    return 0;
}

int WindowDraw(sf::RenderWindow &window, unsigned char *pixels)
{
    if (pixels == nullptr) return Mandelbrot::PixelsAreNullptr;

    sf::Image     image;
    sf::Sprite   sprite;
    sf::Texture texture;

    image.create(Mandelbrot::windowWidth, Mandelbrot::windowHeight, pixels);
    image.saveToFile("cringe.png");
    texture.loadFromImage(image);
    sprite.setTexture(texture);

    window.draw(sprite);

    return 0;
}


int GetMandelbrotSet(unsigned char *pixels)
{
    if (pixels == nullptr) return Mandelbrot::PixelsAreNullptr;

    float x0_init = Mandelbrot::x0;
    float y0_init = Mandelbrot::y0;

    float dx = Mandelbrot::dx;
    float dy = Mandelbrot::dy;

    for (int i = 0; i < Mandelbrot::windowHeight; ++i)
    {
        float y0 = y0_init + dy * i;
        for (int j = 0; j < Mandelbrot::windowWidth; ++j)
        {
            float x0 = x0_init + dx * j;
            int n = 0;


            float x = x0 * x0 - y0 * y0 + x0;
            float y = x0 * y0 + x0 * y0 + y0;

            while (++n < Mandelbrot::maxCounters && x*x + y*y < Mandelbrot::radiusSquaredMax)
            {
                float x2 = x * x;
                float y2 = y * y;
                float xy = x * y;

                x = x2 - y2 + x0;
                y = xy + xy + y0;
            }

            if (n != 256)
                *((unsigned int *) pixels + j + Mandelbrot::windowWidth * i) = 0xFF + n * 256 * 256 * 256 + n * 128;
        }
    }

    return 0;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(Mandelbrot::windowWidth, Mandelbrot::windowHeight), "Manbelbrot Set");

    unsigned char *pixels = (unsigned char *) calloc(Mandelbrot::windowWidth * Mandelbrot::windowHeight, 4);
    if (pixels == nullptr) return -1;

    for (int i = 0; i < Mandelbrot::windowWidth * Mandelbrot::windowHeight; ++i)
    {
        // *((unsigned int *)pixels + i) = 0xFF80FF00;
        //                                A B G R
    }

    while (window.isOpen())
    {
        sf::Event event;
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            ProceedKeyboard(window, event);
        }

        GetMandelbrotSet(pixels);

        window.clear();

        WindowDraw(window, pixels);

        window.display();
    }

    free(pixels);

    return 0;
}
