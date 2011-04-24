/**
 * 	@file projectiles.cpp
 * 	@brief Implémentation de la classe Projectile
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>

#include "projectiles.h"
#include "../util/debug.h"
#include "../game/game.h"
#include "../game/static_data.h"
#include "../physic/collisions_manager.h"
#include "../sprites/sprites_manager.h"


/**************************
**  Méthodes projectiles **
**************************/


Projectile::Projectile() {}

Projectile::Projectile(Rect pos, direction h, unsigned int speedx, unsigned int speedy, unsigned int damage)
{
	PRINT_CONSTR(3, "Construction d'un projectile")
    m_pos = pos;
    m_dir = h;
    m_damage = damage;
	m_life_span = PROJ_LIFE_SPAN;
    std::string rep = PIC_PROJ_R;

    /* Rajouter le nom... */
    m_sprite = gGraphics->get_sprites_manager()->add_table(rep+"simple/simple", MIDDLEGROUND);
    m_sprite->set_pos(m_pos);
	m_pos.h = m_sprite->h();
	m_pos.w = m_sprite->w();

    m_speed.x = speedx;
    m_speed.y = speedy;

	m_dead = false;
	m_phase = 0;

	m_invincible = false;
}

void Projectile::update_pos(Collisions_manager *collisions_manager)
{
    m_sprite->set_pos(m_pos);
	m_pos.h = m_sprite->h();
	m_pos.w = m_sprite->w();
	m_phase++;
	unsigned int coll;
	/* cas où le sprite descend */
	for (int speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE) {
		coll = collisions_manager->get_matrix()->down_collision_type(m_pos);
		if (Collisions_manager::is_down_coll(coll)){
			m_dead = true;
		} else {
			m_pos.y += BOX_SIZE;
		}
	}

	/* cas où le sprite monte */
	for (int speed_y = m_speed.y ; speed_y < 0 ; speed_y += BOX_SIZE){
		if (Collisions_manager::is_up_coll(collisions_manager->get_matrix()->up_collision_type(m_pos))){
			m_dead = true;
		} else {
			m_pos.y -= BOX_SIZE;
		}
	}

	/* cas où le sprite va à droite */
	for (int speed_x = m_speed.x ; speed_x > 0 ; speed_x -= BOX_SIZE){
			if(Collisions_manager::is_down_coll(collisions_manager->get_matrix()->down_collision_type(m_pos)))
				m_dead = true;
			m_pos.x += BOX_SIZE;
	}

	/* cas où le sprite va à gauche */
	for (int speed_x = m_speed.x ; speed_x < 0 ; speed_x += BOX_SIZE){
			if(Collisions_manager::is_down_coll(collisions_manager->get_matrix()->down_collision_type(m_pos))) {
				m_dead = true;
			}
			m_pos.x -= BOX_SIZE;
	}
	if (m_phase >= m_life_span)
		m_dead = true;
}

void Projectile::update_speed()
{

}

void Projectile::update_state()
{
    if ( m_speed.x > 0 ) {
        m_dir = LEFT;
    } else {
        m_dir = RIGHT;
    }
    m_sprite->change_anim(NONE, m_dir);
}

void Projectile::set_chan(ouille_chan chan)
{
    m_chan = chan;
}

Projectile::~Projectile()
{
	PRINT_CONSTR(3, "Destruction d'un projectile")
}

unsigned int Projectile::damage() const
{
    return m_damage;
}

Rect Projectile::speed() const
{
    return m_speed;
}

bool Projectile::dead() const
{
	return m_dead;
}

void Projectile::kill()
{
	m_dead = true;
	if ( !m_invincible ) {
        m_sprite->set_to_delete();
	}
	m_sprite = NULL;
}

bool Projectile::invincible()
{
    return m_invincible;
}
