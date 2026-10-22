# Cellular Automaton

This is a collection of cellular automaton implementations that I have made.

## Predator and Prey
The world is grid of cells, with 3 possibilities: Predator(Red), Prey(Green), or Empty(Black).

Both predator and prey have a set health, that changes over time.

The simulation works in steps, with the following rules:

    -For prey:
        -Tries to move in a random direction.
        -Health increases.
        -When health reaches a threshold:
            -They will reproduce, creating a new "Prey"
            -Their health resets to 1

    -For predator:
        -Tries to move in a random direction.
        -Health decreases.
        -When health reaches 0, they die and turn into "Nothing".
        -If the adjacent square is a prey:
            -They will eat it, turning it into a "predator" (reproducing)
            -Their health will increase by the amount of health the eaten prey had
            
           
 ![Image](http://i.imgur.com/ufXdrSz.png)

## Langton's Ant

Squares on a plane are colored variously either black or white. We arbitrarily identify one square as the "ant". The ant can travel in any of the four cardinal directions at each step it takes. The "ant" moves according to the rules below:

At a white square, turn 90° right, flip the color of the square, move forward one unit
At a black square, turn 90° left, flip the color of the square, move forward one unit

## Game of Life

    The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells, 
    each of which is in one of two possible states, alive or dead, or "populated" or "unpopulated". 
    Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or 
    diagonally adjacent. At each step in time, the following transitions occur:

 - Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
 - Any live cell with two or three live neighbours lives on to the next generation.
 - Any live cell with more than three live neighbours dies, as if by overpopulation.
 - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 
## Brian's Brain

Brian's brain has 3 cell types: On, Off, and dying. 

Each generation:
    -On cells go into a dying state
    -Dying cells go into the off state
    -Off cells go into an on state, if and only if exactly 2 [Moore's] neighbours are in the On state


## Wireworld

Wire world is a little different in the way I allow the editing of a circuit before actually running the program.



## Building and Running

### Windows (Visual Studio)

The easiest way to build is to use [vcpkg](https://vcpkg.io/en/index.html) and install dependencies through this.

```bash
vcpkg install sfml
vcpkg install imgui
vcpkg integrate install
```

Then open the Visual Studio project file to build and run.

### Linux

#### Pre-requisites

Install Vcpkg and other required packages using your distribution's package manager:

```sh
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh

# These are required to build some packages
sudo apt install cmake make autoconf libtool pkg-config

# The following are required for SFML
sudo apt install libx11-dev xorg-dev freeglut3-dev libudev-dev
```

Ensure paths are set correctly:

```sh
export VCPKG_ROOT=/path/to/vcpkg
export PATH=$VCPKG_ROOT:$PATH
```

RECOMMENDED: Add the above lines to your `.bashrc` or `.zshrc` file:

```sh
echo 'export VCPKG_ROOT=/path/to/vcpkg' >> ~/.bashrc
echo 'export PATH=$VCPKG_ROOT:$PATH' >> ~/.bashrc
```

#### Build and Run

To build, at the root of the project:

```sh
vcpkg install # First time only
sh scripts/build.sh
```

To run, at the root of the project:

```sh
sh scripts/run.sh
```

To build and run in release mode, simply add the `release` suffix:

```sh
sh scripts/build.sh release
sh scripts/run.sh release
```
