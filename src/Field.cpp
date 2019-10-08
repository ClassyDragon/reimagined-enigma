
#include "Field.h"

Field::Field(sf::RenderWindow* window) : window(window) {
    textures.insert(std::pair<char, sf::Texture*>('r', new sf::Texture));
    textures.insert(std::pair<char, sf::Texture*>('p', new sf::Texture));
    textures.insert(std::pair<char, sf::Texture*>('y', new sf::Texture));
    textures.insert(std::pair<char, sf::Texture*>('g', new sf::Texture));
    textures.insert(std::pair<char, sf::Texture*>('o', new sf::Texture));
    textures.insert(std::pair<char, sf::Texture*>('b', new sf::Texture));
    textures.insert(std::pair<char, sf::Texture*>('c', new sf::Texture));
    textures.insert(std::pair<char, sf::Texture*>('w', new sf::Texture));

    // Load textures:
    textures['r']->loadFromFile("resources/red.png");
    textures['p']->loadFromFile("resources/purple.png");
    textures['y']->loadFromFile("resources/yellow.png");
    textures['g']->loadFromFile("resources/green.png");
    textures['o']->loadFromFile("resources/orange.png");
    textures['b']->loadFromFile("resources/blue.png");
    textures['c']->loadFromFile("resources/cyan.png");
    textures['w']->loadFromFile("resources/white.png");

    for (int i = 0; i < field_width; i++)
        for (int j = 0; j < field_height; j++) {
            blocks[i][j] = new Block();
            blocks[i][j]->setTexture(textures['o']);
        }
    for (int i = 0; i < field_width; i++) 
        for (int j = 0; j < field_height; j++)
            blocks[i][j]->setPosition(sf::Vector2f(50 + (50 * i), 50 + (50 * j)));
}

Field::~Field() {
    for (std::map<char, sf::Texture*>::iterator i = textures.begin(); i != textures.end(); i++ ) 
        delete i->second;
    for (int i = 0; i < field_width; i++)
        for (int j = 0; j < field_height; j++)
            delete blocks[i][j];
}

void Field::render() {
    for (int i = 0; i < field_width; i++)
        for (int j = 0; j < field_height; j++)
            blocks[i][j]->render(window);
}
