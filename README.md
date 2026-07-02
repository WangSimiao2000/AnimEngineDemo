# AnimEngineDemo

AnimEngineDemo is built on top of [MiaoAnimEngine](https://github.com/WangSimiao2000/MiaoAnimEngine)

## Features

The demo (`src/main.cpp`) contrasts the two animation models AnimEngine
provides, using raylib only for visualization:

- **Tween vs Spring, side by side** — two balls chase the same target on the X
  axis. Press `SPACE` to flip the target and watch how each model reacts.
  - **RED (Tween)** — fixed-duration easing (`EaseInOut`). Re-targeting
    mid-flight has to restart the animation, producing a visible snap.
  - **BLUE (Spring)** — physics-based, interruptible. Re-targeting keeps the
    current velocity and smoothly redirects, with no restart.
- 3D perspective camera, grid, and an on-screen HUD showing each ball's
  position and the spring's live velocity.

## Building

### Requirements

- CMake 3.16 or higher
- C++17 compiler
- Dependencies are included as git submodules under `external/`

### Windows (MSVC)

```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

The executable will be generated at `build\Release\demo.exe`

### Linux / macOS (GCC/Clang)

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)  # Linux
# or
cmake --build .  # Generic
```

The executable will be generated at `build/demo`

### IDE Build

If using CLion, Visual Studio, or other CMake-compatible IDEs:

1. Open the project root directory
2. The IDE will automatically detect CMakeLists.txt
3. Select build configuration (Debug/Release)
4. Click the build button

### Notes

- The project automatically compiles `external/raylib` and `external/AnimEngine` dependencies
- raylib examples and games are disabled (`BUILD_EXAMPLES OFF`) to speed up compilation
- If git submodules are not initialized, run:
  ```bash
  git submodule update --init --recursive
  ```
