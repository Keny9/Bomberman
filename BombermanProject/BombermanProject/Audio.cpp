#include "Audio.h"
#include <iostream>


Music::Music()
{
	mainTheme = Mix_LoadMUS("music.wav"); // Chargement de la musique
}

Music::~Music()
{
	Mix_FreeMusic(mainTheme); //Libération de la musique
}

void Music::startMusic()
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		std::cout << "Erreur lors de l'initialisation de l'audio", Mix_GetError();
	}

	//mainTheme = Mix_LoadMUS("music.wav"); // Chargement de la musique

	Mix_PlayMusic(mainTheme, -1); // Jouer infiniment la musique 
}