# reimagined-enigma
Simple open-source Tetris Game made using C++ and the SFML Library.

__Current Version: v1.0__
1. Finally released!
2. Added sound effects for dropping and line clearing.
3. Many under-the-hood changes to the engine to make the project easily expandable.

__Previous Versions__

**v1.0.7b**

Changes:
1. New Sprint Mode.
2. Buttons on menu show description when hovering over them.
3. State class now has a pure virtual destructor.
4. TetrisGame class now has a destructor to delete current state.
5. Added pause menu that opens in game when pressing the Esc key.
6. High score tracking!
    - High scores for each mode are currently stored under __save/highscores.txt__.
7. Many structural changes to how to engine works:
    - Marathon and Sprint mode now inherit from a GameState class.
    - Tetramino types are now stored as an integer, classified by an enum, as opposed to a char.

**v1.0.6b**

Changes:
1. Added the rest of the missing pentominoes.
2. Changed the colors of some pentominoes.

**v1.0.5b**
Changes:
1. Added missing pentominoes.
2. Fixed hold piece generating incorrect pieces for some pentaminoes.

**v1.0.4b**
Changes:
1. Added buttons to menu.
2. Marathon has new options:
    - Tetromino mode: Play with the standard Tetrominoes
    - Pentomino mode: Play with the 5-block Pentominoes
    - Both mode: Play with all the pieces!


![Screenshot](media/screenshot2.png)

## Current Progress:
* Piece movement and rotation.
* Line clearing and clear animation.
* Super Rotation System! (kinda...)
* Score and total line clears displayed.
* Next Piece queue and hold piece!
* Ability for users to easily add new pieces... (like pentaminos!)
* State system for menus, modes, etc.
* Levels with varying speeds.

## TO-DO:
1. More game modes.
2. High score keeping.
3. Music and SFX! :D

## BUGS:
1. Ghost Piece does not account for spins.

## Needs Improved:
1. Representation of solid tiles in field.
