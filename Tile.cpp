//
// Created by Julien Wakim on 4/11/22.
//

#include "Tile.h"
#include "TextureManager.h"
#include <iostream>

using namespace std;

Tile::Tile() {
    bomb = false;
    hidden.setTexture(TextureManager::GetTexture("tile_hidden"));
    revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
    flag.setTexture(TextureManager::GetTexture("flag"));
    mine.setTexture(TextureManager::GetTexture("mine"));
    hide = true;
    clicked = false;
    flagged = false;
    numOfSurroundingBombs = 0;
    numOfTilesRevealed = 0;
}

sf::Sprite Tile::GetSprite() {
    if(hide){
        return hidden;
    }
    else{
        return revealed;
    }

}

void Tile::SetPosition(float x, float y) {
    hidden.setPosition(x,y);
    revealed.setPosition(x,y);
    flag.setPosition(x,y);
    mine.setPosition(x,y);
    number.setPosition(x,y);
}

bool Tile::bombPresent(){
    return bomb;
}

void Tile::setBomb(){
    bomb = true;
    surroundingTiles.clear();
}

sf::Sprite Tile::GetBombs(bool on){
    if(on && bomb){
        return mine;
    }
    else if(!hide && bomb){
        return mine;
    }
    else if(flagged){
        return flag;
    }
    else if(hide){
        return hidden;
    }
    else{
        return GetTileNumber();
    }
}

sf::Sprite Tile::GetFlags(){
    if(flagged){
        return flag;
    }
    else if(!hide && bomb){
        return mine;
    }
    else if(hide){
        return hidden;
    }
    else{
        return revealed;
    }
}


void Tile::revealTile() {
    hide = false;
    if(!bomb && numOfSurroundingBombs == 0) {
        for (int i = 0; i < surroundingTiles.size(); i++) {
            if (!surroundingTiles[i]->flagged && !surroundingTiles[i]->bomb && surroundingTiles[i]->hide) {
                if (surroundingTiles[i]->numOfSurroundingBombs == 0) {
                    surroundingTiles[i]->hide = false;
                    surroundingTiles[i]->revealTile();
                } else {
                    surroundingTiles[i]->hide = false;
                }
            }
        }
    }
}

void Tile::clickTile(){
    clicked = true;
}

bool Tile::getClicked(){
    return clicked;
}

void Tile::lossGameTile(){
    if(bomb){
        hide = false;
    }
}

void Tile::flagTile() {
    flagged = !flagged;
}

bool Tile::getflagged(){
    return flagged;
}

bool Tile::getTileState(){
    return hide;
}

void Tile::addTileToSurrounding(Tile* tile){
    surroundingTiles.push_back(tile);
}

vector<Tile*> Tile::surroundingTileVector(){
    return surroundingTiles;
}

sf::Sprite Tile::GetTileNumber(){
    if(flagged){
        return flag;
    }
    else if(hide){
        return hidden;
    }
    if(numOfSurroundingBombs == 0){
        return revealed;
    }
    string file = "number_" + to_string(numOfSurroundingBombs);
    number.setTexture(TextureManager::GetTexture(file));
    return number;
}

void Tile::setNumberOfSurroundingBombs() {
    for(int i = 0; i < surroundingTiles.size(); i++){
        if(surroundingTiles[i]->bomb){
            numOfSurroundingBombs++;
        }
    }
}

int Tile::getNumberOfSurroundingBombs(){
    return numOfSurroundingBombs;
}

void Tile::flagTilePermanent(){
    flagged = true;
}
