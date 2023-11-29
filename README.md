> [!WARNING]
> This README file is under construction and could contain misinformation.

# Void Engine
Void Engine is a C++ Game Engine developed as a learning project to explore C++, handle larger codebases, and integrate multiple external libraries.

<br/>

## Table of Contents
- [Features](#features)
- [Getting Started](#getting-started)
- [Dependencies](#dependencies)
- [Building from Source](#building-from-source)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

<br/>

## Features  
### ECS Architecture
Utilizes the ENTT library and aims to develop a custom ECS system.

### Graphics
Leverages OpenGL, GLFW, and GLAD for powerful graphics capabilities.

### Physics System
Incorporates a self-created physics system with support for Mesh, Sphere, and Box collision and response.

### Model Loading
Utilizes ASSIMP for efficient loading of 3D models.

### Audio Programming
Implements FMOD for audio functionality.

### Graphical Development Environment
Features the beginning of a graphical development environment named Nebula, utilizing IMGUI.

### External File Parsing
Supports JSON file parsing with the help of NLOHMANN.

### Build System
Uses Premake5 for solution and project management.

### Logging Solution
Integrates SPDLOG for effective logging.

<br/>

## Getting Started
To get started with Void Engine, follow these steps:

Clone the Repository:

``` bash
git clone https://github.com/your-username/void-engine.git
cd void-engine
Build the Engine:
```

``` bash
premake5 [platform]
make
Replace [platform] with your target platform (e.g., vs2019, xcode, etc.).
```

Run a Sample Application:

bash
Copy code
cd bin
./VoidSample
This will run a sample application using Void Engine.

<br/>

## Dependencies
Void Engine relies on the following external libraries:

- ENTT
- OpenGL
- GLFW
- GLAD
- ASSIMP
- FMOD
- IMGUI
- NLOHMANN JSON
- Premake5
- SPDLOG

<br/>

## Building from Source
...

<br/>

## Usage
...

<br/>

## Contributing
...

<br/>

## License
This project is licensed under the MIT License.

