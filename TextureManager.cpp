//
// Created by Julien Wakim on 4/12/22.
//
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;
#include "TextureManager.h"

//Redeclare the variable so this file knows it exists and can use it
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string textureName) {
    string path = "images/";
    path += textureName + ".png";

    textures[textureName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName) {

    //if the texture doesn't exist.. load first than return it
    if(textures.find(textureName) == textures.end()) { //we didnt find it
        LoadTexture(textureName);
    }
    return textures[textureName];
}

void TextureManager::Clear() {
    textures.clear(); //Gets rid of all stored objects
}
