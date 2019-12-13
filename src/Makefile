lib = -lsfml-window -lsfml-system -lsfml-graphics
flags = -Wall
EXEC = Tetris
COMP = g++

$(EXEC): source.o Tetris.o Field.o Tetramino.o Block.o Sprite.o Animation.o TextureManager.o precomp.o State.o Marathon.o Menu.o
	$(COMP) $^ -o $(EXEC) $(lib)

source.o: source.cpp Tetris.o
	$(COMP) -c $<

Tetris.o: Tetris.cpp Tetris.h State.o Marathon.o
	$(COMP) -c $<

Field.o: Field.cpp Field.h Tetramino.o Block.o TextureManager.o precomp.o
	$(COMP) -c $<

Tetramino.o: Tetramino.cpp Tetramino.h Block.o precomp.o
	$(COMP) -c $<

Block.o: Block.cpp Block.h
	$(COMP) -c $<

Sprite.o: Sprite/Sprite.cpp Sprite/Sprite.h Sprite/Animation.cpp Sprite/Animation.h TextureManager.o precomp.o
	$(COMP) -c Sprite/Animation.cpp
	$(COMP) -c Sprite/Sprite.cpp

State.o: State.cpp State.h
	$(COMP) -c $<

Marathon.o: Marathon.cpp Marathon.h State.o Field.o TextureManager.o Sprite.o
	$(COMP) -c $<

Menu.o: Menu.cpp Menu.h State.o TextureManager.o
	$(COMP) -c $<

TextureManager.o: TextureManager/TextureManager.cpp TextureManager/TextureManager.h
	$(COMP) -c $<

precomp.o: Dbg_Log/Dbg_Log.cpp Dbg_Log/Dbg_Log.h
	$(COMP) -c Dbg_Log/Dbg_Log.cpp -c -o $@

clean:
	rm ./*.o ./*/*.o
