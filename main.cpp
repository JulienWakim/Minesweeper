#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Board.h"
#include "Random.h"
#include "TextureManager.h"
using namespace std;

Board readFile(string file);
void setBombs(vector< vector<Tile> >& boardArray, Board& board);
vector< vector<Tile> > readTestFile(string file, vector<vector<Tile> >& blankArray, Board& board);
void setPositiionTiles(vector<vector<Tile> >& tiles);
void restartBoard(Board& board, vector<vector<Tile> >& tiles);
void settingBombCounter(vector<vector<Tile> >& tiles);


Board readFile(string file){
    ifstream inFile(file);
    string columns;
    string rows;
    string numOfBombs;
    getline(inFile, columns);
    getline(inFile, rows);
    getline(inFile, numOfBombs);
    int intCol = stoi(columns);
    int intRow = stoi(rows);
    int intBomb = stoi(numOfBombs);
    Board mainBoard = Board(intCol, intRow, intBomb);
    return mainBoard;
}
void setBombs(vector<vector<Tile> >& boardArray, Board& board){
    int bombsPlaced = 0;
    while (bombsPlaced!=board.getBombs()) {
        int x = Random::Int(0, board.getCol()-1);
        int y = Random::Int(0, board.getRow()-1);
        if (!boardArray[x][y].bombPresent()) {
            boardArray[x][y].setBomb();
            bombsPlaced++;
        }
    }
}
vector<vector<Tile> > readTestFile(string file, vector<vector<Tile> >& blankArray, Board& board){
    ifstream inFile(file);
    string lineInFile;
    int row = 0;
    int numOfBombs = 0;
    while(getline(inFile, lineInFile)){
        for (int i = 0; i < lineInFile.size(); i++) {
            char num = lineInFile[i];
            if(num == '1'){
                blankArray[i][row].setBomb();
                numOfBombs++;
            }
        }
        row++;
    }
    board.setNumOfBombs(numOfBombs);
    return blankArray;
}
void setPositiionTiles(vector<vector<Tile> >& tiles){
    for (int i = 0; i < tiles.size(); i++) {   // for each row
        for (int j = 0; j < tiles[i].size(); j++) { // for each column
            tiles[i][j].SetPosition(i*32,j*32);
        }
    }
}
void restartBoard(Board& board, vector<vector<Tile> >& tiles){
    board.clearArray();
    tiles.clear();
    board.clearBombs();
    tiles = board.createBoardArray();
    setPositiionTiles(tiles);
}
void settingBombCounter(vector<vector<Tile> >& tiles){
    for (int i = 0; i < tiles.size(); i++) {
        for (int j = 0; j < tiles[i].size(); j++) {
            tiles[i][j].setNumberOfSurroundingBombs();
        }
    }
}

