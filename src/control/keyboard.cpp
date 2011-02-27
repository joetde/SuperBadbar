/**
 * 	@file keyboard.cpp
 * 	@brief implémentation de la Classe Keyboard
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
#include <iostream>

#ifdef WIN32
    #include "../../lib/SDL/include/SDL/SDL.h"
#else
    #include <SDL/SDL.h>
#endif

#include <stdint.h>

#include "keyboard.h"
#include "../util/debug.h"
#include "../util/repertories.h"
#include "../util/analyser.h"

Keyboard::Keyboard(bool record_on, bool replay_on,  std::string output_name, std::string input_name)
{
	PRINT_CONSTR(1, "Construction de Keyboard")
	for (uint32_t i = 0; i < SDLK_LAST; i++)
		m_key_config[i] = k_none;
	for (uint32_t i = 0; i <= k_fire; i++)
		m_key_down[i] = false;
	m_key_config[SDLK_i] = k_up;
	m_key_config[SDLK_k] = k_down;
	m_key_config[SDLK_j] = k_left;
	m_key_config[SDLK_l] = k_right;
	m_key_config[SDLK_q] = k_jump;
	m_key_config[SDLK_d] = k_fire;
	m_key_config[SDLK_SPACE] = k_action;
	m_key_config[SDLK_a] = k_prev_weapon;
	m_key_config[SDLK_z] = k_next_weapon;
	m_record_on = record_on;
	m_replay_on = replay_on;
	if (m_replay_on) {
		m_analyser = new Analyser();
		m_analyser->open(input_name);
	} else {
		m_analyser = NULL;
	}
	if (m_record_on) {
		m_record_file = new std::ofstream(output_name.c_str(), std::ios::out | std::ios::trunc);
	} else {
		m_record_file = NULL;
	}
}

Keyboard::~Keyboard()
{
	PRINT_CONSTR(1, "Destruction d'Keyboard")
	if (m_record_file)
		delete m_record_file;
	if (m_analyser)
		delete m_analyser;
}

void Keyboard::update_events()
{
	if (!m_replay_on) {
		if (m_record_on)
			*m_record_file << std::endl;
		for (int i = k_none; i < k_fire + 1 ; i++)
			if (key_down((enum key)i))
				m_key_down[i]++;
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT :
				m_key_down[k_exit] = 1;
				if (m_record_on)
					*m_record_file << k_exit << " " << m_key_down[k_exit] << " ";
				break;
			case SDL_KEYDOWN:
				m_key_down[m_key_config[event.key.keysym.sym]] = 1;
				if (m_record_on)
					*m_record_file << m_key_config[event.key.keysym.sym] <<
						" " << m_key_down[m_key_config[event.key.keysym.sym]] << " ";
				if (event.key.keysym.sym==SDLK_ESCAPE) {
					m_key_down[k_exit]=1;
					if (m_record_on)
						*m_record_file << k_exit << " " << m_key_down[k_exit] << " ";
				}
				break;
			case SDL_KEYUP:
				m_key_down[m_key_config[event.key.keysym.sym]] = 0;
				if (m_record_on)
					 *m_record_file <<  m_key_config[event.key.keysym.sym] <<
						" " << m_key_down[m_key_config[event.key.keysym.sym]] << " ";
				break;
			default:
				break;
			}
		}
		if (m_record_on)
			*m_record_file << "666 666";
	} else {
		int x = m_analyser->read_int();
		int y = m_analyser->read_int();
		while (x != 666 && y != 666) {
			m_key_down[x] = y;
			x = m_analyser->read_int();
			y = m_analyser->read_int();
			PRINT_DEBUG(3, "%d %d", x, y);
		}
	}
}


bool Keyboard::key_down(enum key k) const
{
	return m_key_down[k];
}

int Keyboard::time_pressed(enum key k) const
{
	return m_key_down[k];
}

bool Keyboard::key_dir_down() const
{
    return (m_key_down[k_left]||m_key_down[k_right]);
}

void Keyboard::disable_key(enum key k)
{
	m_key_down[k] = false;
}

void Keyboard::disable_all_keys()
{
	for (uint32_t i = 0; i <= k_fire; i++)
		disable_key((enum key)i);
}
