// Classe LangueFolle pour l'enemySprites de niveau 1 du jeu Bomberman

//ajouter les chronomètres temps Delta et autre timer que j'ai enlevés.  comparer avec bombe.cpp

#include "LangueFolle.h"

LangueFolle::LangueFolle(SDL_Window* w, float positionStartX, float positionStartY)
{
	window = w;
	animationDeplacement = 0;		//  ordre de déplacement lié avec sprite

	positionImageX = positionStartX;
	positionImageY = positionStartY;
	currentTime = 0;

	i = 1;
	j = 1;

	velociteX = 0.1/2;  //vitesse de déplacement sur l'axe des X
	velociteY = 0.1/2; //vitesse de déplacement sur l'axe des Y
	tempsPrecedent = 0;
	tempsDelta = 0;
	tempsPasseSprite = 0; // temps passé depuis le début de l'exécution du programme
	tempsPasseDirection = 0;
	tempsPasseDefilement = 0;
	deplacementDirection = 0;    //0 = droite, 1 = gauche, 2 = haut, 3 = bas
	isDead = false;

	enemySprites = SDL_LoadBMP("LangueFolle.bmp");

	tblSpriteEnnemi[3] = {};
	initializeEnemySprites();
}

LangueFolle::~LangueFolle()
{
	SDL_FreeSurface(enemySprites);
	enemySprites = NULL;
}

void LangueFolle::initializeEnemySprites()
{
	SDL_SetColorKey(enemySprites, SDL_TRUE, SDL_MapRGB(enemySprites->format, 255, 242, 0)); // transparence du sprite de l'enemySprites

	for (int i = 0; i < 3; i++)
	{
		tblSpriteEnnemi[i].x = 24 * i;
		tblSpriteEnnemi[i].y = 0;
		tblSpriteEnnemi[i].w = 24;
		tblSpriteEnnemi[i].h = 26;
	}
}

void LangueFolle::walksAround(SDL_Surface* screenSurface, float timeFrameEnemy, int tblIntMap[13][15], SDL_Rect tblRectMap[13][15], SDL_Rect positionBonhomme)
{
	float prochainePositionX = positionImageX;
	float prochainePositionY = positionImageY;

	if (deplacementDirection == 4)
	{
		deplacementDirection = 0;
	}

	if (isDead == false) // Si LangueFolle est mort, il ne s'affiche plus.
	{
		if (timeFrameEnemy > 70) // Si 50 ms se sont écoulées
		{
			// changement de sprite selon le temps

			animationDeplacement++;
			if (animationDeplacement == 3)
			{
				animationDeplacement = 1;
				animationDeplacement--;
			}

			// enemySprites change de directions lorque rencontre un obstacle

			if (deplacementDirection == 0)//0= droite
			{
				prochainePositionX += velociteX;
			}

			else if (deplacementDirection == 2)// 2= gauche
			{
				prochainePositionX -= velociteX;
			}

			else if (deplacementDirection == 1)// 1= haut
			{
				prochainePositionY -= velociteY;
			}

			else if (deplacementDirection == 3)// 3= bas
			{
				prochainePositionY += velociteY;
			}

			timeFrameEnemy = 0;
		}


		nextDestination.x = prochainePositionX;
		nextDestination.y = prochainePositionY;
		nextDestination.w = 100;
		nextDestination.h = 100;

		findCoordinatesInMap(); // Donne l'emplacement de l'ennemi sur la grille

		if (tblIntMap[upperY][leftX] == 0 && tblIntMap[lowerY][rightX] == 0 && tblIntMap[lowerY][leftX] == 0 && tblIntMap[upperY][rightX] == 0) {
			destination = nextDestination;
			positionImageX = prochainePositionX;
			positionImageY = prochainePositionY;
		}

		else {
			deplacementDirection++;
		}

		SDL_BlitSurface(enemySprites, &tblSpriteEnnemi[animationDeplacement], screenSurface, &destination);
	}
}

void LangueFolle::findCoordinatesInMap() {

	leftX = nextDestination.x / 50;
	upperY = nextDestination.y / 50;
	rightX = (nextDestination.x + 24) / 50;
	lowerY = (nextDestination.y + 26) / 50;
}

SDL_Rect LangueFolle::getPositionLangueFolle() {
	return destination;
}

void LangueFolle::setIsDead(bool death) {
	isDead = death;
}

bool LangueFolle::getIsDead() {
	return isDead;
}