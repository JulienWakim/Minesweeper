//
// Created by Julien Wakim on 4/11/22.
//

#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;


class Tile {
private:
    sf::Sprite hidden;
    sf::Sprite revealed;
    sf::Sprite flag;
    sf::Sprite mine;
    sf::Sprite number;
    bool bomb;
    bool hide;
    bool clicked;
    bool flagged;
    vector<Tile*> surroundingTiles;
    int numOfSurroundingBombs;
    int numOfTilesRevealed;
public:
    Tile();
    sf::Sprite GetSprite();
    sf::Sprite GetBombs(bool on);
    sf::Sprite GetFlags();
    sf::Sprite GetTileNumber();
    void SetPosition(float x, float y);
    bool bombPresent();
    void setBomb();
    void revealTile();
    void clickTile();
    bool getClicked();
    void lossGameTile();
    void flagTile();
    void flagTilePermanent();
    bool getflagged();
    bool getTileState();
    void addTileToSurrounding(Tile* tile);
    vector<Tile*> surroundingTileVector();
    void setNumberOfSurroundingBombs();
    int getNumberOfSurroundingBombs();
};


#endif //MINESWEEPER_TILE_H
