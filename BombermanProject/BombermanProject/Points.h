#pragma once
#include <SDL_ttf.h>

class Points
{

private:

	SDL_Surface* screenSurface;
	SDL_Rect position;

	TTF_Font *font;
	SDL_Color fontColor;
	SDL_Surface *texte;
	char tblPoints[20];

	const int FONTSIZE = 20;
	const char *FONTNAME = "osdmono.ttf";

public:

	Points(SDL_Surface* b);
	~Points();
	void showGamePoints(int points);

};

