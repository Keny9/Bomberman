#pragma once
#include <SDL.h>

class Bomberman
{
public:
	Bomberman(SDL_Window* w);
	~Bomberman();

	// M�thodes
	void changeDirection(const Uint8 * keys, SDL_Surface* screenSurface, SDL_Rect tblRectMap[13][15], int tblIntMap[13][15]);

	/*
	Fonction pour faire marcher le bonhomme
	lastTime: la derni�re fois que PollEvent a retourn� 1 en millisecondes
	screenSurface: surface sur laquelle le bomberman est affich�
	*/
	void walk(float &lastTime, SDL_Surface* screenSurface);

	/*
	Fonction pour faire marcher le bonhomme
	dyingBomberman: tableau contenant les sprites d'animation de la mort du bomberman
	screenSurface: surface sur laquelle le bomberman est affich�
	destination: position � laquelle le bomberman se situe � sa mort et o� l'animation doit se faire
	window: pour rafra�chir l'affichage dans la fen�tre
	*/
	void die(SDL_Surface* screenSurface, SDL_Window* window);

	// Affiche le nombre de vies restantes
	void showLives(SDL_Surface * screenSurface, SDL_Window * window);

	// Trouve les coordonn�es de bomberman dans la grille 
	void findCoordinatesInMap();

	SDL_Rect getDestination();

	// Get the position of Bomberman for the bomb placement
	int getRightX();
	int getLowerY();

	// Get the lives left
	int getLife();
	// Set the new lives left after taking damage
	void removeLife(int damage);
	void setDead(bool dead);
	bool getIsDead();

	int leftX;
	int upperY;
	int rightX;
	int lowerY;

	bool getVitesse();
	bool getBombePlus();
	int getAnimationDead();
	
	void setLastTimeTookDamage(float time);
	float getLastTimeTookDamage();

	void setIsInvincible(bool invincible);
	bool getIsInvincible();


private:
	// Constantes
	const int IDLE_SPRITE_ANIMATION_INDEX = 2;
	const char *WALKING_SPRITES_FILE = "bomberman.bmp";
	const char *DYING_SPRITES_FILE = "bombermandie.bmp";
	const char *HEART_SPRITE = "life.bmp";
	const char *STAR_SPRITE = "star.bmp";

	const float INITIAL_X_POSITION = 50.0f;
	const float INITIAL_Y_POSITION = 50.0f;
	const int DYING_ANIMATION_FRAMES = 8;
	const int WALKING_DIRECTIONS_FRAMES = 4;
	const int WALKING_FRAMES = 5;


	// Attributs
	bool isDead;
	unsigned int nbLives;
	bool wasExecuted;

	float lastTimeTookDamage;
	bool isInvincible;

	SDL_Window* window;
	SDL_Surface* walkingSprites;
	SDL_Surface* dyingSprites;
	SDL_Surface* heartSprite;
	SDL_Surface* starSprite;

	// Coordonn�es initiales du bonhomme
	float positionImageX;
	float positionImageY;
	float vitesse;

	// Position du walkingSprites dans la fen�tre
	SDL_Rect destination;
	// Prochaine destination � laquelle on veut d�placer bomberman
	SDL_Rect nextDestination;

	// Direction � laquelle le bonhomme fait face (lignes)
	int dir;
	// D�placements du bonhomme sur la spritesheet (colonnes)
	int dep;

	bool depLastSprite;
	bool animateWalk;
	bool vitesseTaken;
	bool bombePlus;

	// Table containing sprites from the sprite sheets
	SDL_Rect walkingBomberman[4][5];
	SDL_Rect dyingBomberman[8];
	SDL_Rect lifeBomberman;

	int nbAnimationDead;

	// M�thodes 
	void initializeSprites(SDL_Rect walkingBomberman[4][5], SDL_Rect dyingBomberman[8]);
	void initializeWalkingSprites(SDL_Rect walkingBomberman[4][5]);
	void initializeDyingSprites(SDL_Rect dyingBomberman[8]);

};

