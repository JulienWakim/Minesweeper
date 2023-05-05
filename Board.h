//
// Created by Julien Wakim on 4/11/22.
//

#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <vector>


class Board {
private:
    int columns;
    int rows;
    int numOfBombs;
    int numOfFlags;
    vector<vector<Tile> > arrayBoard;
public:
    Board();
    Board(int col, int row, int bombs);
    Board(int col, int row, vector<vector<Tile> > array);
    vector<vector<Tile> >& createBoardArray();
    int getCol();
    int getRow();
    int getBombs();
    vector<vector<Tile> >& getBoardArray();
    void clearArray();
    void setBoardArray(vector<vector<Tile> >& newArray);
    void clearBombs();
    void setNumOfBombs(int num);
    void incrementNumOfBombs();
    void decrementNumOfBombs();
    void incrementNumOfFlags();
    void decrementNumOfFlags();
    int getCounter();
    void addingSurroundingTiles();
    void settingBombCounter();
    int getNumOfTileRevealed();
};


#endif //MINESWEEPER_BOARD_H
