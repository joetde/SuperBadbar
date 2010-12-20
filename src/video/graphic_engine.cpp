/**
 * 	@file graphic_engine.cpp
 * 	@brief Implémentation de la classe Graphic_engine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
 
#include "graphic_engine.h"
#include "../sprites/babar.h"
#include "../video/camera.h"
#include "../video/talks.h"
#include "../video/dashboard.h"
#include "../video/pictures_container.h"
#include "../game/static_data.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>


Graphic_engine::Graphic_engine()
{
	PRINT_CONSTR(1, "Construction de Graphic_engine")
	PRINT_TRACE(1, "Initialisation de SDL")
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		PRINT_DEBUG(1, "Erreur d'initialisation de la SDL")
		return;
	}
	PRINT_TRACE(1, "Initialisation de TTF")
	if (TTF_Init() == -1) {
		PRINT_DEBUG(1, "Erreur d'initialisation de TTF");
		return;
	}
	m_camera = new Camera();
	m_talks = new Talks();
	m_dashboard = new Dashboard();
	m_pictures_container = new Pictures_container();
}

Graphic_engine::~Graphic_engine()
{
	PRINT_CONSTR(1, "Destruction de Graphic_engine")
	delete m_camera;
	delete m_talks;
	delete m_dashboard;
	delete m_pictures_container;
	PRINT_TRACE(1, "Fermeture de TTF")
	TTF_Quit();
	PRINT_TRACE(1, "Fermeture de SDL")
	SDL_Quit();
}

void Graphic_engine::init_graphic_engine(Babar *babar, Static_data *static_data)
{
	m_camera->init_camera(babar);
	m_talks->init_talks(m_camera, m_pictures_container);
	m_dashboard->init_dashboard(m_pictures_container);
}

void Graphic_engine::update(Static_data *static_data)
{
	m_camera->update_pos(static_data);
}

void Graphic_engine::draw_dashboard(int lifes, Camera *camera, Babar *babar)
{
	m_dashboard->draw_dashboard(lifes, camera, babar);
}


Camera *Graphic_engine::get_camera()
{
	return m_camera;
}

Talks *Graphic_engine::get_talks()
{
	return m_talks;
}

Pictures_container *Graphic_engine::get_pictures_container()
{
	return m_pictures_container;
}
