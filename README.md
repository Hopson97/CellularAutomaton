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