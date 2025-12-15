# Pathfinding Visualizer (A\*) — Grid

A C++20 desktop application that visualizes the A\* shortest‑path algorithm on a 2D grid. Built with SFML 3 for rendering and TGUI for the user interface.
This project was created as part of my **ADSA (Algorithms & Data Structures)** (course).
This project focuses on:

- incremental algorithms (non‑blocking UI)
- explicit data‑structure choices
- clean separation between grid, graph, algorithm, and UI

## Features

- **Interactive grid**

  - Left‑click to place/remove **walls**

- **Draggable Start & End nodes**

  - Drag with mouse
  - Dropping on a wall removes the wall automatically
  - Start and End **cannot be swapped directly**

- **Incremental A\*** visualization

  - Runs one step per frame (`AStarRunner::step`)
  - UI never freezes during execution

- **Adjustable animation speed** (1–100 ms per step)
- **8‑direction movement** (horizontal, vertical, diagonal)
- **Event‑driven rendering**

  - Window redraws only when state changes

---

## Controls (In‑App)

- **Left Click** on grid cell → Toggle **Wall / Empty**
- **Drag** Start or End cell → Move node
- **Visualize** → Start A\* pathfinding
- **Reset** → Clear walls & reset algorithm state
- **Animation Speed Slider** → Delay per A\* step (ms)

---

## Algorithm Details

### Graph Representation

- Grid is converted into an **adjacency list graph**:

```cpp
std::unordered_map<
    Pair,
    std::unordered_set<Pair, PairHash>,
    PairHash
> adjList;
```

- Nodes are removed/added dynamically when walls change
- Each cell may have up to **8 neighbors**

### Movement Cost

- Horizontal / Vertical: `1.0`
- Diagonal: `1.41421356` (√2)

### Heuristic

- **Diagonal (Octile) Distance**:

```cpp
h = (dx + dy) + (√2 − 2) * min(dx, dy)
```

- Admissible and consistent for 8‑direction movement

### A\* Execution Model

- Implemented in `AStarRunner`
- Uses:

  - `priority_queue` for open list
  - `unordered_set` for closed list
  - `unordered_map` for node details (f, g, h, parent)

- Algorithm advances **one expansion per step**

### Visualization States

- **Discovered** → Node added to open list
- **Visited** → Node expanded (closed list)
- **Path** → Final reconstructed shortest path

---

## Performance Considerations

- **Non‑blocking algorithm** (incremental stepping)
- **No full redraw loop**

  - Redraw occurs only when:

    - grid state changes
    - UI interaction happens
    - A\* expands or updates nodes

- Custom hash for `std::pair<int, int>` to enable fast unordered containers

---

## Requirements

- **CMake ≥ 3.29**
- C++20 compiler (MSVC recommended for windows)
- **vcpkg** platform indpedenent dependency manager (manifest mode)

### Dependencies (`vcpkg.json`)

- `sfml` ≥ 3.0.2
- `tgui` ≥ 1.8.0

---

## Build Instructions

This project uses **vcpkg manifest mode**, so dependencies are installed automatically.

### 1. Install vcpkg (once)

Windows

```powershell
git clone https://github.com/microsoft/vcpkg
cd vcpkg
.\bootstrap-vcpkg.bat
```

Linux / macOS

```bash
git clone https://github.com/microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.sh
```

### 2. Configure & Build

Windows

```powershell
git clone https://github.com/JagritThukral/grid-pathfinding-visualizer
cd grid-pathfinding-visualizer

cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE=C:\path\to\vcpkg\scripts\buildsystems\vcpkg.cmake \
  -DVCPKG_TARGET_TRIPLET=x64-windows

cmake --build build --config Debug
```

Linux / macOS

```bash
git clone https://github.com/JagritThukral/grid-pathfinding-visualizer
cd grid-pathfinding-visualizer

cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake

cmake --build build --config Debug
```

> To create Release builds, replace `Debug` with `Release`.

### 3. Run

```powershell
.\build\Debug\project_pathfinding_grid.exe
```

```bash
./build/Debug/project_pathfinding_grid
```

> For Release builds, replace `Debug` with `Release`.

---

## Project Structure

```
grid-pathfinding-visualizer/
│
├─ main.cpp                # Window loop, input handling, A* stepping
│
├─ graph/
│  ├─ Graph.hpp/.cpp       # Adjacency list + heuristic
│  └─ AStarRunner.hpp/.cpp # Incremental A* implementation
│
├─ grid/
│  ├─ Cell.hpp/.cpp        # Cell state & rendering
│
├─ ui/
│  ├─ UIManager.hpp/.cpp   # TGUI panels, controls, legend
│
├─ utils/
│  ├─ Constants.hpp        # Grid size, colors, layout, directions
│  ├─ PairHash.hpp         # Hash for std::pair<int,int>
│  └─ RoundedRectangle.hpp # Custom rounded rectangle shape
│
├─ CMakeLists.txt
├─ vcpkg.json
└─ README.md
```

---

## Customization

Most visual and layout parameters can be changed in:

```
utils/Constants.hpp
```

Including:

- Grid rows & columns
- Cell size & padding
- Colors for each cell state
- UI layout and panel dimensions

---

## Troubleshooting

- **SFML / TGUI not found**

  - Ensure `-DCMAKE_TOOLCHAIN_FILE=.../vcpkg.cmake` is passed
  - Make sure vcpkg is bootstrapped

- **Runtime DLL errors**

  - Ensure vcpkg’s installed DLL directory is on `PATH`

- **Nothing redraws**

  - Rendering is event‑driven by design
  - UI actions or A\* steps must trigger redraw flags

---

## Notes

- Currently **only A\*** is implemented
- Architecture allows easy extension to:

  - Dijkstra
  - BFS / DFS
  - Weighted grids

---

Made by **Jagrit Thukral**
