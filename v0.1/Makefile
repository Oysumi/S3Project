TEXTUREh=DisplayClass/texture.h
TEXTUREcpp=DisplayClass/texture.cpp
FENETREh=DisplayClass/fenetre.h
FENETREcpp=DisplayClass/fenetre.cpp
FONCTIONSh=fonctions.h
FONCTIONScpp=fonctions.cpp
MAINcpp=main.cpp
BIN=game

$(BIN): $(TEXTUREh) $(FENETREh) $(FONCTIONSh) $(TEXTUREcpp) $(FENETREcpp) $(FONCTIONScpp) $(MAINcpp)
	g++ -Wall -lSDL $(TEXTUREh) $(FENETREh) $(FONCTIONSh) $(TEXTUREcpp) $(FENETREcpp) $(FONCTIONScpp) $(MAINcpp) \
	-o $(BIN)
clean:
	rm -f $(BIN)