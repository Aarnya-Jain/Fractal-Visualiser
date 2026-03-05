# Fractal Visualiser

A high-performance, interactive fractal exploration engine built with **C** and **Raylib**. This project provides a real-time environment to visualise and manipulate various fractal algorithms, leveraging both CPU-based recursion and GPU-accelerated shaders.


## Features

- **Multiple Fractal Engines**:
  - **Fractal Trees**: Recursive branching with adjustable angles and thickness.
  - **Barnsley Fern**: Iterated Function System (IFS) based plant simulation.
  - **L-System**: String-rewriting based plant growth with stochastic branching.
  - **Julia Set**: GPU-accelerated rendering using GLSL shaders for smooth, real-time exploration.
- **Interactive Controls**:
  - Real-time parameter adjustment via **RayGUI** sliders.
  - Dynamic fractal switching using a dropdown menu.
  - Toggleable color gradients and cosine color palettes.
  - Wind simulation for tree-based fractals.
- **Performance**:
  - Efficient C implementation.
  - GPU-accelerated Julia set rendering for high-resolution exploration.

## Dependencies

To build and run this project, you need the following:

- **Raylib**: A simple and easy-to-use library to enjoy videogames programming.
- **RayGUI**: Immediate-mode GUI library for Raylib.
- **OpenGL / GLSL**: Required for shader-based rendering.
- **GCC**: Or any compatible C compiler.

## Build Instructions

You can compile the project using the following command:

```bash
gcc main.c -o fractal -lraylib -lm -lpthread -ldl -lrt -lX11
```

> [!NOTE]
> Ensure that `raylib` is installed on your system and available in your library path.

## Project Structure

The project is organised into modular engines for each fractal type:

```text
.
├── main.c                  # Entry point and UI logic
├── raygui.h                # GUI implementation
└── engines/                # Fractal generation logic
    ├── Fractal-Trees/      # Recursive tree implementation
    ├── Barnsley-Fern/      # IFS based fern implementation
    ├── L-System-Trees/     # L-System plant growth
    └── Julia-Set/          # GLSL shaders and Julia set logic
```

## Controls / Usage

- **Dropdown Menu**: Switch between different fractal engines (Tree, Fern, L-System, Julia Set).
- **Sliders**:
  - **Tree/L-System**: Adjust length, thickness, branching ratio, and angles.
  - **Fern**: Control iteration count and scale.
  - **Julia Set**: Modify complex constants (`cx`, `cy`), zoom scale, and max iterations.
- **Toggles**:
  - **Color**: Enable/disable color palettes.
  - **Wind**: Toggle wind animation for trees.
  - **Symmetric**: Force symmetric branching for L-Systems and Trees.

## Screenshots

| Fractal Tree | Julia Set |
| :---: | :---: |
| ![Tree](https://github.com/user-attachments/assets/f5756922-4159-4a0a-89f9-e5bcf75374ca) | ![Julia](https://github.com/user-attachments/assets/288f52dd-3908-4f50-a8d5-eacb8e8e45c7) |

| Barnsley Fern | L-System |
| :---: | :---: |
| ![Fern](https://github.com/user-attachments/assets/54c98ff1-d744-483c-afb8-b34745e8cb6d) | ![L-System](https://github.com/user-attachments/assets/815f69ac-74ec-4ccc-aa63-cc425ff8908e) |

## Other Fractals

- The project is liscenced under the MIT license and open for contributions.
- Other fractals can be added to the project by following the same structure as the existing fractals.