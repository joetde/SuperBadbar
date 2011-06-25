#ifndef ANIMATED_SET_MANAGER_H_INCLUDED
#define ANIMATED_SET_MANAGER_H_INCLUDED

#include "AnimatedSet.h"

class AnimatedSet;

/**
 *  @class AnimatedSetManager
 *  @brief Classe gr�ant les animated_sets
 */
class AnimatedSetManager {
    private:
        std::list<AnimatedSet*> * m_sets;

        /**
         *  @brief Ajout d'un set
         */
        void add(AnimatedSet * set);
    public:
        /**
         *  @brief Constructeur
         */
        AnimatedSetManager();

        /**
         *  @brief Destructeur
         */
        ~AnimatedSetManager();

        /**
         *  @brief Ajouter un nophysic_set
         */
        void add_set(std::string anim_name, int x, int y, bool rand_pic=false, bool ended=false, bool to_delete=false);

        /**
         *  @brief Ajouter un physic_set
         */
        void add_set(std::string anim_name, Rect pos, Rect speed);

        /**
         *  @brief Mise � jour : update_pos, update_speed
         */
        void update();

        /**
         *  @brief Vide la liste sans la d�truire
         */
        void clear();

        /**
         *  @brief Charge les sets du niveau
         *  @param Analyser ouvert sur le fichier .lvl
         */
        void load_sets(Analyser * a);
};

#endif // ANIMATED_SET_MANAGER_H_INCLUDED
