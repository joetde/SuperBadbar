#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "../sprites/sprites.h"
#include "../sprites/projectiles_manager.h"
#include "../game/collisions_manager.h"
#include "../items/weapons.h" /* pour enum */

#define ESTIM_SPEED 10
#define WEIGHT_PROJ 100
#define DIST_WEIGHT 100


class AI {
    private:
        Rect * m_pos;
        Sprite * m_target;

        double eval(direction d);
        double dist(Rect A, Rect B);
        bool check_collision(Rect A, Rect B);
        double eval_up();
        double eval_down();
        double eval_left();
        double eval_right();

    public:
        AI(Sprite * target, Rect * pos);
        ~AI();

        /**
         * @brief donne la direction � suivre
         * @return direction
         */
        direction dir();
};

#endif // AI_H_INCLUDED