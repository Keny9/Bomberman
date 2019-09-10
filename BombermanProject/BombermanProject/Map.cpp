#include "Map.h"

Map::Map() // Constructeur
{
	positionImageX = 0;
	positionImageY = 0;
	valeurMap = 0;
	mapFile = "map1.txt";
	tblRectMap[13][15] = {};
	tblIntMap[13][15] = {};
	showBas = false;
	showHaut = false;
	showGauche = false;
	showDroite = false;

	showBas2 = false;
	showHaut2 = false;
	showDroite2 = false;
	showGauche2 = false;

	indestructible = SDL_LoadBMP("indestructible.bmp");
	destructible = SDL_LoadBMP("destructible.bmp");
	titleScreen = SDL_LoadBMP("titleScreen.bmp");
	vitesse = SDL_LoadBMP("vitesse.bmp");
	door = SDL_LoadBMP("door.bmp");
	bombePower = SDL_LoadBMP("bombePower.bmp");
}

Map::~Map() //Destructeur
{
	SDL_FreeSurface(indestructible);
	SDL_FreeSurface(destructible);
	SDL_FreeSurface(titleScreen);
	SDL_FreeSurface(vitesse);
	SDL_FreeSurface(door);
	SDL_FreeSurface(bombePower);
}

void Map::ouvrirFichier() // Ouvrir le fichier
{
	entree.open(mapFile);
}

void Map::lireFichier()
{
	for (int i = 0; i < 13; i++) // Sert à mettre les valeur de la map dans le tableau
	{
		for (int j = 0; j < 15; j++)
		{
			entree >> valeurMap;
			tblIntMap[i][j] = valeurMap;
		}
	}
}

void Map::generateMap(SDL_Surface* background,bool vitesseTaken,bool bombePlus) { //Générer la carte

	initialiserRectPosition(tblRectMap);

	for (int i = 0; i < 13; i++) {

		for (int j = 0; j < 15; j++) {

			if (tblIntMap[i][j] == 1) {
				SDL_BlitSurface(destructible, NULL, background, &tblRectMap[i][j]); // Affiche les blocs destructibles
			}

			else if (tblIntMap[i][j] == 2) {
				SDL_BlitSurface(indestructible, NULL, background, &tblRectMap[i][j]); // Affiche les blocs indestructibles
			}
		}
	}

	if (tblIntMap[1][4] == 0 && bombePlus == false)
	{
		SDL_BlitSurface(bombePower, NULL, background, &tblRectMap[1][4]);
	}

	if (tblIntMap[7][10] == 0 && vitesseTaken == false)
	{
		SDL_BlitSurface(vitesse, NULL, background, &tblRectMap[7][10]);
	}
	else
	{
		SDL_BlitSurface(NULL, NULL, background, &tblRectMap[7][10]);
	}

	if (tblIntMap[11][6] == 0)
	{
		SDL_BlitSurface(door, NULL, background, &tblRectMap[11][6]);
	}
}

void Map::initialiserRectPosition(SDL_Rect tblRectMap[13][15]) // Initialise les positions des rectangles sur la grille
{
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 15; j++) {
			tblRectMap[i][j].h = 50;
			tblRectMap[i][j].w = 50;
			tblRectMap[i][j].x = j * 50;
			tblRectMap[i][j].y = i * 50;
		}
	}
}

void Map::reinitialisation() // Réinitialise les valeurs de l'axe X et Y
{
	positionImageX = 0;
	positionImageY = 0;
}


