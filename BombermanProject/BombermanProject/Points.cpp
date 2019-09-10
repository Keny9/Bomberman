#include "Points.h"
#include <iostream>

Points::Points(SDL_Surface* b)
{
	screenSurface = b;

	texte = NULL;
	font = TTF_OpenFont(FONTNAME, FONTSIZE); // Chargement de la police
	fontColor = { 255, 255, 255 };
	tblPoints[20] = { 0 };

	position = { 500, 670, 100, 100};

}

void Points::showGamePoints(int points) {
	
	sprintf_s(tblPoints, "Points : %d", points); /* On écrit dans la chaîne "tblPoints" le score */

	texte = TTF_RenderText_Solid(font, tblPoints, fontColor);

	SDL_BlitSurface(texte, NULL, screenSurface, &position);
}

Points::~Points()
{
	TTF_CloseFont(font);
	font = NULL;
	SDL_FreeSurface(texte);
}