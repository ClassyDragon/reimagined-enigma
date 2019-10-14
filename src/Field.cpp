
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

    // Initialize keys:
    for (int i = 0; i < 2; i++)
        key_pressed[i] = 0;

    for (int i = 0; i < field_width; i++)
        for (int j = 0; j < field_height; j++) {
            blocks[i][j] = new Block();
            blocks[i][j]->setTexture(textures['w']);
            blocks[i][j]->set_screen_position(sf::Vector2f(50 + (50 * i), 50 + (50 * j)));
        }

    movement_delay = new sf::Clock();

    init_rng();

    generate_piece(rng_bag[0]);    
}

Field::~Field() {
    for (std::map<char, sf::Texture*>::iterator i = textures.begin(); i != textures.end(); i++ ) 
        delete i->second;
    for (int i = 0; i < field_width; i++)
        for (int j = 0; j < field_height; j++)
            delete blocks[i][j];
    delete current_piece;
    delete movement_delay;
}

void Field::render() {
    for (int i = 0; i < field_width; i++)
        for (int j = 0; j < field_height; j++)
            blocks[i][j]->render(window);
    current_piece->render(window);
}

void Field::update() {
    update_input();
}

void Field::update_input() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        move_left();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        move_right();
    }
    else {
        key_pressed[0] = 0;
        key_pressed[1] = 0;
    }
}

void Field::init_rng() {
    srand(time(NULL));
    std::vector<int> temp_bag;
    for (int i = 0; i < 7; i++) {
        temp_bag.push_back(i);
    }

    int tempint;
    while (!temp_bag.empty()) {
        tempint = rand() % temp_bag.size();
        rng_bag.push_back(temp_bag[tempint]);
        temp_bag.erase(temp_bag.begin() + tempint);
    }
}

void Field::generate_piece(int type) {
    switch (type) {
        case 0: {
                    current_piece = new Tetramino('S', textures['r']);
                    break;
                }
        case 1: {
                    current_piece = new Tetramino('T', textures['p']);
                    break;
                }
        case 2: {
                    current_piece = new Tetramino('J', textures['b']);
                    break;
                }
        case 3: {
                    current_piece = new Tetramino('L', textures['o']);
                    break;
                }
        case 4: {
                    current_piece = new Tetramino('Z', textures['g']);
                    break;
                }
        case 5: {
                    current_piece = new Tetramino('O', textures['y']);
                    break;
                }
        case 6: {
                    current_piece = new Tetramino('I', textures['c']);
                    break;
                }
        default: {
                    current_piece = new Tetramino('I', textures['r']);
                    break;
                 }
    }
}

void Field::set_window(sf::RenderWindow* window) {
    this->window = window;
}

// Current Piece Functions:
void Field::move_left() {   
    
    if (key_pressed[0] == 0) {
        movement_delay->restart();
        current_piece->move_left();
        key_pressed[0] = 1;
    }
    if (key_pressed[0] == 1 && movement_delay->getElapsedTime().asMilliseconds() > 380) {
        current_piece->move_left();
    }
    if (key_pressed[0] == 1 && movement_delay->getElapsedTime().asMilliseconds() > 500) {
        current_piece->move_left();
        key_pressed[0] == 2;
        movement_delay->restart();
    }
    if (key_pressed[0] == 2 && movement_delay->getElapsedTime().asMilliseconds() > 200) {
        current_piece->move_left();
        movement_delay->restart();
    }
    
}

void Field::move_right() {
    if (key_pressed[1] == 0) {
        movement_delay->restart();
        current_piece->move_right();
        key_pressed[1] = 1;
    }
    if (key_pressed[1] == 1 && movement_delay->getElapsedTime().asMilliseconds() > 380) {
        current_piece->move_right();
    }
    if (key_pressed[1] == 1 && movement_delay->getElapsedTime().asMilliseconds() > 500) {
        current_piece->move_right();
        key_pressed[1] == 2;
        movement_delay->restart();
    }
    if (key_pressed[1] == 2 && movement_delay->getElapsedTime().asMilliseconds() > 200) {
        current_piece->move_right();
        movement_delay->restart();
    }
}

void Field::move_down() {
}

void Field::hard_drop() {
}

void Field::soft_drop() {
}
