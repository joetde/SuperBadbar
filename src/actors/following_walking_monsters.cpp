/**
 * 	@file following_walking_monsters.cpp
 * 	@brief Source de la classe Following_walking_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
#include <iostream>
#include <stdint.h>

#include "following_walking_monsters.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "../items/gun.h"
#include "../items/monster_basic_weapon.h"
#include "babar.h"
#include "../AI/AI.h"



Following_walking_monster::Following_walking_monster(Analyser *analyserLevel)
{
    m_nom = analyserLevel->read_string();

	// donnees contenues dans le level
	m_pos.x = analyserLevel->read_int();
	m_pos.y = analyserLevel->read_int();

	initFromMonsterFile(m_nom);

    m_ai = new AI(gBabar, &m_pos);
		
}

Following_walking_monster::~Following_walking_monster()
{
    delete m_ai;
}

void Following_walking_monster::update_speed_ai()
{
    direction d = m_ai->dir();
    m_state = WALKING;

    switch ( d ) {
        case LEFT:
            m_dir = LEFT;
            m_speed.x = -m_speed_def;
            break;
        case RIGHT:
            m_dir = RIGHT;
            m_speed.x = m_speed_def;
            break;
        case UP:
            /* pour ne pas avoir de vitesse trop rapides */
            if ( m_speed.y >= 0 ) {
                m_speed.y -= 70;
            }
            break;
        case DOWN:
            m_pos.y += 10;
            break;
        case NOPE:
            /* où le monstre ne doit rien faire => state = WAIT */
            m_state = WAIT;
            break;
    }
	m_speed.y += GRAVITE;


}



