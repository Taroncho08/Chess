A classic chess game implemented in C++ using the SFML library for graphics.

# Table of Contents
- [Introduction](#introduction)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)


## Introduction
This is a simple yet fully functional chess game developed in C++ with the Simple and Fast Multimedia Library (SFML) for handling graphics and windowing. The game supports two-player mode and includes all the standard chess rules.

## Requirements
- C++ compiler (GCC, Clang, MSVC, etc.)
- SFML library (version 2.5.0 or later)

## Installation

### Linux/MacOS
1. Install SFML using your package manager:
    ```sh
    sudo apt-get install libsfml-dev # Debian/Ubuntu
    sudo dnf install sfml-devel      # Fedora
    brew install sfml                # MacOS
    ```
2. Clone the repository:
    ```sh
    git clone https://github.com/Taroncho08/Chess.git
    ```
3. Navigate to the project directory:
    ```sh
    cd Chess/
    ```
4. Build the project using CMake:
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```


### Windows
1. Download and install SFML from the [official website](https://www.sfml-dev.org/download.php).
2. Clone the repository:
    ```sh
    git clone https://github.com/Taroncho08/Chess.git
    ```
3. Navigate to the project directory:
   ```sh
    cd Chess/
    ```
4. Build the project using CMake:
    ```sh
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```


## Usage
After building the project, you can run the executable to start the game.

```sh
./Chess
