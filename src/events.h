/**
 * Gestion des évènements: contient la configuration des touches
 * et l'utilise pour gérer les actions déclenchées par le joueur
 **/

#ifndef _EVENTS_
#define _EVENTS_

enum key {
	k_none, k_exit, k_up, k_down, k_right, k_left, k_jump, k_fire
};

class Events_status {
private:
	enum key m_key_config[SDLK_LAST];
	bool m_key_down[k_fire + 1];
public:
	Events_status();	/* constructeur */  // il faudra le faire à partir d'un fichier de configuration
	~Events_status();	/* destructeur */
	void update_events();	/* met à jour les touches enfoncées à partir des actions du joueur */
	bool key_down (enum key k);	/* retourne vrai si la touche est enfoncée */
};



#endif