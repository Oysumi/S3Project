#ifndef __REMPLISSAGE_H__
#define __REMPLISSAGE_H__

#include "../MenuClass/ActionButton.h"
#include <vector>

/* Sert exclusivement à la création des boutons pour les menus
 * permet alors un accès direct aux cases et donc à la libération
 * de ces dernières */

std::vector<AbstractButton*> remplissage() ;
void deleteVect(std::vector<AbstractButton*> tab);

#endif