BIN=game

TEXTUREh=DisplayClass/texture.h
FENETREh=DisplayClass/fenetre.h
FONCTIONSh=fonctions.h
ABUNITh=CharactersClass/AbstractUnit.h
ABPLAYERh=CharactersClass/AbstractPlayer.h
HUMPLAYERh=CharactersClass/HumanPlayer.h
ARTPLAYERh=CharactersClass/ArtificialPlayer.h
ABBUTTONh=MenuClass/AbstractButton.h

TEXTUREcpp=DisplayClass/texture.cpp
FENETREcpp=DisplayClass/fenetre.cpp
FONCTIONScpp=fonctions.cpp
ABUNITcpp=CharactersClass/AbstractUnit.cpp
ABPLAYERcpp=CharactersClass/AbstractPlayer.cpp
HUMPLAYERcpp=CharactersClass/HumanPlayer.cpp
ARTPLAYERcpp=CharactersClass/ArtificialPlayer.cpp
ABBUTTONcpp=MenuClass/AbstractButton.cpp
MAINcpp=main.cpp

$(BIN): $(TEXTUREh) $(FENETREh) $(FONCTIONSh) $(ABUNITh) $(ABPLAYERh) $(HUMPLAYERh) $(ARTPLAYERh) $(ABBUTONh) \
		$(TEXTUREcpp) $(FENETREcpp) $(FONCTIONScpp) $(ABUNITcpp) $(ABPLAYERcpp) $(HUMPLAYERcpp) $(ARTPLAYERcpp) $(ABBUTONcpp) $(MAINcpp)
	g++ -Wall -lSDL $(TEXTUREh) $(FENETREh) $(FONCTIONSh) $(ABUNITh) $(ABPLAYERh) $(HUMPLAYERh) $(ARTPLAYERh) $(ABBUTONh) \
					$(TEXTUREcpp) $(FENETREcpp) $(FONCTIONScpp) $(ABUNITcpp) $(ABPLAYERcpp) $(HUMPLAYERcpp) $(ARTPLAYERcpp) \
					$(ABBUTONcpp) $(MAINcpp) \
	-o $(BIN)
clean:
	rm -f $(BIN)