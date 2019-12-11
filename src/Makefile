lib = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

Tetris: Block.o Tetris.o Tetramino.o Field.o precomp.o TextureManager.o Sprite.o Animation.o source.o
	g++ *.o -o Tetris $(lib)
	@echo "Compiled successfully!"

Tetris.o: Tetris.cpp Tetris.h Field.o Block.o Tetramino.o TextureManager.o Sprite.o
	g++ Tetris.cpp -c $(lib)

Tetramino.o: Tetramino.cpp Tetramino.h Block.o
	g++ Tetramino.cpp -c $(lib)

Block.o: Block.cpp Block.h
	g++ Block.cpp -c $(lib)

Field.o: Field.cpp Field.h Tetramino.o Block.o TextureManager.o
	g++ Field.cpp -c $(lib)

precomp.o: Dbg_Log/Dbg_Log.*
	g++ Dbg_Log/*.cpp -c -o precomp.o

TextureManager.o: TextureManager/*
	g++ TextureManager/TextureManager.cpp -c -o TextureManager.o

Sprite.o: Sprite/Sprite.* Sprite/Animation.*
	g++ Sprite/Sprite.cpp -c
	g++ Sprite/Animation.cpp -c

source.o: source.cpp
	g++ source.cpp -c $(lib) 

clean:
	rm *.o
