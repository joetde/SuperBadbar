/**
 * Contient la boucle de Game et les paramètres de la partie
 * Sera accessible à partir de la touche "jouer" du menu
**/


#include "../sound/sound.h"
#include "game.h"
#include "../util/debug.h"
#include "../util/collisions.h"
#include "../control/keyboard.h"

#include "../sprites/babar.h"
#include "../sprites/monsters.h"
#include "../sprites/projectiles.h"
#include "../util/lists.h"
#include "../sprites/sprites.h"
#include "../sprites/babar.h"
#include "../video/camera.h"
#include "../video/talks.h"
#include "../game/dynamic_data.h"
#include "../game/static_data.h"
#include "../sound/sound.h"
#include "../sound/sound_manager.h"
#include "../video/statics.h"
#include "../video/dashboard.h"
#include "../events/events_manager.h"


Game::Game(): m_sound_manager(new Sound_manager()), m_keyboard(new Keyboard()),m_static_data(new Static_data()),   m_dynamic_data(new Dynamic_data()), m_camera(new Camera), m_talks(new Talks()),  m_events_manager(new Events_manager)
{
	PRINT_CONSTR(1, "Construction de la classe Game")
	m_static_data->init_static_data(1);
	m_dynamic_data->init_dynamic_data(m_camera, m_static_data, m_sound_manager, m_keyboard);
	m_camera->init_camera(m_dynamic_data->babar());
	m_talks->init_talks(m_camera);
	m_events_manager->init_events_manager(m_static_data, m_dynamic_data);
	m_events_manager->load_events();
	m_dashboard = new Dashboard();
	m_time = SDL_GetTicks();
	m_previous_time = SDL_GetTicks();
	update_camera();
}

Game::~Game()
{
	PRINT_CONSTR(1, "Destruction de la classe Game")

}

void Game::update_pos()
{
//~ 	m_babar.update_pos(m_static_data);
		m_dynamic_data->babar_monsters_collision();

	m_dynamic_data->babar_update_pos(m_static_data);
	m_dynamic_data->projectiles_friend_update_pos(m_static_data);
	m_dynamic_data->monsters_update_pos(m_static_data);

	
}

void Game::update_speed()
{
//~ 	m_babar.update_speed();
	m_dynamic_data->babar_update_speed();
	m_dynamic_data->monsters_update_speed();

//~ 	m_babar.update_state(m_static_data);         /* A changer de place, en discuter */   
	m_dynamic_data->babar_update_state(m_static_data);
	
	
}

void Game::update_camera()
{
    m_camera->update_pos(m_static_data);
}

void Game::update_events_manager()
{
	m_events_manager->update();
}


void Game::refresh_screen()
{
	/* affichage du fond */
	m_camera->update_pos(m_static_data);
	m_camera->display_background(m_static_data->background());

	/* affichage des statics (à faire en premier car derrière -> p-e pas tous...) */
	m_static_data->display_statics(m_camera);

    /* affichage des monstres */
	m_dynamic_data->display_monsters(m_camera);


	/* affichage des projectiles */
	m_dynamic_data->display_projectiles_friend(m_camera);
	
	
	/* suppression de projectiles trop vieux */
	m_dynamic_data->delete_old_projectiles_friend(m_static_data);
	
	
	/* affichage du sprite babar */
	m_camera->display_sprite(m_dynamic_data->babar());
	
	/* affichage du tableau de board */
	m_dashboard->draw_dashboard(m_dynamic_data->babar()->lifes(), m_camera, m_dynamic_data->babar());

	/* mise à jour */
	m_camera->flip_camera();
}



void Game::game_loop()
{
	int compteur = 0;
	float used_time = 0;
	bool end = false;
	int begining = SDL_GetTicks();
	m_sound_manager->play_music();
	while (!end){
		m_time = SDL_GetTicks();
		if (m_time - m_previous_time > TIME_LOOP) {
			PRINT_TRACE(3,"Cycle de jeu n°%d", compteur)
			compteur++;
			m_previous_time = m_time;
			m_keyboard->update_events();
			update_events_manager();
			if (m_keyboard->key_down(k_exit))
				end = true;
            m_dynamic_data->update(m_camera);
			update_speed();
			update_pos();
			check_monsters();
			refresh_screen();
			m_time = SDL_GetTicks();
			used_time += (float)(m_time - m_previous_time)/(float)TIME_LOOP;
			if (compteur % PERF_CYCLES == 0) {
				PRINT_PERF("pourcentage d'utilisation du temps: %d", (int)((used_time * 100) / PERF_CYCLES))
				used_time = 0;
			}
		} else  {
		    SDL_Delay(TIME_LOOP - (m_time - m_previous_time));
		}
	}
	PRINT_PERF("**************************************")
	PRINT_PERF("* temps moyen d'un cycle en ms = %d *", ((SDL_GetTicks() - begining)/compteur))
	PRINT_PERF("**************************************")

}




void Game::check_monsters()
{
	m_dynamic_data->update_monsters_projectiles();
}


