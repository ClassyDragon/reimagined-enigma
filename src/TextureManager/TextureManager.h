// ====================== TextureManager Class ==========================
// Author: Caleb Geyer/ClassyDragon (http://www.github.com/ClassyDragon)
// ======================================================================
// Description: A very simple Texture Manager class to be used with the
//      SFML library in C++. Provides an efficient way of loading
//      texture files that does not result in unnecessary repeat loading.
// ======================================================================
// Use:
//      1. Create a TextureManager object.
//      2. Use the load(std::string filename) method to load a new
//          texture. The class will check that a texture is not
//          loaded more than once.
//      3. Use the [] operator to access an element (returns sf::Texture*).
//          If the object is a pointer type, use the
//          get_texture(std::string key) method instead.
// ======================================================================
// Note:
//      1. If the TextureManager object is to be passed to other objects,
//          allocate it as a pointer, as the deconstructor could delete
//          the sf::Texture pointers more than once.
// ======================================================================

#pragma once

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>

const bool debug_mode = true;

class TextureManager {
    public:
        // Add a new texture to the map:
        static void load(std::string filepath);

        // Get pointer at key:
        static sf::Texture* get_texture(std::string key);
        static sf::Texture& get_texture_ref(std::string key);

        // Map Iterators:
        static std::map<std::string, sf::Texture>::iterator begin();
        static std::map<std::string, sf::Texture>::iterator end();

        // Get Size of the map:
        static int size();

        // DEBUG:
        static void Debug_Log(std::string message);

        //
        static std::map<std::string, sf::Texture> load_textures();

        // Map containing texture pointers:
        static std::map<std::string, sf::Texture> textures;
    private:
};