int main()
{
    Board configBoard = readFile("boards/config.cfg");
    int configNumberOfBombs = configBoard.getBombs();
    sf::RenderWindow window(sf::VideoMode(configBoard.getCol() * 32, configBoard.getRow() * 32 +100), "Minesweeper");

    //FACE CODE
    sf::Sprite face;
    face.setPosition(configBoard.getCol() * 32/2 - 32, configBoard.getRow() * 32);
    bool gameCont = true;
    bool win, lose = false;
    bool newGame = false;
    if(gameCont){
        face.setTexture(TextureManager::GetTexture("face_happy"));
    }


    //TEST CODE
    sf::Sprite test1;
    sf::Sprite test2;
    sf::Sprite test3;
    test1.setPosition(configBoard.getCol() * 32/2 +(32*5), configBoard.getRow() * 32);
    test2.setPosition(configBoard.getCol() * 32/2 +(32*7), configBoard.getRow() * 32);
    test3.setPosition(configBoard.getCol() * 32/2 +(32*9), configBoard.getRow() * 32);
    test1.setTexture(TextureManager::GetTexture("test_1"));
    test2.setTexture(TextureManager::GetTexture("test_2"));
    test3.setTexture(TextureManager::GetTexture("test_3"));
    bool text1 = false;
    bool text2 = false;
    bool text3 = false;

    //DEBUG CODE
    sf::Sprite debug;
    debug.setPosition(configBoard.getCol() * 32/2 + (32*3), configBoard.getRow() * 32);
    debug.setTexture(TextureManager::GetTexture("debug"));
    bool debugSwitch = false;

    //Bomb Counter
    sf::Sprite digit1;
    sf::Sprite digit2;
    sf::Sprite digit3;
    sf::Sprite digit4;
    digit1.setPosition(0, configBoard.getRow() * 32);
    digit2.setPosition(21, configBoard.getRow() * 32);
    digit3.setPosition(42, configBoard.getRow() * 32);
    digit4.setPosition(63, configBoard.getRow() * 32);
    digit1.setTexture(TextureManager::GetTexture("digits"));
    digit2.setTexture(TextureManager::GetTexture("digits"));
    digit3.setTexture(TextureManager::GetTexture("digits"));
    digit4.setTexture(TextureManager::GetTexture("digits"));

    vector< vector<Tile> >& tiles = configBoard.createBoardArray();
    setPositiionTiles(tiles);
    setBombs(tiles, configBoard);
    configBoard.addingSurroundingTiles();
    settingBombCounter(tiles);

     //run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::MouseButtonReleased){
                if(!win && !lose){
                    if (event.mouseButton.button == sf::Mouse::Right){
                        for (int i = 0; i < tiles.size(); i++) {
                            for (int j = 0; j < tiles[i].size(); j++) {
                                sf::FloatRect tileButton = tiles[i][j].GetSprite().getGlobalBounds();
                                if (tileButton.contains(mousePosition.x, mousePosition.y)) {
                                    if(tiles[i][j].getTileState()) {
                                        tiles[i][j].flagTile();
                                        if (tiles[i][j].getflagged()) {
                                            configBoard.incrementNumOfFlags();
                                        } else {
                                            configBoard.decrementNumOfFlags();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if (event.mouseButton.button == sf::Mouse::Left){

                    //WIN OR LOSE
                    if(win || lose){
                        sf::FloatRect newGameButton = face.getGlobalBounds();
                        sf::FloatRect test1Button = test1.getGlobalBounds();
                        sf::FloatRect test2Button = test2.getGlobalBounds();
                        sf::FloatRect test3Button = test3.getGlobalBounds();
                        if (newGameButton.contains(mousePosition.x, mousePosition.y)){
                            newGame = true;
                            text3 = false;
                            text2 = false;
                            text1 = false;
                            lose = false;
                            win = false;
                            face.setTexture(TextureManager::GetTexture("face_happy"));
                        }
                        else if (test1Button.contains(mousePosition.x, mousePosition.y)){
                            if(text1 == false){
                                text1 = true;
                            }
                            text2 = false;
                            text3 = false;
                            lose = false;
                            win = false;
                            face.setTexture(TextureManager::GetTexture("face_happy"));
                        }

                        else if (test2Button.contains(mousePosition.x, mousePosition.y)){
                            if(text2 == false){
                                text2 = true;
                            }
                            text3= false;
                            text1 = false;
                            lose = false;
                            win = false;
                            face.setTexture(TextureManager::GetTexture("face_happy"));
                        }
                        else if (test3Button.contains(mousePosition.x, mousePosition.y)){
                            if(text3 == false){
                                text3 = true;
                            }
                            text2 = false;
                            text1 = false;
                            lose = false;
                            win = false;
                            face.setTexture(TextureManager::GetTexture("face_happy"));
                        }
                        else{
                            continue;
                        }
                    }

                    //DEBUG BUTTON
                    sf::FloatRect debugButton = debug.getGlobalBounds();
                    if (debugButton.contains(mousePosition.x, mousePosition.y)){
                        debugSwitch = !debugSwitch;
                    }

                    //TEST BUTTONS
                    sf::FloatRect test1Button = test1.getGlobalBounds();
                    if (test1Button.contains(mousePosition.x, mousePosition.y)){
                        if(text1 == false){
                            text1 = true;
                        }
                        text2 = false;
                        text3 = false;
                    }

                    sf::FloatRect test2Button = test2.getGlobalBounds();
                    if (test2Button.contains(mousePosition.x, mousePosition.y)){
                        if(text2 == false){
                            text2 = true;
                        }
                        text3= false;
                        text1 = false;
                    }

                    sf::FloatRect test3Button = test3.getGlobalBounds();
                    if (test3Button.contains(mousePosition.x, mousePosition.y)){
                        if(text3 == false){
                            text3 = true;
                        }
                        text2 = false;
                        text1 = false;
                    }

                    //New Game
                    sf::FloatRect newGameButton = face.getGlobalBounds();
                    if (newGameButton.contains(mousePosition.x, mousePosition.y)){
                        newGame = true;
                        text3 = false;
                        text2 = false;
                        text1 = false;
                    }

                    //TILE
                    for (int i = 0; i < tiles.size(); i++) {
                        for (int j = 0; j < tiles[i].size(); j++) {
                            sf::FloatRect tileButton = tiles[i][j].GetSprite().getGlobalBounds();
                            if (tileButton.contains(mousePosition.x, mousePosition.y)){
                                if(tiles[i][j].getflagged()){
                                    continue;
                                }
                                tiles[i][j].revealTile();
                                if(tiles[i][j].bombPresent() && !tiles[i][j].getClicked()){
                                    tiles[i][j].clickTile();
                                    lose = true;
                                }
                            }
                        }
                    }
                }
            }
        }


        window.clear();


        if(lose){
            for (int i = 0; i < tiles.size(); i++) {
                for (int j = 0; j < tiles[i].size(); j++) {
                    tiles[i][j].lossGameTile();
                    window.draw(tiles[i][j].GetSprite());
                    window.draw(tiles[i][j].GetFlags());
                    window.draw(tiles[i][j].GetBombs(debugSwitch));
                }
            }
        }
        else if(win){
            for (int i = 0; i < tiles.size(); i++) {
                for (int j = 0; j < tiles[i].size(); j++) {
                    if(tiles[i][j].bombPresent()){
                        tiles[i][j].flagTilePermanent();
                    }
                    window.draw(tiles[i][j].GetSprite());
                    window.draw(tiles[i][j].GetTileNumber());
                }
            }
        }
        else {
            for (int i = 0; i < tiles.size(); i++) {
                for (int j = 0; j < tiles[i].size(); j++) {
                        window.draw(tiles[i][j].GetSprite());
                        window.draw(tiles[i][j].GetFlags());
                        window.draw(tiles[i][j].GetTileNumber());
                        if(debugSwitch) {
                            window.draw(tiles[i][j].GetBombs(debugSwitch));
                        }
                }
            }
        }

        if(text1){
            restartBoard(configBoard, tiles);
            tiles = readTestFile("boards/testboard1.brd", tiles, configBoard);
            configBoard.addingSurroundingTiles();
            settingBombCounter(tiles);
            text1 = false;
        }

        else if(text2){
            restartBoard(configBoard, tiles);
            tiles = readTestFile("boards/testboard2.brd", tiles, configBoard);
            configBoard.addingSurroundingTiles();
            settingBombCounter(tiles);
            text2 = false;
        }

        else if(text3){
            restartBoard(configBoard, tiles);
            tiles = readTestFile("boards/testboard3.brd", tiles, configBoard);
            configBoard.addingSurroundingTiles();
            settingBombCounter(tiles);
            text3 = false;
        }

        else if(newGame){
            restartBoard(configBoard, tiles);
            configBoard.setNumOfBombs(configNumberOfBombs);
            setBombs(tiles, configBoard);
            configBoard.addingSurroundingTiles();
            settingBombCounter(tiles);
            newGame = false;
        }

        //BOMB COUNTER
        int counter = configBoard.getCounter();
        string strNumOfBombs = "" + (configBoard.getCounter());
        int multiplier = 0;
        int temp = 0;
        if(win){
            counter = 0;
        }
        if(counter < 0){
           digit1.setTextureRect(sf::IntRect(210, 0, 21, 32));
            counter = abs(counter);
        }
        else{
            digit1.setTextureRect(sf::IntRect(0,0,0,0));
        }
        multiplier = counter/100;
        digit2.setTextureRect(sf::IntRect(multiplier*21, 0, 21, 32));
        temp = counter % 100;
        multiplier = temp/10;
        digit3.setTextureRect(sf::IntRect(multiplier*21, 0, 21, 32));
        temp = counter % 10;
        digit4.setTextureRect(sf::IntRect(temp*21, 0, 21, 32));

        if(configBoard.getNumOfTileRevealed() == (tiles[0].size() * tiles.size()) - configBoard.getBombs()){
            win = true;
        }

        //WIN
        if(win){
            face.setTexture(TextureManager::GetTexture("face_win"));
        }

        //LOSE
        if(lose){
            face.setTexture(TextureManager::GetTexture("face_lose"));
        }

        window.draw(face);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);
        window.draw(debug);
        window.draw(digit1);
        window.draw(digit2);
        window.draw(digit3);
        window.draw(digit4);




        window.display();


    }

    return 0;
}