void Map::destroyWalls(SDL_Rect positionBombe, bool explosion, SDL_Rect positionBombe2, bool explosion2, int &gamePoints, float timeFrame) { // Collision et destruction des murs 

	int posX = positionBombe.x / 50; // Premiere bombe
	int posY = positionBombe.y / 50;

	int posX2 = positionBombe2.x / 50; // Deuxieme bombe
	int posY2 = positionBombe2.y / 50;

	if (explosion == true) { // Premiere bombe collision
		if (tblIntMap[posY + 1][posX] == 1) {
			tblIntMap[posY + 1][posX] = 0;

			if (timeFrame  < 1.0f) {
				gamePoints += 50;
			}
		}

		if (tblIntMap[posY + 1][posX] == 0) {
			showBas = true;
		}

		if (tblIntMap[posY - 1][posX] == 1) {
			tblIntMap[posY - 1][posX] = 0;

			if (timeFrame  < 1.0f) {
				gamePoints += 50;
			}
		}

		if (tblIntMap[posY - 1][posX] == 0) {
			showHaut = true;
		}

		if (tblIntMap[posY][posX + 1] == 1) {
			tblIntMap[posY][posX + 1] = 0;

			if (timeFrame < 1.0f) {
				gamePoints += 50;
			}
		}

		if (tblIntMap[posY][posX + 1] == 0) {
			showDroite = true;
		}

		if (tblIntMap[posY][posX - 1] == 1) {
			tblIntMap[posY][posX - 1] = 0;

			if (timeFrame  < 1.0f) {
				gamePoints += 50;
			}
		}

		if (tblIntMap[posY][posX - 1] == 0) {
			showGauche = true;
		}
	}
		
	if (explosion2 == true) { // Deuxième bombe collision
		if (tblIntMap[posY2 + 1][posX2] == 1 || tblIntMap[posY2 + 1][posX2] == 0) {
			tblIntMap[posY2 + 1][posX2] = 0;
			showBas2 = true;
		}
		if (tblIntMap[posY2 - 1][posX2] == 1 || tblIntMap[posY2 - 1][posX2] == 0) {
			tblIntMap[posY2 - 1][posX2] = 0;
			showHaut2 = true;
		}
		if (tblIntMap[posY2][posX2 + 1] == 1 || tblIntMap[posY2][posX2 + 1] == 0) {
			tblIntMap[posY2][posX2 + 1] = 0;
			showDroite2 = true;
		}
		if (tblIntMap[posY2][posX2 - 1] == 1 || tblIntMap[posY2][posX2 - 1] == 0) {
			tblIntMap[posY2][posX2 - 1] = 0;
			showGauche2 = true;
		}
	}

	if (explosion == false) // Rectangle qui s'affiche de la bombe 1
	{
		showBas = false;
		showHaut = false;
		showDroite = false;
		showGauche = false;
	}

	if (explosion2 == false) // Rectangle qui s'affiche de la bombe 2
	{
		showBas2 = false;
		showHaut2 = false;
		showDroite2 = false;
		showGauche2 = false;
	}

}

bool Map::bombDamageBomberman(SDL_Rect positionBombe, bool explosion, SDL_Rect positionBomberman) {

	int posBombX = positionBombe.x / 50;
	int posBombY = positionBombe.y / 50;

	int posBombermanX = (positionBomberman.x + 10) / 50;
	int posBombermanY = (positionBomberman.y + 16) / 50;

	if (explosion == true) {

		// Check if bomb and bomberman are in the same case of the map
		if ((posBombX == posBombermanX && posBombY == posBombermanY)
			|| (posBombX + 1 == posBombermanX && posBombY == posBombermanY)
			|| (posBombX - 1 == posBombermanX && posBombY == posBombermanY)
			|| (posBombX == posBombermanX && posBombY + 1 == posBombermanY)
			|| (posBombX == posBombermanX && posBombY - 1 == posBombermanY)) {

			return true;
		}
	}

	return false;
}

bool Map::bombDamageEnemy(SDL_Rect positionBombe, bool explosion, SDL_Rect positionLangueFolle) {

	int posBombX = positionBombe.x / 50;
	int posBombY = positionBombe.y / 50;

	int positionLangueFolleX = (positionLangueFolle.x + 12) / 50;
	int positionLangueFolleY = (positionLangueFolle.y + 13) / 50;

	if (explosion == true) {

		// Check if bomb and bomberman are in the same case of the map
		if ((posBombX == positionLangueFolleX && posBombY == positionLangueFolleY)
			|| (posBombX + 1 == positionLangueFolleX && posBombY == positionLangueFolleY)
			|| (posBombX - 1 == positionLangueFolleX && posBombY == positionLangueFolleY)
			|| (posBombX == positionLangueFolleX && posBombY + 1 == positionLangueFolleY)
			|| (posBombX == positionLangueFolleX && posBombY - 1 == positionLangueFolleY)) {

			return true;
		}
	}

	return false;
}

bool Map::enemyDamageBomberman(SDL_Rect positionBomberman, SDL_Rect positionLangueFolle) {

	int posBombermanX = (positionBomberman.x + 10) / 25;
	int posBombermanY = (positionBomberman.y + 16) / 25;

	int positionLangueFolleX = (positionLangueFolle.x + 12) / 25;
	int positionLangueFolleY = (positionLangueFolle.y + 12) / 25;

	if (positionLangueFolleX == posBombermanX && positionLangueFolleY == posBombermanY) {

		return true;
	}

	return false;
}

bool Map::getHaut()
{
	return showHaut;
}

bool Map::getBas()
{
	return showBas;
}
									
bool Map::getGauche()
{
	return showGauche;
}

bool Map::getDroite()
{
	return showDroite;
}

bool Map::getHaut2()
{
	return showHaut2;
}

bool Map::getBas2()
{
	return showBas2;
}

bool Map::getGauche2()
{
	return showGauche2;
}

bool Map::getDroite2()
{
	return showDroite2;
}