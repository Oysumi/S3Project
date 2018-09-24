BIN=game

TEXTUREh=DisplayClass/texture.h
FENETREh=DisplayClass/fenetre.h
FONCTIONSh=fonctions.h
ABUNITh=CharactersClass/AbstractUnit.h
ABPLAYERh=CharactersClass/AbstractPlayer.h
HUMPLAYERh=CharactersClass/HumanPlayer.h
ARTPLAYERh=CharactersClass/ArtificialPlayer.h
ABUTTONh=MenuClass/AbstractButton.h
ACTBUTTONh=MenuClass/ActionButton.h
SUBMENUh=MenuClass/SubMenuButton.h
MENUh=MenuClass/Menu.h
MATRICEh=MatriceClass/MatriceGameGestion.h
TERRh=MapClass/terrain.h

TEXTUREcpp=DisplayClass/texture.cpp
FENETREcpp=DisplayClass/fenetre.cpp
FONCTIONScpp=fonctions.cpp
HUMPLAYERcpp=CharactersClass/HumanPlayer.cpp
ARTPLAYERcpp=CharactersClass/ArtificialPlayer.cpp
ABUTTONcpp=MenuClass/AbstractButton.cpp
ACTBUTTONcpp=MenuClass/ActionButton.cpp
MENUcpp=MenuClass/Menu.cpp
TERRcpp=MapClass/terrain.cpp
MAINcpp=main.cpp

$(BIN): $(TEXTUREh) $(FENETREh) $(FONCTIONSh) $(ABUNITh) $(ABPLAYERh) \
		$(HUMPLAYERh) $(ARTPLAYERh) $(ABUTTONh) $(ACTBUTTONh) $(SUBMENUh) $(MENUh) \
		$(MATRICEh) $(TERRh) \
		$(TEXTUREcpp) $(FENETREcpp) $(FONCTIONScpp) $(HUMPLAYERcpp) $(ARTPLAYERcpp) $(ABUTTONcpp) $(ACTBUTTONcpp) \
		$(MENUcpp) $(TERRcpp) $(MAINcpp)
	g++ -Wall -lSDL $(TEXTUREh) $(FENETREh) $(FONCTIONSh) $(ABUNITh) $(ABPLAYERh) $(HUMPLAYERh) $(ARTPLAYERh) \
				    $(ABUTTONcpp) $(ACTBUTTONh) $(ABUTONh) $(SUBMENUh) $(MENUh) $(MATRICEh) $(TERRh) \
					$(TEXTUREcpp) $(FENETREcpp) $(FONCTIONScpp) $(HUMPLAYERcpp) $(ARTPLAYERcpp) $(MENUcpp) \
					$(ACTBUTTONcpp) $(TERRcpp) $(MAINcpp) \
	-o $(BIN)
clean:
	rm -f $(BIN)