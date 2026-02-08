# cub3D

A ray-casting engine inspired by the classic Wolfenstein 3D. This project renders a first-person 3D view inside a maze using ray-casting techniques, implemented in C with MiniLibX.

## 🚀 About

cub3D is a graphical project that recreates the fundamental ray-casting techniques used in early first-person shooters. The program reads a scene description from a `.cub` file and renders a dynamic 3D maze environment where players can navigate and explore.

Key aspects of the implementation:
- **Ray-casting renderer**: Textured walls with different textures per cardinal direction
- **Player movement**: Smooth controls with collision detection
- **Robust parsing**: Validates scene files with detailed error messages

## 💻 Cross-platform Support

The Makefile automatically detects and builds for **macOS** (Metal/OpenGL) and **Linux** with the appropriate MiniLibX backend.

## 📝 How to Build

To build the project, follow these steps:

```bash

# Build the project
make

# Run with a map file
./cub3D maps/default.cub
```

## 🎮 Controls

| Key | Action |
|-----|--------|
| `W` `A` `S` `D` | Move forward, left, backward, right |
| `←` `→` | Rotate view left and right |
| `ESC` | Exit the program |

Clicking the window close button will also exit cleanly.

## ✨ Features

- **Textured 3D walls**: Different textures for North, South, East, and West facing walls
- **Floor and ceiling colors**: Customizable RGB colors for floor and ceiling
- **Wall collision detection**: Players cannot walk through walls
- **Minimap overlay**: Live minimap showing player position and orientation
- **Animated player sprite**: Dynamic sprite with movement-based animation
- **Scene validation**: Comprehensive .cub file parsing with error handling

## 🗂️ Scene File Format

The `.cub` file defines the game environment with the following structure:

```
NO ./path_to_north_texture.xpm
SO ./path_to_south_texture.xpm
WE ./path_to_west_texture.xpm
EA ./path_to_east_texture.xpm

F 220,100,0
C 135,206,235

111111111
100000001
10N000001
100000001
111111111
```

**Texture identifiers:**
- `NO` — North wall texture path
- `SO` — South wall texture path  
- `WE` — West wall texture path
- `EA` — East wall texture path

**Color identifiers:**
- `F` — Floor color in RGB format (0-255)
- `C` — Ceiling color in RGB format (0-255)

**Map characters:**
- `1` — Wall
- `0` — Empty space
- `N/S/E/W` — Player starting position and orientation

**Requirements:**
- Map must be closed/surrounded by walls
- Map must be the last element in the file
- Only one player spawn point allowed
