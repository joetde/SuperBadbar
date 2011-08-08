/**
 * 	@file surface.h
 * 	@brief Header de la classe Surface
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _SURFACE_
#define _SURFACE_

#include <string>
#include <vector>

#include <util/Rect.h>
#include "util/debug.h"

#include <SFML/Graphics.hpp>

class PicturesContainer;
struct SDL_Surface;
class SurfaceCompositeItem;




/**
*	@class Surface
*	@brief Classe representant toute image du jeu (sans sa position)
*/
class Surface {
protected:
	sf::Drawable *m_drawable;
	sf::Sprite *m_sprite;
	static PicturesContainer *m_pictures_container;
	SDL_Surface *m_surface; // a virer

public:

	Surface():
		m_drawable(NULL),	
		m_sprite(NULL),
		m_surface(NULL)
		{}

	/**
	*	@brief Constructeur
	*	@param filename Le chemin du fichier a partir de la racine du projet
	*/
	Surface(std::string filename);

	/**
	*	@brief Destructeur
	*/
	virtual ~Surface();

	/**
	*	@brief Accesseur
	*	@return L'image SFML
	*/
	sf::Drawable *getSurface();
	SDL_Surface *get_surface();

	virtual void setSurface(sf::Drawable *surface) {m_drawable = surface;}

	/**
	*	@brief Duplique la SDL surface contenue et la renvoie
	*	@return La copie
	*/
	SDL_Surface *get_copy_surface();
	/**
	*	@brief Initialise le PicturesContainer des Surfaces
	*	@warning A appeler seulement �  l'initialisation du moteur graphic
	*	@param PicturesContainer Le gestionnaire d'images
	*/
	static void set_pictures_container(PicturesContainer *PicturesContainer);

	/**
	*	@brief Accesseur
	*	@return La largeur de l'image
	*/
	virtual int w();

	/**
	*	@brief Accesseur
	*	@return La hauteur de l'image
	*/
	virtual int h();

	/**
	*	@brief Mutateur
	*	@param La largeur de l'image
	*/
	void set_w(int w);

	/**
	*	@brief Mutateur
	*	@return La hauteur de l'image
	*/
	void set_h(int h);

	/*!
	*	@brief Accesseur
	*	@return La liste des surfaces filles et de leurs positions relatives
	*
	*	Les Surface ayant des enfants heritent de SurfaceComposite
	*/
	virtual std::vector<SurfaceCompositeItem *> *children ()  { return NULL; }

	/**
	*	@brief Blit l'image sur le background
	*	@param background La surface sur laquelle on blit l'image
	*	@param pos La position de blit par rapport au background (x et y comptent)
	*	@param rel_pos La taille du rectangle copie (h et w comptent)
	*/
	void blit_surface(Surface *background, Rect pos, Rect rel_pos);
	void blit_surface(Surface *background, Rect pos);

};

#endif
