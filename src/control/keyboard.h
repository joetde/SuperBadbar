/**
 * 	@file keyboard.h
 * 	@brief header de la Classe Keyboard
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#ifndef _KEYBOARD_
#define _KEYBOARD_

#include "../../lib/SDL/include/SDL/SDL.h"

#include <iostream>
#include <string>
#include <queue>

enum key {
	k_none = 0, k_exit, k_escape, k_up, k_down, k_right, k_left, k_next_weapon, k_prev_weapon, k_action, k_jump, k_fire //k_fire doit etre le dernier
};
enum menu_key {
	mk_up, mk_down, mk_left, mk_right, mk_enter, mk_exit, mk_escape, mk_none
};

class Analyser;

/**
 * 	@class Keyboard
 *	@brief Gestion des evènement claviers
 *
 *	La classe Keyboard met à jour le tableau des touches enfoncees.
 *	Les touches gerees sont: quitter, haut, bas, droite, gauche, action,
 * 	saut, tir.\n
 *	Elle fournit un accesseur vers l'etat de ces touches.\n
 *	Elle permet egalement de forcer la desactivation d'une ou plusieurs
 *	touches part l'appel d'une methode (disable_key, disable_all)
 *
 * 	@todo Enlever les touches inutiles, charger les touches depuis
 *	un fichier de configuration, donner la possibilite au joueur
 * 	de choisir ses touches avec un menu
 *
 *	@warning Si trop de touches sont appuyees simultanement, certaines ne sont pas detectees.\n
 *	Solution: changer la configuration des touches (eviter en particulier les fleches directionnelles)
 **/
class Keyboard {

private:
	enum key m_key_config[SDLK_LAST];	// tableau de configuration des touches
	int m_key_down[k_fire + 1];		// tableau des touches enfoncees
//~ 	int m_key_down_bis[k_fire + 1];		// tableau des touches enfoncees
//~ 	int m_key_down_bis2[k_fire + 1];		// tableau des touches enfoncees
	bool m_record_on, m_replay_on; 	// indique si les entrees doivent etre enregistrees (resp lues)
	Analyser *m_analyser;			// analyser si m_replay_on vaut vrai
	std::ofstream *m_record_file;
	std::queue<menu_key> m_menu_input; 
public:
	/*!
	* 	@brief Constructeur
	*	@param record_on Si vrai, le clavier sauvegarde les entrees dans file_name
	*	@param replay_on Si vrai, le clavier lit les entrees dans file_name
	*	@param file_name Chemin du fichier d'input ou output a partir du repertoire courant
	*/
	Keyboard(bool record_on = false, bool replay_on = false,  std::string output_name = "", std::string input_name = "");

	/*!
	* 	@brief Destructeur
	*/
	~Keyboard();

	/*!
	* 	@brief Charge La configuration des touches depuis un fichier
	*	@param config_name Le nom du fichier de configuration depuis le dossier des fichiers de configuration	
	*/
	void load_config(std::string config_name);

	/*!
	* 	@brief Met à jour le tableau des touches enfoncees
	*/
	void update_events();

	/*!
	* 	@brief Accesseur
	*	@param k la touche a controler
	*	@return Vrai si la touche est enfoncee
	*/
	bool key_down (enum key k) const;

	/*!
	* 	@brief Accesseur
	*	@param k la touche a controler
	*	@return Le nombre de cycles depuis lequel la touche est enfoncee
	*/
	int time_pressed(enum key k) const;

	/*!
	* 	@brief Accesseur
	*	@return Vrai si une touche gauche ou droite est enfoncee
	*/
	bool key_dir_down() const;

	/*!
	* 	@brief Force le relachement de la touche
	*	@param k la touche à relacher
	*/
	void disable_key(enum key k);

	/*!
	* 	@brief Force le relachement de toutes les touches
	*/
	void disable_all_keys();
	
	
	/*!
	*	@brief Attend un evenement menu_key et le retourne
	*	@return Le menu_key entre par l'utilisateur
	*/
	menu_key wait_menu_key();
	
	/*!
	*	@brief Detecte dans la pile un evenement menu_key et le retourne
	*	@return Le menu_key entre par l'utilisateur (mk_none s'il n'y en a pas)
	*/	
	menu_key poll_menu_key();
	
	/*!
	*	@brief Met le jeu en pause jusqu'a l'enfoncement de la touche k
	*	@param k La touche attendue
	*/
	void wait_key(enum key k);
	
	/*!
	*	@brief Met le jeu en pause jusqu'a l'enfoncement d'une touche 
	*/	
	void wait_for_any_key();
	
	/*!
	*	@brief Autorise la repetition des touches (typiquement pour le menu)
	*/
	void enable_key_repeat();

	/*!
	*	@brief Interdit la repetition des touches (typiquement pour le jeu normal)
	*/
	void disable_key_repeat();
	
	/*!
	*	@brief Vide la liste des touches menu recemment enfoncees
	*/
	void reset_menu_keys();
	
	/*!
	*	@brief Teste s'il reste des touches menu enfoncees non traitees
	*	@return Vrai s'il reste au moins une touche non traitee
	*/
	bool is_next_menu_key() const;
	
	/*!
	*	@brief Supprime la derniere touche menu enfoncee de la liste
	*	@return La derniere touche menu enfoncee 
	*/
	menu_key pop_menu_key();
	
private:
	// auxilliaire de wait_menu_key et poll_menu_key
	menu_key treat_menu_key(SDL_Event event);

	// mutateur: affecte val enfonce a l'indice k dans le tableau des touches
	void set_key(enum key k, int val);
	void set_key(int k, int val);

	// increment le temps d'appui sur k
	void incr_key_down(enum key k);
	void incr_key_down(int k);


};



#endif
