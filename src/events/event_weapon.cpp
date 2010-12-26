/** * 	@file event_weapon.cpp * 	@brief implémentation de la classe Event * * 	@author Guillaume Bérard & Benoit Morel * 	@date decembre 2010 * */#include <iostream>#include "../items/weapons.h"#include "event_weapon.h"#include "../sprites/babar.h"#include "../util/debug.h"#include "../util/globals.h"#include "../util/analyser.h"#include "../util/repertories.h"#include "../video/pictures_container.h"#include "../video/surface.h"Event_weapon::Event_weapon(Babar *target, Pictures_container *pictures_container, Rect pos) : Event_item(target, pos){	PRINT_CONSTR(3, "Construction d'un event_weapon");	m_weapon_type =  SHOTGUN;	m_can_be_destroyed = false;	std::string chemin = PIC_R + "items/weapons/rifle.png";	m_picture = new Surface(chemin);	m_pos.w = m_picture->w();	m_pos.h = m_picture->h();}Event_weapon::Event_weapon(Babar *target, Pictures_container *pictures_container, Analyser *analyser){	PRINT_CONSTR(3, "Construction d'un event_weapon");	m_can_be_destroyed = false;	std::string weapon_name = analyser->read_string();	std::string chemin = PIC_R + "items/weapons/" + weapon_name + ".png";	if (weapon_name == "shotgun") {		m_weapon_type = SHOTGUN;	} else if (weapon_name == "machinegun"){		m_weapon_type = MACHINEGUN;	} else if (weapon_name == "gun") {		m_weapon_type = GUN;	} else {		PRINT_DEBUG(1, "nom d'arme inconnu dans l'event_weapon, choix du gun par defaut");		m_weapon_type = GUN;	}	m_picture = new Surface(chemin);	m_pos.x = analyser->read_int();	m_pos.y = analyser->read_int();	m_pos.w = m_picture->w();	m_pos.h = m_picture->h();	m_target = target;}Event_weapon::~Event_weapon(){	delete m_picture;	PRINT_CONSTR(3, "Destruction d'un event_weapon");}void Event_weapon::start(){	m_can_be_destroyed = true;	m_target->add_weapon(m_weapon_type);}Surface *Event_weapon::current_picture() const{	return m_picture;}