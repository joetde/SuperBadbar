
void Camera::display_background(SDL_Surface *background)

void Camera::display_static(Static *sttc)
{
    SDL_Rect pos_static = sttc->position();
    pos_static.x -= m_frame.x;
	pos_static.y -= m_frame.y;
    SDL_BlitSurface(sttc->image(), NULL, m_screen, &pos_static);
}


