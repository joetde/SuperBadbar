/**
 * 	@file sound_engine.h
 * 	@brief Header de la classe Sound_engine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _SOUND_ENGINE_
#define _SOUND_ENGINE_

#include "../../lib/fmodapi375win/api/inc/fmod.h"

#include <string>
#include <map>
#include "../items/weapons.h"

#define MUSIC_CANAL 1

#define BABAR_FIRE_CANAL 2

class Sound;
class Sonorisable;
/**
 * 	@class Sound_engine
 * 	@brief Moteur de son
 *
 *
 */
class Sound_engine {
private:
	std::map<std::string, FSOUND_SAMPLE*> m_sound_samples;
	FSOUND_STREAM *m_music;
	int m_sounds_volume;
	int m_music_volume;


public:

	/**
	 * @brief Constructeur
	*/
	Sound_engine();

	/**
	 * @brief Destructeur
	*/
	~Sound_engine();

	/**
	 * @brief Joue la musique
	*/
	void play_music();

	/**
	 * @brief Joue la musique
	*/
	void play_sound(std::string key);

	void play_sound(Sonorisable *sonorisable);
	
	void set_sounds_volume(int v);
	void set_music_volume(int v);
	int get_sounds_volume() const;
	int get_music_volume() const;
};


#endif
