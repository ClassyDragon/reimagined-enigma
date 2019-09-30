
Tetris: source.o Tetris.o
	g++ source.o Tetris.o -o Tetris -lsfml-graphics -lsfml-window -lsfml-audio

source.o: source.cpp
	g++ source.cpp -c -lsfml-graphics -lsfml-window -lsfml-audio

Tetris.o: Tetris.cpp Tetris.h
	g++ Tetris.cpp -c -lsfml-graphics -lsfml-window -lsfml-audio
