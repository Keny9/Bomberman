#pragma once
#include <SDL.h>

class Bomb {

private:

	int	nbBombeEnJeu; // Le nombre de bombe en jeu 
	int	nbBombeInventaire; // Nombre de bombes max auquel le personnage a droit
	int	bombeSpriteX;
	int	bombeSpriteY;
	int	explosionSpriteX;
	int	explosionSpriteY;
	int	frameBombe; // Nb image de la bombe
	int	frameExplosion;
	int	completeAnimation; // Nombre d'animations complet

	bool showBombe; // Montrer la bombe
	bool showExplosion; // Montrer l'explosion
	bool explosionEnCours; // Explosion en cours

	float bombeX; // Position de la bombe
	float bombeY;

	SDL_Surface* bombe;
	SDL_Surface* explosion;

	SDL_Rect bombeSprite[1][3];
	SDL_Rect explosionSprite[7][4];

	SDL_Rect posBombe; // Position de la bombe
	SDL_Rect posExplosion; // Position de l'explosion

public:

	Bomb(); // Constructeur de la classe
	~Bomb(); // Déconstructeur

	 // Les différentes méthodes de la classe Bomb
	void faireBombe();
	void faireExplosion();
	void animerBombe(float &timeFrame);
	bool montrerBombe();
	void poserBombe();
	void initializePosBombe(SDL_Rect positionBonhomme);
	void initializePosExplosion();
	void animerExplosion(float timeFrame, SDL_Surface* background, bool bas, bool haut, bool gauche, bool droite);
	void faireApparaitreBombe(SDL_Surface* background);

	SDL_Rect getPositionBomb();

	bool getExplosion();

};

