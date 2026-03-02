# ExcalEngine - Yet Another C++ Game Engine

A Game Engine with C# Scripting. This is more of a hobby project of mine that started as a university assignment in my second semester of my first year in Software Engineering.

## Features
- Programmable Render Pipeline using OpenGL 4.6
- C# Scripting with a Bindings List (you can implement your own language bindings if you want)
- ECS based internal workflow.
- Cross Platform (Linux and Windows. Mac support might be added as a list of features for the later stages.)

## Architecture
The whole Engine is divided into 5 parts:
- ExcalCore: Core features of the whole Engine.
- ExcalRuntime: Responsible for running the game.
- ExcalBindings: C ABI bindings for the whole Engine Core.
- ExcalSharp: C# Bindings to the ExcalBindings.
- ExcalEditor: Editor Application for using ExcalCore to create games.

## Getting Started
### Requirements
- CMake >= 3.10
- C++23 compatible compiler (GCC 13+ or Clang 16+)
- .NET 8 SDK (for C# bindings)
- OpenGL 4.6 capable GPU

### Building
```bash
# Clone with submodules
git clone --recursive https://github.com/you/ExcalEngine

# Configure
cmake -B build -DCMAKE_BUILD_TYPE=Debug

# Build
cmake --build build
```

## Project Structure
- Folders:
  - Assets - Contains all user made Assets (Images, Scripts, Models, etc.)
  - Editor - Contains Editor Specific files like C# Scripts for Custom Editors, which will not be included in the final executable.
- Files:
  - .excalproj - ExcalEngine Project File, containing all dependencies and build commands.
 
## Roadmap
[x] Starting a Basic Git project :)

[ ] Basic 3D Rendering

[ ] Materials

[ ] Lighting and Shading

[ ] Simple Editor Applications

## Journal
For anyone curious, I've also attached my development journal in the `docs/` folder. It contains all the logs, documentation and development ideas that I've come up with.

## License
This project is licensed under the Apache License 2.0. See [LICENSE](LICENSE) for details.

## Contributing
For now I won't be accepting any pull requests, though some criticism would be appreciated, since this is a project for learning, just don't be too harsh, please :)
