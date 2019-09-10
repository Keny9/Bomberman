// Classe Bomberman pour le personne principal du jeu

#include "Bomberman.h"

Bomberman::Bomberman(SDL_Window* w)
{
	window = w;

	nbLives = 5;
	isDead = false;
	isInvincible = false;

	dep = IDLE_SPRITE_ANIMATION_INDEX;
	dir = 0;
	depLastSprite = false;
	animateWalk = false;
	vitesseTaken = false;
	bombePlus = false;

	positionImageX = INITIAL_X_POSITION;
	positionImageY = INITIAL_Y_POSITION;
	vitesse = 0.0999f;

	walkingSprites = SDL_LoadBMP(WALKING_SPRITES_FILE);
	dyingSprites = SDL_LoadBMP(DYING_SPRITES_FILE);
	heartSprite = SDL_LoadBMP(HEART_SPRITE);
	starSprite = SDL_LoadBMP(STAR_SPRITE);

	dyingBomberman[DYING_ANIMATION_FRAMES] = {};
	walkingBomberman[WALKING_DIRECTIONS_FRAMES][WALKING_FRAMES] = {};

	initializeSprites(walkingBomberman, dyingBomberman);

	nbAnimationDead = 0;
}

void Bomberman::initializeSprites(SDL_Rect walkingBomberman[4][5], SDL_Rect dyingBomberman[8]) {


	SDL_SetColorKey(walkingSprites, SDL_TRUE, SDL_MapRGB(walkingSprites->format, 255, 0, 0)); // Set transparency

	SDL_SetColorKey(dyingSprites, SDL_TRUE, SDL_MapRGB(dyingSprites->format, 255, 0, 0)); // Set transparency

	SDL_SetColorKey(heartSprite, SDL_TRUE, SDL_MapRGB(heartSprite->format, 0, 255, 0)); // Set transparency

	SDL_SetColorKey(starSprite, SDL_TRUE, SDL_MapRGB(starSprite->format, 0, 255, 0)); // Set transparency

	initializeWalkingSprites(walkingBomberman);
	initializeDyingSprites(dyingBomberman);
}

void Bomberman::initializeWalkingSprites(SDL_Rect walkingBomberman[4][5]) { // Initialize walking sprites

	float spriteWidth = 0.0f;
	float spriteHeight = 0.0f;

	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			spriteWidth = 21.2f;
			spriteHeight = 35.0f;
			break;
		case 1:
			spriteWidth = 21.6f;
			spriteHeight = 34.0f;
			break;
		case 2:
			spriteWidth = 21.6f;
			spriteHeight = 33.0f;
			break;
		case 3:
			spriteWidth = 21.4f;
			spriteHeight = 32.0f;
			break;
		}
		for (int j = 0; j < 5; j++) { // 1ere ligne de la spritesheet
			walkingBomberman[i][j].x = (float)j * spriteWidth;
			walkingBomberman[i][j].y = (float)i*spriteHeight;
			walkingBomberman[i][j].w = spriteWidth;
			walkingBomberman[i][j].h = spriteHeight;
		}
	}
}

void Bomberman::initializeDyingSprites(SDL_Rect dyingBomberman[8]) { // Initialize death sprites

	float spriteWidth = 0.0f;
	float spriteWidthCompiled = 0.0f;
	for (int j = 0; j < 8; j++) {
		if (j == 6 || j == 0 || j == 1 || j == 7) {
			spriteWidth = 21.0f;
		}
		else if (j == 2 || j == 4) {
			spriteWidth = 25.0f;
		}
		else if (j == 5) {
			spriteWidth = 20.0f;
		}
		else if (j == 3) {
			spriteWidth = 30.0f;
		}

		dyingBomberman[j].x = spriteWidthCompiled;
		dyingBomberman[j].y = 0;
		dyingBomberman[j].w = spriteWidth;
		dyingBomberman[j].h = 35;

		spriteWidthCompiled += spriteWidth;
	}

}

