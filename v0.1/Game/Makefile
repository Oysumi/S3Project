BIN=game
INSTL=../include
LIB=../lib

TEXTUREh=../DisplayClass/texture.h
FENETREh=../DisplayClass/fenetre.h
FONCTIONSh=../Fonctions/fonctions.h
ABUNITh=../CharactersClass/AbstractUnit.h
ABPLAYERh=../CharactersClass/AbstractPlayer.h
HUMPLAYERh=../CharactersClass/HumanPlayer.h
ARTPLAYERh=../CharactersClass/ArtificialPlayer.h
ABUTTONh=../MenuClass/AbstractButton.h
ACTBUTTONh=../MenuClass/ActionButton.h
SUBMENUh=../MenuClass/SubMenuButton.h
MENUh=../MenuClass/Menu.h
MATRICEh=../MatriceClass/MatriceGameGestion.h
TERRh=../MapClass/terrain.h
TEXTEh=../DisplayClass/Texte.h

TEXTUREcpp=../DisplayClass/texture.cpp
FENETREcpp=../DisplayClass/fenetre.cpp
FONCTIONScpp=../Fonctions/fonctions.cpp
HUMPLAYERcpp=../CharactersClass/HumanPlayer.cpp
ARTPLAYERcpp=../CharactersClass/ArtificialPlayer.cpp
ABSBUTTONcpp=../MenuClass/AbstractButton.cpp
ACTBUTTONcpp=../MenuClass/ActionButton.cpp
MENUcpp=../MenuClass/Menu.cpp
MATRICEcpp=../MatriceClass/MatriceGameGestion.cpp
TERRcpp=../MapClass/terrain.cpp
TEXTEcpp=../DisplayClass/Texte.cpp
MAINcpp=main.cpp

$(BIN): $(TEXTUREh) $(FENETREh) $(FONCTIONSh) $(ABUNITh) $(ABPLAYERh) \
		$(HUMPLAYERh) $(ARTPLAYERh) $(ABUTTONh) $(ACTBUTTONh) $(SUBMENUh) $(MENUh) \
		$(MATRICEh) $(TERRh) $(TEXTEh)\
		$(TEXTUREcpp) $(FENETREcpp) $(FONCTIONScpp) $(HUMPLAYERcpp) $(ARTPLAYERcpp) $(ACTBUTTONcpp) \
		$(ABSBUTTONcpp) $(MENUcpp) $(MATRICEcpp) $(TERRcpp) $(TEXTEcpp) $(MAINcpp)
	g++ -Wall -g -lSDL $(TEXTUREh) $(FENETREh) $(FONCTIONSh) $(ABUNITh) $(ABPLAYERh) $(HUMPLAYERh) $(ARTPLAYERh) \
				    $(ACTBUTTONh) $(ABUTONh) $(SUBMENUh) $(MENUh) $(MATRICEh) $(TERRh) $(TEXTEh) \
					$(TEXTUREcpp) $(FENETREcpp) $(FONCTIONScpp) $(HUMPLAYERcpp) $(ARTPLAYERcpp) $(MENUcpp) \
					$(ABSBUTTONcpp) $(ACTBUTTONcpp) $(MATRICEcpp) $(TERRcpp) $(TEXTEcpp) $(MAINcpp) \
		-I $(INSTL) \
		-L $(LIB) \
		-Wl,-rpath,$(LIB) \
	    -o $(BIN) \
	    -lm -lSDL_mixer \
	    -lSDL \
	    -lSDL_image \
	    -lSDL_ttf
clean:
	rm -f $(BIN)