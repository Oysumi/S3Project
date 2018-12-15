#include "Ressource.h"
#include "../Fonctions/fonctions.h"
using namespace std ;

//CONSTRUCTEUR

Ressource::Ressource()
{
	m_gold = 0 ;
	m_wood = 0 ;
	m_food = 0 ;
}

Ressource::Ressource(int gold, short wood, short food)
{
	m_gold = gold ;
	m_wood = wood ;
	m_food = food ;
}


//GETTERS

int Ressource::gold () const
{
	return m_gold ;
}
short Ressource::wood () const
{
	return m_wood ;
}
short Ressource::food () const
{
	return m_food ;
}


//SETTERS

void Ressource::set_gold(int gold)
{
	m_gold = gold ;
}
void Ressource::set_wood(short wood)
{
	m_wood = wood ;
}
void Ressource::set_food(short food)
{
	m_food = food ;
}


void Ressource::add_gold(int gold)
{
	m_gold += gold ;
}
void Ressource::add_wood(short wood)
{
	m_wood += wood ;
}
void Ressource::add_food(short food)
{
	m_food += food ;
}


void Ressource::del_gold(int gold)
{
	if (gold > m_gold)
		m_gold = 0 ;
	else
		m_gold -= gold ;
}
void Ressource::del_wood(short wood)
{
	if (wood > m_wood)
		m_wood = 0 ;
	else
		m_wood -= wood ;
}
void Ressource::del_food(short food)
{
	if (food > m_food)
		m_food = 0 ;
	else
		m_food -= food ;
}

void Ressource::operator+=(Ressource const& res)
{
	m_gold += res.m_gold ;
	m_wood += res.m_wood ;
	m_food += res.m_food ;
}