BIN=game
INSTL=../include
LIB=../lib

TEXTUREh=../DisplayClass/texture.h
FENETREh=../DisplayClass/fenetre.h
FONCTIONSh=../Fonctions/fonctions.h
UNITh=../CharactersClass/Unit.h
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
MAPh=../MapClass/map.h
CONSh=../MapClass/construction.h
POSh=../MapClass/position.h
REMPLIh=../Fonctions/remplissage.h
OBJMOBh=../MapClass/objetmobile.h
DECh=../MatriceClass/decision.h

TEXTUREcpp=../DisplayClass/texture.cpp
FENETREcpp=../DisplayClass/fenetre.cpp
FONCTIONScpp=../Fonctions/fonctions.cpp
UNITcpp=../CharactersClass/Unit.cpp
ABPLAYERcpp=../CharactersClass/AbstractPlayer.cpp
HUMPLAYERcpp=../CharactersClass/HumanPlayer.cpp
ARTPLAYERcpp=../CharactersClass/ArtificialPlayer.cpp
ABSBUTTONcpp=../MenuClass/AbstractButton.cpp
ACTBUTTONcpp=../MenuClass/ActionButton.cpp
MENUcpp=../MenuClass/Menu.cpp
MATRICEcpp=../MatriceClass/MatriceGameGestion.cpp
TERRcpp=../MapClass/terrain.cpp
TEXTEcpp=../DisplayClass/Texte.cpp
MAPcpp=../MapClass/map.cpp
CONScpp=../MapClass/construction.cpp
POScpp=../MapClass/position.cpp
REMPLIcpp=../Fonctions/remplissage.cpp
OBJMOBcpp=../MapClass/objetmobile.cpp
DECcpp=../MatriceClass/decision.cpp
MAINcpp=main.cpp

$(BIN): $(TEXTUREh) $(FENETREh) $(FONCTIONSh) $(ABUNITh) $(ABPLAYERh) \
		$(HUMPLAYERh) $(ARTPLAYERh) $(ABUTTONh) $(ACTBUTTONh) $(SUBMENUh) $(MENUh) \
		$(MATRICEh) $(TERRh) $(TEXTEh) $(MAPh) $(CONSh) $(POSh) $(REMPLIh) $(OBJMOBh) $(DECh) \
		$(TEXTUREcpp) $(FENETREcpp) $(FONCTIONScpp) $(HUMPLAYERcpp) $(ARTPLAYERcpp) $(ACTBUTTONcpp) \
		$(ABSBUTTONcpp) $(MENUcpp) $(MATRICEcpp) $(TERRcpp) $(TEXTEcpp) $(REMPLIcpp) $(MAINcpp)
	g++ -Wall -g -lSDL $(TEXTUREh) $(FENETREh) $(FONCTIONSh) $(UNITh) $(ABPLAYERh) $(HUMPLAYERh) $(ARTPLAYERh) \
				    $(ACTBUTTONh) $(ABUTONh) $(SUBMENUh) $(MENUh) $(MATRICEh) $(TERRh) $(TEXTEh) $(REMPLIh) \
					$(TEXTUREcpp) $(FENETREcpp) $(FONCTIONScpp) $(HUMPLAYERcpp) $(ABPLAYERcpp) $(UNITcpp) $(ARTPLAYERcpp) $(MENUcpp) \
					$(ABSBUTTONcpp) $(ACTBUTTONcpp) $(MATRICEcpp) $(TERRcpp) $(TEXTEcpp) $(REMPLIcpp) $(OBJMOBcpp) $(DECcpp) $(MAPcpp) $(CONScpp) $(POScpp) $(MAINcpp) \
		-I $(INSTL) \
		-L $(LIB) \
		-Wl,-rpath,$(LIB) \
	    -o $(BIN) \
	    -lSDL \
	    -lSDL_image \
	    -lSDL_ttf
clean:
	rm -f $(BIN)