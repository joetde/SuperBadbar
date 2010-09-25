
void Camera::display_background(SDL_Surface *background)
void Camera::display_sprite(Babar *babar)
{
	SDL_Rect pos_babar = babar->position();
	pos_babar.x -= m_frame.x;
	pos_babar.y -= m_frame.y;
	SDL_BlitSurface(babar->current_picture(), NULL, m_screen, &pos_babar);

}

{
	SDL_Rect pos_monster = monster->position();
	pos_monster.x -= m_frame.x;
	pos_monster.y -= m_frame.y;
	SDL_BlitSurface(monster->current_picture(), NULL, m_screen, &pos_monster);
}

void Camera::display_sprite(Projectile * proj)   /* Surcharge */
{
	SDL_Rect pos_proj = proj->position();
	pos_proj.x -= m_frame.x;
	pos_proj.y -= m_frame.y;
	SDL_BlitSurface(proj->current_picture(), NULL, m_screen, &pos_proj);
}

void Camera::display_static(Static *sttc)
{
    SDL_Rect pos_static = sttc->position();
    pos_static.x -= m_frame.x;
	pos_static.y -= m_frame.y;
    SDL_BlitSurface(sttc->image(), NULL, m_screen, &pos_static);
}