void Bomberman::changeDirection(const Uint8 * keys, SDL_Surface* screenSurface, SDL_Rect tblRectMap[13][15], int tblIntMap[13][15]) {

	float prochainePositionX = positionImageX;
	float prochainePositionY = positionImageY;

	if (keys[SDL_GetScancodeFromKey(SDLK_d)]) {
		dir = 1;
		prochainePositionX += vitesse;
		animateWalk = true;
	}

	else if (keys[SDL_GetScancodeFromKey(SDLK_a)]) {
		dir = 3;
		prochainePositionX -= vitesse;
		animateWalk = true;
	}

	else if (keys[SDL_GetScancodeFromKey(SDLK_w)]) {
		dir = 2;
		prochainePositionY -= vitesse;
		animateWalk = true;
	}

	else if (keys[SDL_GetScancodeFromKey(SDLK_s)]) {
		dir = 0;
		prochainePositionY += vitesse;
		animateWalk = true;
	}

	else {
		dep = 2;
		animateWalk = false;
	}

	nextDestination.x = prochainePositionX;
	nextDestination.y = prochainePositionY;
	nextDestination.w = 100;
	nextDestination.h = 100;

	findCoordinatesInMap(); // Donne l'emplacement de bomberman sur la grille

	if (tblIntMap[upperY][leftX] == 0 && tblIntMap[lowerY][rightX] == 0 && tblIntMap[lowerY][leftX] == 0 && tblIntMap[upperY][rightX] == 0) {
		destination = nextDestination;
		positionImageX = prochainePositionX;
		positionImageY = prochainePositionY;
	}

	if (destination.x >= tblRectMap[7][10].x && destination.x <= tblRectMap[7][10].x + 50 && destination.y >= tblRectMap[7][10].y && destination.y <= tblRectMap[7][10].y + 50) // Power-up vitesse
	{
		vitesse = 0.2f;
		vitesseTaken = true;
	}

	if (destination.x >= tblRectMap[1][4].x && destination.x <= tblRectMap[1][4].x + 50 && destination.y >= tblRectMap[1][4].y && destination.y <= tblRectMap[1][4].y + 50) // Power-up bombe
	{
		bombePlus = true;
	}

}

void Bomberman::walk(float &lastTime, SDL_Surface* screenSurface) {

	int currentTime = SDL_GetTicks();

	if (animateWalk && (currentTime - lastTime) > 70) // Si 70 ms se sont écoulées
	{
		if (depLastSprite == true) {
			dep--;
			if (dep == -1) {
				depLastSprite = false;
				dep = 2;
			}
		}
		else if (depLastSprite == false) {
			dep++;
			if (dep == 5) {
				depLastSprite = true;
				dep = 2;
			}
		}

		lastTime = currentTime; // Le temps "actuel" devient le temps "precedent" pour nos futurs calculs

	}

	SDL_BlitSurface(walkingSprites, &walkingBomberman[dir][dep], screenSurface, &destination); // Affichage du walkingSprites

}

void Bomberman::die(SDL_Surface* screenSurface, SDL_Window* window)
{
	for (int i = 0; i < 8; i++) {

		SDL_BlitSurface(dyingSprites, &dyingBomberman[i], screenSurface, &destination); // Affichage du walkingSprites
		SDL_UpdateWindowSurface(window); // Update the surface 
		SDL_Delay(70);
	}

	nbAnimationDead += 1;
}

void Bomberman::showLives(SDL_Surface* screenSurface, SDL_Window* window) {

	SDL_Rect position = { 70, 660, 0, 0 };

	if (isInvincible == false) {
		int lives = getLife();
		

		for (int i = 0; i < lives; i++) {

			SDL_BlitSurface(heartSprite, NULL, screenSurface, &position); // Affichage du walkingSprites
			position.x += i + 1 * 30;
		}
	}

	else if (isInvincible == true) {
		SDL_BlitSurface(starSprite, NULL, screenSurface, &position);
	}

}

void Bomberman::findCoordinatesInMap() {

	leftX = nextDestination.x / 50;
	upperY = nextDestination.y / 50;
	rightX = (nextDestination.x + 21) / 50;
	lowerY = (nextDestination.y + 32) / 50;
}

SDL_Rect Bomberman::getDestination() {
	return destination;
}

int Bomberman::getRightX() {
	return rightX;
}

int Bomberman::getLowerY() {
	return lowerY;
} 

void Bomberman::removeLife(int damage) {

		nbLives -= damage;
}

int Bomberman::getLife() {
	return nbLives;
}

bool Bomberman::getIsDead() {
	return isDead;
}

void Bomberman::setDead(bool dead) {
	isDead = dead;
}

bool Bomberman::getVitesse()
{
	return vitesseTaken;
}

bool Bomberman::getBombePlus()
{
	return bombePlus;
}

int Bomberman::getAnimationDead()
{
	return nbAnimationDead;
}

void Bomberman::setLastTimeTookDamage(float time) {
	lastTimeTookDamage = time;
}

float Bomberman::getLastTimeTookDamage() {
	return lastTimeTookDamage;
}

void Bomberman::setIsInvincible(bool invincible) {
	isInvincible = invincible;
}

bool Bomberman::getIsInvincible() {
	return isInvincible;
}

Bomberman::~Bomberman() { // Destructeur

	SDL_FreeSurface(walkingSprites);
	SDL_FreeSurface(dyingSprites);
	SDL_FreeSurface(heartSprite);
	walkingSprites = NULL;
	dyingSprites = NULL;
	heartSprite = NULL;
}