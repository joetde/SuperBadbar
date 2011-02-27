/**
 * 	@file walking_monsters.cpp
 * 	@brief Source de la classe Walking_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
#include <iostream>
#include <stdint.h>

#include "walking_monsters.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "../sound/sound_manager.h"
#include "../video/pictures_container.h"
#include "babar.h"


Walking_monster::Walking_monster() {}

Walking_monster::Walking_monster(Analyser *analyserLevel)
{
	m_nom = analyserLevel->read_string();
	Analyser analyserMonster;

	// donnees contenues dans le level
	m_pos.x = analyserLevel->read_int();
	m_pos.y = analyserLevel->read_int();
	m_area_begin = analyserLevel->read_uint32_t();
	m_area_end = analyserLevel->read_uint32_t();

	// donnees propres a la nature du monstre (a chercher dans le bestiaire)
	analyserMonster.open((MONSTERS_STATS_R + m_nom + MONSTERS_EXT).c_str());
	m_life = analyserMonster.read_int();
	m_speed_def = analyserMonster.read_int();
	analyserMonster.close();

	// images
    std::string pic_monsters_rep = PIC_MONSTERS_R;

    m_animt = new Anim_table(pic_monsters_rep+m_nom+"/"+m_nom);

	m_speed.x = m_speed_def;
	m_dir = RIGHT;

    m_animt->set_rect(m_pos);

	m_can_fire = false;
}

Walking_monster::~Walking_monster()
{

}


void Walking_monster::update_speed(Babar *babar)
{
	m_speed.y += GRAVITE;
	if (m_pos.x<m_area_begin) {
	    m_dir = LEFT;
		m_speed.x = -m_speed.x;
	}
	if (m_pos.x>m_area_end) {
	    m_dir = RIGHT;
	    m_speed.x = -m_speed.x;
	}
}

