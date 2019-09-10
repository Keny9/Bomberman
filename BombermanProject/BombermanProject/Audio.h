#pragma once
#include "SDL_mixer.h"

class Music
{
private:
	
	Mix_Music* mainTheme;

public:

	Music();
	~Music();

	void startMusic();
};

