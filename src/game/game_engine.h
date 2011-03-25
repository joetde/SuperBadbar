/**
 * 	@file game_engine.h
 * 	@brief header de la classe Game_engine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */



#ifndef _GAME_ENGINE
#define _GAME_ENGINE

#include <stdint.h>

class Static_data;
class Game;
class Camera;
class Keyboard;
class Babar;
class Monsters_manager;
class Events_manager;
class Collisions_manager;
class Projectiles_manager;
class Pictures_container;
class Sound_engine;


/**
 * 	@class Game_engine
 * 	@brief Moteur de jeu: traite les données
 *
 *	Contient notamment les listes de sprites, la matrice
 *	de collision.
 */
class Game_engine {
private:
	uint32_t m_matrix_weight;					/* Largeur de la matrice */
	uint32_t m_matrix_height;					/* Hauteur de la matrice */
	Monsters_manager *m_monsters_manager;
	bool m_victory;
public:
	/**
	 * 	@brief Constructeur
	*/
	Game_engine();

	/**
	 * 	@brief Destructeur
	*/
	~Game_engine();

	/**
	 * 	@brief Initialisation des données
	 * 	@param level_name Le chemin depuis la racine vers le niveau a charger
	 * 	@param camera La camera qui servira à afficher les images
	 * 	@param static_data Données du niveau
	 * 	@param keyboard Gestionnaire du clavier
	 *	@param pictures_container Le gestionnaire d'images
	*/
	void init_game_engine(std::string level_name, Camera *camera, Pictures_container *pictures_container);

	/*!
	 *	@brief Met a jour le game_engine
	*/
	void update();

	/**
	 * 	@brief Mise à jour des positions des éléments du jeu
	 *	@todo à déplacer
	*/
	void update_pos();

	/**
	 * 	@brief Mise à jour des vitesses des éléments du jeu
	*/
	void update_speed();

	/**
	 * 	@brief Supprimer les projectiles et monstres "morts"
	 *	@param static_data données du niveau
	*/
	void delete_dead_things();

	/**
	 * 	@brief Check les collisions monstres/projectiles
	*/
	void update_monsters_projectiles();

	/**
	 * 	@brief Check les collisions babar/projectiles
	*/
	void update_babar_projectiles();

	/**
	 * 	@brief Affichage des monstres
	 *	@param camera La camera d'affichage
	*/
	void display_monsters(Camera * const camera) const;

 	/**
	 * 	@brief Affichage des projectiles amis
	 *	@param camera La camera d'affichage
	 *	@todo à déplacer
	*/
	void display_projectiles_friend(Camera *camera);

	/**
	 * 	@brief Affiche les événements affichables
	 *	@param camera La camera qui affichera les événéments
	*/
	void display_events(Camera *camera);

	/*!
	 * 	@brief Joue les sons à jouer ce cycle
	 *	@param sound_engine Gestionnaire de son
	 *
	 * Gère pour l'instant les sons de babar et des monstres
	*/
	void play_sounds();

	/*!
	 *	@brief Fait gagner le niveau
	*/
	void set_victory();

	/*!
	 *	@brief Accesseur
	 *	@return Vrai si le joueur a gagne
	*/
	bool has_won();
	
	/*!
	 *	@brief Accesseur
	 *	@return Vrai si le joueur a perdu
	*/
	bool has_lost();
	
	
};



#endif
