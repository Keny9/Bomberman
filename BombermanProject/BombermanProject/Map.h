#pragma once

#include <SDL.h>
#include <fstream>
#include <string>

using namespace std;

class Map
{
private:

	int positionImageX;
	int positionImageY;
	int valeurMap;
	
	bool showHaut; //Quelle partie de l'explosion sont montrées
	bool showBas;
	bool showDroite;
	bool showGauche;

	bool showHaut2; //Les parties de la deuxieme bombe si le power-up a été récupérer
	bool showBas2;
	bool showDroite2;
	bool showGauche2;

	ifstream entree;

	string mapFile;

	SDL_Surface* indestructible;
	SDL_Surface* destructible;  // Bloc destructible
	SDL_Surface* titleScreen; // Écran titre
	SDL_Surface* vitesse; //PowerUp pour courrir plus vite
	SDL_Surface* door; //Porte de sortie
	SDL_Surface* bombePower; //Power-up une bombe de plus en inventaire

public:

	SDL_Rect tblRectMap[13][15];
	int tblIntMap[13][15];
	Map(); // Constructeur de la classe
	~Map();	// Destructeur

	void ouvrirFichier();
	void lireFichier();
	void generateMap(SDL_Surface * background,bool vitesseTaken, bool bombePlus);
	void initialiserRectPosition(SDL_Rect tabRectMap[13][15]);
	void reinitialisation();

	void destroyWalls(SDL_Rect positionBombe, bool explosion,SDL_Rect positionBombe2, bool explosion2, int &gamePoints, float timeFrame);
	bool bombDamageBomberman(SDL_Rect positionBombe, bool explosion, SDL_Rect positionBomberman);
	bool bombDamageEnemy(SDL_Rect positionBombe, bool explosion, SDL_Rect positionLangueFolle);
	bool enemyDamageBomberman(SDL_Rect positionBomberman, SDL_Rect positionLangueFolle);

	bool getHaut();
	bool getBas();
	bool getGauche();
	bool getDroite();

	bool getHaut2();
	bool getBas2();
	bool getGauche2();
	bool getDroite2();


};
