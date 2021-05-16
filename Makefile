CC = g++
SOURCE_FILES = Transposition.cpp Board.cpp main.cpp Moves.cpp Minimax.cpp Evaluation.cpp
HEADERS = Transposition.h Board.h Legal_Moves.h Minimax.h Evaluation.h

build: $(SOURCE_FILES) $(HEADERS)
	$(CC) -O3 Board.cpp main.cpp Moves.cpp Minimax.cpp Evaluation.cpp Transposition.cpp -o engine

run: 
	./engine

clean:
	$(RM) *.o