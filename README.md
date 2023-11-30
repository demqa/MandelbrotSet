# MandelbrotSet visualizer using SFML

There are 4 branches: noOptimise, AVX2 (8 floats in parallel), double (no optimise), AVX2withDoubles (4 doubles in parallel).

**I measured it with my processor i5-8265U:**

| Optimisation \ Number of checks:  |  500 checks      |  1000 checks     |
| :-------------------------------: | :--------------: | :--------------: |
| noOptimise                        | 3.41  FPS        | 1.75  FPS        |
| AVX2                              | 17.12 FPS (5.0x) | 10.45 FPS (6.0x) |
| noOptimiseDoubles                 | 3.28  FPS        | 1.65  FPS        |
| AVX2withDoubles                   | 10.67 FPS (3.3x) | 6.08  FPS (3.7x) |

### Control Hotkeys

**Moving: HJKL or arrows**

| Action   |  Hotkey |
|   ---:   |  :---:  |
| Zoom In  |    A    |
| Zoom Out |    S    |
| Close    |    Q    | 


### Installation

```
git clone https://github.com/demqa/MandelbrotSet.git && cd MandelbrotSet
# checkout preferred version. for maximum FPS use AVX2, for best experience use AVX2withDoubles
make && ./mandelbrot
```

