#ifndef _KEYCONFIG_MENU_H
#define _KEYCONFIG_MENU_H

#include "../menus/menu.h"

#include "../video/surface.h"
#include "../menus/ListMenuActions.h"


class KeyconfigMenu: public Menu {
	protected:



	public:
	KeyconfigMenu(Menu *parent = NULL);
	~KeyconfigMenu();
	virtual void update();

	protected:
	virtual void treat_choice(int choice);
};


#endif
