# Minesweeper
This is a program written in C++ that reads binary files, and creates the corresponding boards (1 represents bombs) to play Minesweeper on. The game utilizes SFML for graphics.

## How to play
The objective of the game is to clear the board without detonating any bombs. If a bomb is clicked, the game is over. If a tile is revealed and it is adjacent to a bomb, it will show a number indicating the number of bombs in the adjacent tiles. To win, all tiles without bombs must be revealed.

## Controls
Left click: Reveal tile

Right click: Flag tile

## Features
Three test modes: test_1, test_2, test_3.

Debug mode to reveal all bombs: debug.

Bomb counter to keep track of remaining bombs.

Reset board to a randomly generated one.

## How to run
To compile the program, run the following command in your terminal:
```
./Minesweeper
```

## Acknowledgements
This project was created as part of COP 3503 at the University of Florida. Special thanks to the course instructors for providing guidance and support.
