
lib = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

Tetris: source.o Tetris.o Tetramino.o
	g++ *.o -o Tetris $(lib)

source.o: source.cpp
	g++ source.cpp -c $(lib) 

Tetris.o: Tetris.cpp Tetris.h
	g++ Tetris.cpp -c $(lib)

Tetramino.o: Tetramino.cpp Tetramino.h
	g++ Tetramino.cpp -c $(lib)
