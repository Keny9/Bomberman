// BombermanProject.cpp: d�finit le point d'entr�e pour l'application console.

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "SDL_mixer.h"
#include "Game.h"

using namespace std;

int main(int argc, char* argv[]) {

	SDL_Window* window = NULL; // Fen�tre

	SDL_Surface* background = NULL; // Arri�re-plan

	const int LARGEUR = 750; // Largeur de l'�cran
	const int HAUTEUR = 720; // Hauteur de l'�cran

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		cout << "Erreur lors de l'initialisation de la SDL", SDL_GetError(); // S'il y a une erreur
		exit(EXIT_FAILURE);
	}

	if (TTF_Init() == -1) {
		std::cout << "TTF_Init: %s\n", TTF_GetError();
		exit(2);
	}

	// Cr�er la fen�tre
	window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN);

	// Obtenir la surface de la fen�tre
	background = SDL_GetWindowSurface(window);

	Game* game = new Game(window, background);

	game->start();

	SDL_DestroyWindow(window); // D�truire la fen�tre

	Mix_CloseAudio(); //Fermeture de l'API
	TTF_Quit(); // Arr�t de SDL_TTF
	SDL_Quit(); // Arr�t de SDL (lib�ration de la m�moire)

	return EXIT_SUCCESS;
}
