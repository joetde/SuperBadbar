/**
 * 	@file projectiles.h
 * 	@brief Header de la classe Projectile
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#ifndef _PROJECTILES_
#define _PROJECTILES_

#include "actor.h"

class Static_data;

enum state_p {
    NONE
};

/**
 * 	@class Projectile
 * 	@brief Projectiles du jeu
 */
class Projectile: public Actor {
protected:
    state_p m_state;
    unsigned int m_damage;      /* Nombre de pt des vies que le projectile va faire perdre */
	bool m_dead;				/* Indique si le projectile est à supprimer */

public:
	/*!
	 *	@brief Constructeur
	*/
    Projectile(Rect pos, direction h, unsigned int speedx, unsigned int speedy, unsigned int damage);

	/*!
	 * 	@brief Destructeur
	*/
     ~Projectile();

	/*!
	 * 	@brief Met à jour la position du Projectile
	 *	@param collisions_manager Gestionnaire de collisions
	*/
	void update_pos(Collisions_manager *collisions_manager);

	/*!
	 * 	@brief Accesseur
	 *	@return Le nombre de points de vies que fait perdre le projectile
	*/
    unsigned int damage() const;

	/*!
	 * 	@brief Accesseur
	 *	@return La vitesse du projectile
	*/
    Rect speed() const;   /* Accesseur */

	/*!
	 *	@brief Accesseur
	 *	@return Vrai si le Projectile doit etre supprimé
	*/
	bool dead() const;

	/*!
	 *	@brief Mutateur: "tue" le projectile
	*/
	void kill();
};

#endif
