lib = -lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio
flags = -Wall -Wextra
EXEC = Tetris
COMP = g++

$(EXEC): source.o Tetris.o Field.o Tetramino.o Block.o Button.o Sprite.o Animation.o TextureManager.o precomp.o State.o GameState.o Marathon.o Sprint.o Menu.o
	$(COMP) $^ -o $(EXEC) $(lib) $(flags)

source.o: source.cpp Tetris.o
	$(COMP) -c $< $(flags)

Tetris.o: Tetris.cpp Tetris.h State.o Marathon.o Sprint.o Menu.o
	$(COMP) -c $< $(flags)

Field.o: Field.cpp Field.h Tetramino.o Block.o TextureManager.o precomp.o precomp.h
	$(COMP) -c $< $(flags)

Tetramino.o: Tetramino.cpp Tetramino.h Block.o precomp.o
	$(COMP) -c $< $(flags)

Block.o: Block.cpp Block.h
	$(COMP) -c $< $(flags)

Sprite.o: Sprite/Sprite.cpp Sprite/Sprite.h Sprite/Animation.cpp Sprite/Animation.h TextureManager.o precomp.o
	$(COMP) -c Sprite/Animation.cpp $(flags)
	$(COMP) -c Sprite/Sprite.cpp $(flags)

State.o: State.cpp State.h
	$(COMP) -c $< $(flags)

GameState.o: GameState.cpp GameState.h State.o Field.o TextureManager.o Sprite.o precomp.h
	$(COMP) -c $< $(flags)

Marathon.o: Marathon.cpp Marathon.h State.o GameState.o
	$(COMP) -c $< $(flags)

Sprint.o: Sprint.cpp Sprint.h State.o GameState.o
	$(COMP) -c $< $(flags)

Menu.o: Menu.cpp Menu.h State.o Button.o TextureManager.o precomp.h
	$(COMP) -c $< $(flags)

Button.o: Button.cpp Button.h
	$(COMP) -c $< $(flags)

TextureManager.o: TextureManager/TextureManager.cpp TextureManager/TextureManager.h
	$(COMP) -c $< $(flags)

precomp.o: Dbg_Log/Dbg_Log.cpp Dbg_Log/Dbg_Log.h
	$(COMP) -c Dbg_Log/Dbg_Log.cpp -c -o $@ $(flags)

clean:
	rm ./*.o
