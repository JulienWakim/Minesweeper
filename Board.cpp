//
// Created by Julien Wakim on 4/11/22.
//

#include "Board.h"
#include "Tile.h"
#include "iostream"
#include "Random.h"
using namespace std;

Board::Board() {
    columns = 0;
    rows = 0;
    numOfBombs = 0;
    numOfFlags = 0;
}

Board::Board(int col, int row, int bombs) {
    columns = col;
    rows = row;
    numOfBombs = bombs;
    numOfFlags = 0;
}

int Board::getCol(){
    return columns;
}

int Board::getRow(){
    return rows;
}

int Board::getBombs(){
    return numOfBombs;
}

vector< vector<Tile> >& Board::getBoardArray(){
    return arrayBoard;
}

vector< vector<Tile> >& Board::createBoardArray(){
    for (int i = 0; i < columns; i++) {   // for each row
        vector<Tile> colTile;
        arrayBoard.push_back(colTile);
        for (int j = 0; j < rows; j++) { // for each column
            Tile rowTile;
            arrayBoard[i].push_back(rowTile);
        }
    }
    return arrayBoard;
}

void Board::clearArray() {
    arrayBoard.clear();
}

void Board::setBoardArray(vector< vector<Tile> >& newArray){
    arrayBoard = newArray;
}

void Board::clearBombs() {
    numOfBombs = 0;
    numOfFlags = 0;
}

void Board::setNumOfBombs(int num){
    numOfBombs = num;
}

void Board::incrementNumOfBombs(){
    numOfBombs++;
}

void Board::decrementNumOfBombs(){
    numOfBombs--;
}

void Board::incrementNumOfFlags(){
    numOfFlags++;
}

void Board::decrementNumOfFlags(){
    numOfFlags--;
}

int Board::getCounter(){
    return numOfBombs - numOfFlags;
}

void Board::addingSurroundingTiles() {
    for (int i = 0; i < arrayBoard.size(); i++) {
        for (int j = 0; j < arrayBoard[i].size(); j++) {
            //TOP LEFT
            if (i == 0 && j == 0) {
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i][j + 1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i + 1][j]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i + 1][j + 1]));
            }

                //TOP RIGHT
            else if (i == 0 && j == arrayBoard[i].size() - 1) {
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i][j - 1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i + 1][j]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i + 1][j - 1]));
            }

                //BOTTOM LEFT
            else if (i == arrayBoard.size() - 1 && j == 0) {
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i - 1][j]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i][j + 1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i - 1][j + 1]));
            }

                //BOTTOM RIGHT
            else if (i == arrayBoard.size() - 1 && j == arrayBoard[i].size() - 1) {
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i - 1][j]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i][j - 1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i - 1][j - 1]));
            }

                //TOP LAYER
            else if (i == 0) {
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i][j-1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i][j+1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i+1][j-1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i+1][j+1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i+1][j]));
            }

                //LEFT COLUMN
            else if (j == 0) {
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i-1][j]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i+1][j]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i+1][j+1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i-1][j+1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i][j+1]));
            }

                //BOTTOM LAYER
            else if (i == arrayBoard.size() - 1) {
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i][j+1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i][j-1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i-1][j+1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i-1][j-1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i-1][j]));
            }

                //RIGHT COLUMN
            else if (j == arrayBoard[i].size() - 1) {
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i-1][j]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i+1][j]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i-1][j-1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i+1][j-1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i][j-1]));
            }

                //INSIDE TILES
            else{
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i-1][j-1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i-1][j]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i-1][j+1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i+1][j-1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i+1][j]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i+1][j+1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i][j-1]));
                arrayBoard[i][j].addTileToSurrounding(&(arrayBoard[i][j+1]));
            }

        }
    }

}

void Board::settingBombCounter() {
    for (int i = 0; i < arrayBoard.size(); i++) {
        for (int j = 0; j < arrayBoard[i].size(); j++) {
            arrayBoard[i][j].setNumberOfSurroundingBombs();
        }
    }
    cout << arrayBoard[0][1].getNumberOfSurroundingBombs();
}

int Board::getNumOfTileRevealed(){
    int numOfTilesRevealed = 0;
    for (int i = 0; i < arrayBoard.size(); i++) {
        for (int j = 0; j < arrayBoard[i].size(); j++) {
            if(!arrayBoard[i][j].getTileState()){
                numOfTilesRevealed++;
            }
        }
    }
    return numOfTilesRevealed;
}

