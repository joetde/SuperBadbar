/**
 * 	@file keyboard.cpp
 * 	@brief implémentation de la Classe Keyboard
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */
#include <iostream>

#include "../../lib/SDL/include/SDL/SDL.h"

#include <stdint.h>

#include "Keyboard.h"
#include "../control/EventOrderer.h"
#include "../control/SdlKeyConverter.h"
#include "../control/KeyboardConfig.h"
#include "../util/globals.h"
#include <fstream>	


Keyboard::Keyboard(bool record_on, bool replay_on,  std::string output_name, std::string input_name):
	m_EventOrderer(NULL)
{
	PRINT_CONSTR(1, "Construction de Keyboard")

	for (uint32_t i = 0; i <= k_fire; i++)
		set_key(i, 0);
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
	for (int i = k_none; i < k_fire + 1 ; i++)
		if (key_down((enum key)i))
			incr_key_down(i);
	SDL_Event event;
	menu_key mk;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT :
			set_key(k_exit, 1);
			m_menu_input.push(mk_exit);
			break;
		case SDL_KEYDOWN:
			if (event_ordered()) {
				answer_event_order(event.key.keysym.sym);
			} else {
				set_key(gKeyboardConfig->getKey(event.key.keysym.sym),  1);
				mk = treat_menu_key(event);
				if (mk != mk_none) {
					m_menu_input.push(mk);
				}
			}
			break;
		case SDL_KEYUP:
			set_key(gKeyboardConfig->getKey(event.key.keysym.sym), 0);
			break;
		default:
			break;
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
    return (key_down(k_left)||key_down(k_right));
}

void Keyboard::disable_key(enum key k)
{
	set_key(k, 0);
}

void Keyboard::disable_all_keys()
{
	for (uint32_t i = 0; i <= k_fire; i++)
		disable_key((enum key)i);
}

menu_key Keyboard::treat_menu_key(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_QUIT:
			return mk_exit;
		case SDL_KEYDOWN: /* Si appui d'une touche */
			// priorite aux touches en dur
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
					return mk_escape;
					break;
				case SDLK_UP:
					return mk_up;
				case SDLK_DOWN:
					return mk_down;
				case SDLK_LEFT:
					return mk_left;
				case SDLK_RIGHT:
					return mk_right;
				case SDLK_RETURN: case SDLK_KP_ENTER: case SDLK_SPACE:
					return mk_enter;
				default:
					break;
			}
			// sinon on regarde les touches du joueur
			switch (gKeyboardConfig->getKey(event.key.keysym.sym)) {
				case k_jump: case k_fire:
					return mk_enter;
				case k_up:
					return mk_up;
				case k_down:
					return mk_down;
				case k_right:
					return mk_right;
				case k_left:
					return mk_left;
				default:
					break;
			}
			break;
		default:
			break;
	}
	return mk_none;
}

menu_key Keyboard::poll_menu_key()
{
	SDL_Event event;
	menu_key res;
	while(SDL_PollEvent(&event)) {
		res = treat_menu_key(event);
		if (res != mk_none)
			return res;
	}
	return mk_none;
}

menu_key Keyboard::wait_menu_key()
{
	SDL_Event event;
	menu_key res;
	while (true) {
		SDL_WaitEvent(&event);
		res = treat_menu_key(event);
		if (res != mk_none)
			return res;
	}
	return mk_none;
}

void Keyboard::wait_key(enum key k)
{
	SDL_Event event;
	bool leave = false;
	while(!leave){
		SDL_WaitEvent(&event);
		if(event.type == SDL_KEYDOWN)
			if(gKeyboardConfig->getKey(event.key.keysym.sym) == k)
				leave = true;
	}
}

void Keyboard::wait_for_any_key()
{
	SDL_Event event;
	bool leave = false;
	while(!leave){
		SDL_WaitEvent(&event);
		if(event.type == SDL_KEYDOWN)
			leave = true;
	}
}

void Keyboard::enable_key_repeat()
{
	SDL_EnableKeyRepeat(500, 10);
}

void Keyboard::disable_key_repeat()
{
	SDL_EnableKeyRepeat(0, 10);
}

void Keyboard::set_key(enum key k, int val)
{
	m_key_down[k] = val;
}

void Keyboard::set_key(int k, int val)
{
	set_key((enum key) k, val);
}

void Keyboard::incr_key_down(enum key k)
{
	m_key_down[k]++;
}

void Keyboard::incr_key_down(int k)
{
	incr_key_down((enum key)k);
}

void Keyboard::reset_menu_keys()
{
	PRINT_DEBUG(1, "Reset de menu keys")
	while (is_next_menu_key()) {
		m_menu_input.pop();
	}
}

bool Keyboard::is_next_menu_key() const
{
	return !m_menu_input.empty();
}

menu_key Keyboard::pop_menu_key()
{
	menu_key res = m_menu_input.front();
	m_menu_input.pop();
	return res;
}

void Keyboard::order_event(EventOrderer *EventOrderer)
{
	m_EventOrderer = EventOrderer;
}

bool Keyboard::event_ordered()
{
	return m_EventOrderer;
}

void Keyboard::answer_event_order(SDLKey event)
{
	m_EventOrderer->answer_event_order(event);
	m_EventOrderer = NULL; // une fois qu'on a repondu une fois, on n'a plus d'orderer
}


