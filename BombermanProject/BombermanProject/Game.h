#pragma once
#include <SDL.h>
#include <vector>
#include "Bomberman.h"
#include "Bomb.h"
#include "Map.h"
#include "Audio.h"
#include "SDL_mixer.h"
#include "LangueFolle.h"
#include "Points.h"

class Game {

public:
	Game(SDL_Window* w, SDL_Surface* b);
	void checkBombermanInvincibility(float currentTime);
	void showEndGameScreen();
	~Game();

	void start();

	int gamePoints;


private:
	
	// Attributs
	SDL_Window* window;
	SDL_Surface* background;

	Bomb* bomb;
	Map* map;
	Bomberman* bomberman;
	Music* audio;
	Bomb* bomb2;
	std::vector<LangueFolle*> langueFolle;
	Points* points;

	bool gameOver; // État de la partie
	float lastTime; // L'ancien temps obtenu
	float lastTimeBomberman;
	float currentTime; // Le temps actuel obtenu avec SDL_GetTicks()
	float timeFrame; // Le nombre de secondes attendues	
	float deltaTime; // La différence de temps entre lastTime et currentTime
	float timeFrame2; //Temps pour la deuxieme bombe
	float timeFrameEnnemi;

	SDL_Surface* gameOverBMP;

};

