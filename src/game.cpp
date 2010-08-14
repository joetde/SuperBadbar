/**
 * Contient la boucle de Game et les paramètres de la partie
 * Sera accessible à partir de la touche "jouer" du menu
**/


#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "game.h"
#include "sprites.h"
#include "window.h"
#include "globals.h"
#include "events.h"
#include "camera.h"
#include "collisions.h"
#include "levels.h"
#include "statics.h"


Game::Game(): m_monster(1, (SDL_Rect){100,100,30,30}, 50), m_camera(&m_babar)
{
	m_time = SDL_GetTicks();
	m_previous_time = SDL_GetTicks();
}

Game::~Game()
{

}

void Game::update_pos()
{
	m_babar.update_pos();
	m_monster.update_pos();
	while(!projectiles.end()) {
	    projectiles.element()->update_pos();
	    projectiles.next();
	}
	projectiles.init();
}

void Game::update_speed()
{
	m_babar.update_speed();
	m_monster.update_speed();

	m_babar.update_state();         /* A changer de place, en discuter */
}

void Game::refresh_screen()
{
	/* affichage du fond */
	m_camera.update_pos();
	SDL_Rect background_pos = m_camera.frame();
	background_pos.x = - background_pos.x;
	background_pos.y = - background_pos.y;
	SDL_BlitSurface(curr_lvl.background(), NULL, screen, &background_pos);

	/* affichage des statics (à faire en premier car derrière -> p-e pas tous...) */
	while(!statics.end()) {
	    m_camera.display_static(statics.element());
	    statics.next();
	}
	statics.init();

	/* affichage des projectiles */
	while(!projectiles.end()) {
	    m_camera.display_sprite(projectiles.element());
	    projectiles.next();
	}
	/* suppression de projectiles trop vieux */
    projectiles.delete_elements(too_old);

	/* affichage des sprites */
	m_camera.display_sprite(&m_monster);
	m_camera.display_sprite(&m_babar);

	/* mise à jour */
	SDL_Flip(screen);
}

void Game::game_loop()
{
	bool end = false;
	while (!end){
		m_time = SDL_GetTicks();
		if (m_time - m_previous_time > TIME_LOOP) {
			Events_stat.update_events();
			if (Events_stat.key_down(k_exit))
				end = true;
			update_speed();
			update_pos();
			refresh_screen();
			if (check_collision(m_babar.position(), m_monster.position()))
				fprintf(stderr, "COLLISION\n");
			fprintf(stderr, "pourcentage d'utilisation du temps: %f\n", (float)(m_time - m_previous_time - TIME_LOOP)/100.0); // marge de temps
			m_previous_time = m_time;
		} else  {
		    SDL_Delay(TIME_LOOP - (m_time - m_previous_time));
		}
	}
}

