

#include "StaticData.h"

#include <iostream>
#include <stdint.h>
#include <string>

#include "actors/Actor.h"
#include "actors/Monster.h"
#include "game/Game.h"
#include "util/globals.h"
#include "util/utils.h"
#include "video/Camera.h"
#include "video/PicturesContainer.h"
#include "video/Statics.h"
#include "video/Surface.h"
#include "video/Surface.h"
#include "video/SurfaceBig.h"


StaticData::StaticData()
{
    PRINT_CONSTR (1, "Construction d'un StaticData");

}

StaticData::~StaticData()
{
    PRINT_CONSTR (1, "Destruction d'un StaticData");
    for (std::list<Static *>::iterator it = m_statics_first.begin();
            it != m_statics_first.end(); ++it)
    {
        delete (*it);
    }
    for (std::list<Static *>::iterator it = m_statics_back.begin();
            it != m_statics_back.end(); ++it)
    {
        delete (*it);
    }
    delete m_background;

}

void StaticData::init_StaticData (uint32_t lvl)
{
    std::string rep;
    char str[3];
    std::string str_lvl;
    sprintf (str, "%d", lvl);
    str_lvl = str;
    /*** Ouverture du fichier .lvl  ***/
    rep = LEVELS_R;
    init_StaticData (rep + "level" + str_lvl + ".lvl");
}

void StaticData::init_StaticData (std::string level_name)
{
    PRINT_CONSTR (1, "Construction d'un StaticData")
    m_level_name = level_name;
    Analyser analyser;
    int level = 0;
    /*** Ouverture du fichier .lvl  ***/
    analyser.open (LEVELS_R + m_level_name);

    /*** chargement du fond d'écran ***/
    analyser.find_string ("#Background#");
    m_background = new SurfaceBig (PIC_BACKGROUNDS_R + analyser.read_string() );

    /*** Remplissage des statics  ***/
    std::string static_pic_rep = PIC_STATICS_R;
    std::string static_name;
    analyser.find_string ("#Statics#");
    analyser.read_int();
    static_name = analyser.read_string();
    Rect pos;
    Static *curr_static;
    while (static_name[0] != '!')
    {
        pos.x = analyser.read_int();
        pos.y = analyser.read_int();
        analyser.read_int();
        curr_static = new Static (static_pic_rep + static_name + PICS_EXT, pos);
        level = analyser.read_int();
        if ( level == 0 )
        {
            add_static_back (curr_static);
        }
        else
        {
            add_static_first (curr_static);
        }

        static_name = analyser.read_string();
    }
    analyser.close();
}

Surface * StaticData::background()
{
    return m_background;
}

uint32_t StaticData::StaticData_height()
{
    return m_background->h() / BACKGROUND_SPEED - Constants::WINDOW_HEIGHT ;
    //~     return m_background->h() / BACKGROUND_SPEED / Constants::ZOOM - Constants::WINDOW_HEIGHT ;
}

uint32_t StaticData::StaticData_width()
{
    return m_background->w() / BACKGROUND_SPEED / Constants::ZOOM - Constants::WINDOW_WIDTH;
}

void StaticData::display_statics_first (Camera *camera)
{
    for (std::list<Static *>::iterator it = m_statics_first.begin();
            it != m_statics_first.end(); ++it)
    {
        camera->display ( (*it) );
    }
}

void StaticData::display_statics_back (Camera *camera)
{
    for (std::list<Static *>::iterator it = m_statics_back.begin();
            it != m_statics_back.end(); ++it)
    {
        camera->display ( (*it) );
    }
}

void StaticData::add_static_first (Static *stat)
{
    m_statics_first.push_back (stat);
}

void StaticData::add_static_back (Static *stat)
{
    m_statics_back.push_back (stat);
}

