BIN=game
INSTL=../include
LIB=../lib

TEXTUREh=../DisplayClass/texture.h
FENETREh=../DisplayClass/fenetre.h
FONCTIONSh=../Fonctions/fonctions.h
UNITh=../MapObject/Unit.h
ABPLAYERh=../PlayerClass/AbstractPlayer.h
HUMPLAYERh=../PlayerClass/HumanPlayer.h
ARTPLAYERh=../PlayerClass/ArtificialPlayer.h
ABUTTONh=../MenuClass/AbstractButton.h
ACTBUTTONh=../MenuClass/ActionButton.h
SUBMENUh=../MenuClass/SubMenuButton.h
MENUh=../MenuClass/Menu.h
MATRICEh=../MatriceClass/MatriceGameGestion.h
TERRh=../MapClass/terrain.h
TEXTEh=../DisplayClass/Texte.h
MAPh=../MapClass/map.h
CONSh=../MapObject/construction.h
POSh=../MapClass/position.h
REMPLIh=../Fonctions/remplissage.h
OBJMOBh=../MapObject/mapobject.h
DECh=../MatriceClass/decision.h
SELh=../MatriceClass/selection.h

TEXTUREcpp=../DisplayClass/texture.cpp
FENETREcpp=../DisplayClass/fenetre.cpp
FONCTIONScpp=../Fonctions/fonctions.cpp
UNITcpp=../MapObject/Unit.cpp
ABPLAYERcpp=../PlayerClass/AbstractPlayer.cpp
HUMPLAYERcpp=../PlayerClass/HumanPlayer.cpp
ARTPLAYERcpp=../PlayerClass/ArtificialPlayer.cpp
ABSBUTTONcpp=../MenuClass/AbstractButton.cpp
ACTBUTTONcpp=../MenuClass/ActionButton.cpp
MENUcpp=../MenuClass/Menu.cpp
MATRICEcpp=../MatriceClass/MatriceGameGestion.cpp
TERRcpp=../MapClass/terrain.cpp
TEXTEcpp=../DisplayClass/Texte.cpp
MAPcpp=../MapClass/map.cpp
CONScpp=../MapObject/construction.cpp
POScpp=../MapClass/position.cpp
REMPLIcpp=../Fonctions/remplissage.cpp
OBJMOBcpp=../MapObject/mapobject.cpp
DECcpp=../MatriceClass/decision.cpp
SELcpp=../MatriceClass/selection.cpp
MAINcpp=main.cpp

$(BIN): $(TEXTUREh) $(FENETREh) $(FONCTIONSh) $(ABUNITh) $(ABPLAYERh) \
		$(HUMPLAYERh) $(ARTPLAYERh) $(ABUTTONh) $(ACTBUTTONh) $(SUBMENUh) $(MENUh) \
		$(MATRICEh) $(TERRh) $(TEXTEh) $(MAPh) $(CONSh) $(POSh) $(REMPLIh) $(OBJMOBh) $(DECh) $(SELh) \
		$(TEXTUREcpp) $(FENETREcpp) $(FONCTIONScpp) $(HUMPLAYERcpp) $(ARTPLAYERcpp) $(ACTBUTTONcpp) \
		$(ABSBUTTONcpp) $(MENUcpp) $(MATRICEcpp) $(TERRcpp) $(TEXTEcpp) $(REMPLIcpp) $(MAINcpp)
	g++ -Wall -g -lSDL $(TEXTUREh) $(FENETREh) $(FONCTIONSh) $(UNITh) $(ABPLAYERh) $(HUMPLAYERh) $(ARTPLAYERh) \
				    $(ACTBUTTONh) $(ABUTONh) $(SUBMENUh) $(MENUh) $(MATRICEh) $(TERRh) $(TEXTEh) $(REMPLIh) \
					$(TEXTUREcpp) $(FENETREcpp) $(FONCTIONScpp) $(HUMPLAYERcpp) $(ABPLAYERcpp) $(UNITcpp) $(ARTPLAYERcpp) $(MENUcpp) \
					$(ABSBUTTONcpp) $(ACTBUTTONcpp) $(MATRICEcpp) $(TERRcpp) $(TEXTEcpp) $(REMPLIcpp) $(OBJMOBcpp) $(DECcpp) $(SELcpp) $(MAPcpp) $(CONScpp) $(POScpp) $(MAINcpp) \
		-I $(INSTL) \
		-L $(LIB) \
		-Wl,-rpath,$(LIB) \
	    -o $(BIN) \
	    -lSDL \
	    -lSDL_image \
	    -lSDL_ttf
clean:
	rm -f $(BIN)