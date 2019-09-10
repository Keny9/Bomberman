#pragma once
#include <SDL.h>

class LangueFolle
{
//attributs
private:
	int animationDeplacement;		//  ordre de d�placement li� avec sprite
	int i;
	int j;

	const int LARGEUR_ENNEMI = 25;
	const int HAUTEUR_ENNEMI = 26;

	float positionImageX;
	float positionImageY;
	float currentTime;

	float velociteX;  //vitesse de d�placement sur l'axe des X
	float velociteY; //vitesse de d�placement sur l'axe des Y
	float tempsPrecedent;
	float tempsDelta;
	float tempsPasseSprite; // temps pass� depuis le d�but de l'ex�cution du programme
	float tempsPasseDirection;
	float tempsPasseDefilement;
	int	deplacementDirection;    //0 = droite, 1 = gauche, 2 = haut, 3 = bas
	bool isDead;

	SDL_Surface* enemySprites;
	SDL_Rect destination;
	SDL_Window* window;
	SDL_Rect tblSpriteEnnemi[3];  // sprite d'animation � trois phases

public:

	LangueFolle(SDL_Window* w, float positionStartX, float positionStartY);
	~LangueFolle();

	SDL_Rect nextDestination;

	int leftX;
	int upperY;
	int rightX;
	int lowerY;

// M�thodes
	void walksAround(SDL_Surface* screenSurface, float timeFrameEnnemi, int tblIntMap[13][15], SDL_Rect tblRectMap[13][15], SDL_Rect positionBonhomme);

	SDL_Rect getPositionLangueFolle();
	void setIsDead(bool death);
	bool getIsDead();
	void initializeEnemySprites();
	
	void findCoordinatesInMap();

};

