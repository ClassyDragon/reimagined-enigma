
lib = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

Tetris: source.o Tetris.o Tetramino.o Field.o Block.o precomp.o TextureManager.o
	g++ *.o -o Tetris $(lib)

source.o: source.cpp
	g++ source.cpp -c $(lib) 

Tetris.o: Tetris.cpp Tetris.h
	g++ Tetris.cpp -c $(lib)

Tetramino.o: Tetramino.cpp Tetramino.h
	g++ Tetramino.cpp -c $(lib)

Block.o: Block.cpp Block.h
	g++ Block.cpp -c $(lib)

Field.o: Field.cpp Field.h
	g++ Field.cpp -c $(lib)

precomp.o: Dbg_Log/Dbg_Log.*
	g++ Dbg_Log/*.cpp -c -o precomp.o

TextureManager.o: TextureManager/*
	g++ TextureManager/TextureManager.cpp -c -o TextureManager.o

clean:
	rm *.o
