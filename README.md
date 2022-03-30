# MandelbrotSet visualizer using SFML

There are 3 branches: noOptimise, AVX2 (8 floats in parallel),
& AVX2withDoubles (4 doubles in parallel).
**master is equal to AVX2withDoubles**


**I measured it with my processor i5-8265U:**

| FPS              |  500  |  1000 |
| :--------------: | :---: | :---: |
| noOptimise       | 3.41  | 1.75  |
| AVX2             | 17.12 | 10.45 |
| AVX2withDoubles  | 10.67 | 6.08  |

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

