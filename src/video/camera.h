/**
 * Classe Camera: classe singleton qui gère toute la partie graphique du jeu.
 * Elle initialise la SDL, ouvre la fenetre et les ferme.
 * Elle pointe sur un sprite qu'elle suit dans ses déplacements avec update_pos(), appelé par la classe Game.
 * Elle permet d'afficher des sprites et le fond d'écran aux bons endroits en calculant leur position relative 
 * à la fenetre à partir de leur position absolue. 
 * Elle permet aussi d'afficher une SDL_Surface * quelconque à une position donnée dans la fenetre (indépendamment
 * de la position de la camera)
 * La camera suit le sprite pointé sauf lorsqu'il arrive aux limites du niveau.
 **/

#ifndef _CAMERA_
#define _CAMERA_




class Sprite;
class Babar;
class Monster;
class Projectile;
class Static;
class Static_data;

class Camera {
private:
	SDL_Rect m_frame;	/* cadre de la camera */
	Sprite *m_target;	/* sprite sur lequel pointe la camera */
	SDL_Surface *m_screen;
public:
	Camera(Sprite *target);					/* constructeur */
	~Camera();								/* destructeur */
	void update_pos(Static_data *static_data);						/* mise à jour de la camera */
	void display_background(SDL_Surface *background); /* affichage d'un fond d'écran */
	void display_sprite(Sprite *sprite);      /* affichage d'un Sprite */
	void display_static(Static *sttc);
	SDL_Rect frame();	/* accesseur (m_frame) */
	void display_picture(SDL_Surface *pic, SDL_Rect *pos); /* ATTENTION: pos designe la position par rapport à la fenetre: m_frame n'est pas pris en compte dans cette fonction */

	void flip_camera();
};



#endif