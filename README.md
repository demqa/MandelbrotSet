# MandelbrotSet visualizer using SFML

There are 3 branches: noOptimise, AVX2 (8 floats in parallel),
& AVX2withDoubles (4 doubles in parallel).<br>
**master is equal to AVX2withDoubles**


**I measured it with my processor i5-8265U:**

| Optimisation \ Number of checks:  |  500           |  1000          |
| :-------------------------------: | :------------: | :------------: |
| noOptimise                        | 3.41  FPS      | 1.75  FPS      |
| AVX2                              | 17.12 FPS (5x) | 10.45 FPS (6x) |
| :-------------------------------: | :------------: | :------------: |
| doubles                           | 3.28  FPS      | 1.65  FPS      |
| AVX2withDoubles                   | 10.67 FPS (3x) | 6.08  FPS (4x) |

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
make && ./mandelbrot
```

