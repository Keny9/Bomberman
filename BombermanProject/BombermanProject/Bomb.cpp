#include "Bomb.h"

Bomb::Bomb() //Constructeur de la bombe
{
	nbBombeEnJeu = 0;
	nbBombeInventaire = 1;
	showBombe = false;
	showExplosion = false;
	explosionEnCours = false;

	bombe = SDL_LoadBMP("bombe.bmp");
	explosion = SDL_LoadBMP("explosion.bmp");

	bombeSpriteX = 0;
	bombeSpriteY = 0;
	explosionSpriteX = 0;
	explosionSpriteY = 0;

	frameBombe = 0;
	frameExplosion = 0;

	faireBombe();	//Faire la sprite sheet des bombes
	faireExplosion(); //Faire la sprite sheet des explosions

}

Bomb::~Bomb() //Déconstructeur
{
	SDL_FreeSurface(bombe);
	SDL_FreeSurface(explosion);
}

void Bomb::faireBombe() //Faire le sprite de la bombe
{
	int j = 0,	//Compteur de la boucle
		x = 0,	//Posiiton colonne sprite
		y = 0;	//Position ligne sprite

	for (int i = 0; i < 1; i++) //Ligne
	{
		for (j = 0; j < 3; j++) //Colonne
		{
			bombeSprite[i][j].x = x;
			bombeSprite[i][j].y = y;
			bombeSprite[i][j].h = 50;
			bombeSprite[i][j].w = 49;

			x += 50; //Change de colonne
		}
	}
}

void Bomb::faireExplosion() //Faire le sprite de l'explosion
{
	int x = 0,	//Position colonne
		y = 0;	//Position ligne

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 4; j++) {

			explosionSprite[i][j].x = x;
			explosionSprite[i][j].y = y;
			explosionSprite[i][j].h = 32;
			explosionSprite[i][j].w = 32;

			x += 32; //Change de colonne
		}

		y += 32; //Change de ligne
	}
}

void Bomb::animerBombe(float &timeFrame) //Animation de la bombe
{

	if (timeFrame > 100 && showBombe == true)//Si une seconde est passé
	{
		timeFrame = 0;	//Remettre le timeFrame a 0 pour attendre une nouvelle seconde
		bombeSpriteY++; //Augmenter la position dans le tableau de sprite
		frameBombe++;

		if (bombeSpriteY == 3) //Si on a atteint le maximum de sprite la bombe a explosé
		{
			completeAnimation++;
			bombeSpriteY = 0; //Réinitialise l'image de la bombe au premier sprite

			if (completeAnimation == 10) //Si 10 animations ont été completés
			{
				showBombe = false;		//On ne montre plus la bombe
				completeAnimation = 0;	//Réinitialise le nombre d'animations à 0
				showExplosion = true;  //La bombe explose
			}
		}
	}
}

bool Bomb::montrerBombe() //On vérifie s'il est possible de poser une bombe
{
	if (nbBombeEnJeu < nbBombeInventaire)
	{
		return true;
	}
	return false;
}

void Bomb::poserBombe() // On pose une bombe
{
	showBombe = true;
	nbBombeEnJeu += 1;
	explosionEnCours = true;
}

void Bomb::initializePosBombe(SDL_Rect positionBonhomme) // Donner la position de la bombe
{
	int posX = (positionBonhomme.x + 10) / 50;
	int posY = (positionBonhomme.y + 16) / 50;

	if (nbBombeEnJeu < nbBombeInventaire)
	{
		posBombe.h = 100;
		posBombe.w = 100;
		posBombe.x = posX * 50;
		posBombe.y = posY * 50;
	}
}

void Bomb::initializePosExplosion() //Position fixe de l'explosion
{
	posExplosion.h = 100;
	posExplosion.w = 100;

	if (explosionEnCours == false)
	{
		posExplosion.x = posBombe.x + 10;
		posExplosion.y = posBombe.y + 10;
	}
}

void Bomb::animerExplosion(float timeFrame, SDL_Surface* background,bool bas,bool haut,bool gauche,bool droite) //L'animation de l'explosion
{
	if (showExplosion == true)
	{
		if (timeFrame < 1000)
		{
			SDL_BlitSurface(explosion, &explosionSprite[0][0], background, &posExplosion); //Le centre de l'explosion

			posExplosion.x += 32;

			if (droite == true)
			{
				SDL_BlitSurface(explosion, &explosionSprite[0][5], background, &posExplosion); //L'explosion vers la droite
			}
				posExplosion.x -= 32;
				posExplosion.y -= 32;
			
			if (haut == true)
			{
				SDL_BlitSurface(explosion, &explosionSprite[0][3], background, &posExplosion); //L'explosion vers le haut
			}
				posExplosion.y += 32;
				posExplosion.x -= 32;
	
			if (gauche == true)
			{
				SDL_BlitSurface(explosion, &explosionSprite[0][6], background, &posExplosion); // L'explosion vers la gauche
			}
				posExplosion.y += 32;
				posExplosion.x += 32;
			

			if (bas == true)
			{
				SDL_BlitSurface(explosion, &explosionSprite[0][4], background, &posExplosion); // L'explosion vers le bas
			}				
				posExplosion.y -= 32;			
		}
		else
		{
			showExplosion = false;
			explosionEnCours = false;
			nbBombeEnJeu -= 1;	// Avoir la bombe a nouveau
		}
	}
}

void Bomb::faireApparaitreBombe(SDL_Surface* background) // Faire apparaitre la bombe sur la surface
{
	if (showBombe == true) // Si on peut montrer la bombe et si on peut montrer le sprite sans produire un rectangle invisible
	{
		SDL_BlitSurface(bombe, &bombeSprite[bombeSpriteX][bombeSpriteY], background, &posBombe); // Faire apparaitre la bombe si on peut la montrer
	}
}

SDL_Rect Bomb::getPositionBomb() {
	return posBombe;
}

bool Bomb::getExplosion() {
	return showExplosion;
}