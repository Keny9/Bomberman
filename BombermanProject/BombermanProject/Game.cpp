#include "Game.h"
#include "SDL_mixer.h"


Game::Game(SDL_Window* w, SDL_Surface* b) : bomb(new Bomb()), bomb2(new Bomb()), map(new Map()), 
											bomberman(new Bomberman(w)), audio(new Music()), points(new Points(b))
{
	langueFolle.push_back(new LangueFolle(w, 250.0f, 50.0f));
	langueFolle.push_back(new LangueFolle(w, 450.0f, 450.0f));
	langueFolle.push_back(new LangueFolle(w, 250.0f, 300.0f));
	langueFolle.push_back(new LangueFolle(w, 550.0f, 100.0f));
	
	window = w; // Fenêtre
	background = b; // Surface
	gameOver = false;

	lastTime = 0.0f; // L'ancien temps obtenu
	lastTimeBomberman = 0.0f;
	currentTime = 0.0f; // Le temps actuel obtenu avec SDL_GetTicks()
	timeFrame = 0.0f; // Le nombre de secondes attendues	
	timeFrame2 = 0.0f; //Pour la deuxieme bombe
	deltaTime = 0.0f; // La différence de temps entre lastTime et currentTime
	timeFrameEnnemi = 0.0f;

	gamePoints = 0;

	gameOverBMP = SDL_LoadBMP("gameover.bmp");
}

void Game::start() {

	map->ouvrirFichier();	// Ouvrir le fichier dans lequel on veut lire

	map->lireFichier();	// Lire dans le fichier

	audio->startMusic(); // Commence la musique du jeu

	while (gameOver == false) {
	
		SDL_FillRect(background, NULL, SDL_MapRGB(background->format, 50, 50, 50)); // Nettoyer l'écran

		currentTime = SDL_GetTicks(); // Obtenir le temps courant

		deltaTime = currentTime - lastTime; // Obtenir la différence de temps entre le dernier temps pris en compte et le temps actuel

		timeFrame += deltaTime; // Le temps entre l'ancien et le nouveau temps courant  

		timeFrame2 += deltaTime;

		timeFrameEnnemi += deltaTime;

		SDL_PumpEvents();
		const Uint8 * keys = SDL_GetKeyboardState(NULL);

		if (keys[SDL_GetScancodeFromKey(SDLK_ESCAPE)])
		{
			gameOver = true; // Le joueur veut quitter
		}

		if (keys[SDL_GetScancodeFromKey(SDLK_SPACE)])
		{
			if (bomb->montrerBombe()) // Est-ce qu'on montre la bombe
			{
				bomb->poserBombe();	// On pose la bombe
			}
		}

		if (keys[SDL_GetScancodeFromKey(SDLK_e)]) // Si le joueur a unlock une deuxième bombe
		{
			if (bomb2->montrerBombe() && bomberman->getBombePlus() == true) // Est-ce qu'on montre la deuxième bombe
			{
				bomb2->poserBombe();	// On pose la deuxième bombe
			}
		}
		

		map->generateMap(background,bomberman->getVitesse(),bomberman->getBombePlus()); // Générer la map
		for (int i = 0; i < langueFolle.size(); i++) {

			langueFolle.at(i)->initializeEnemySprites();

			langueFolle.at(i)->walksAround(background, timeFrameEnnemi, map->tblIntMap, map->tblRectMap, bomberman->getDestination());
		}
		
		if (bomberman->getIsDead() == false) {

			bomberman->changeDirection(keys, background, map->tblRectMap, map->tblIntMap); // Changement de position du bonhomme

			bomberman->walk(lastTimeBomberman, background); // Faire marcher le bonhomme

			if (bomberman->getBombePlus() == true) // Si on a une deuxième bombe
			{
				bomb2->initializePosBombe(bomberman->getDestination()); // Initialiser la position de la bombe à la position du personnage 

				bomb2->initializePosExplosion(); // Initialiser la position de la bombe a la position du personnage

				bomb2->animerBombe(timeFrame2); // Animer la bombe

				bomb2->animerExplosion(timeFrame2, background, map->getBas2(), map->getHaut2(), map->getGauche2(), map->getDroite2()); // Animer l'explosion
			}

			bomb->initializePosBombe(bomberman->getDestination()); // Initialiser la position de la bombe à la position du personnage 

			bomb->initializePosExplosion(); // Initialiser la position de la bombe a la position du personnage

			bomb->animerBombe(timeFrame); // Animer la bombe

			bomb->animerExplosion(timeFrame, background, map->getBas(), map->getHaut(), map->getGauche(), map->getDroite()); // Animer l'explosion

			map->destroyWalls(bomb->getPositionBomb(), bomb->getExplosion(), bomb2->getPositionBomb(), bomb2->getExplosion(), gamePoints, timeFrame);

			bomb->faireApparaitreBombe(background);

			bomb2->faireApparaitreBombe(background);

			checkBombermanInvincibility(SDL_GetTicks());

			for (int i = 0; i < langueFolle.size(); i++) {

				if (bomberman->getIsInvincible() == false
					&& (map->bombDamageBomberman(bomb->getPositionBomb(), bomb->getExplosion(), bomberman->getDestination()) == true
						|| map->enemyDamageBomberman(bomberman->getDestination(), langueFolle.at(i)->getPositionLangueFolle()) == true)) { // Si bomberman se trouve dans le rayon d'explosion, perd une vie

					bomberman->setLastTimeTookDamage(SDL_GetTicks());
					bomberman->setIsInvincible(true);

					if (bomberman->getLife() > 0) {
						bomberman->removeLife(1);
					}

					if (bomberman->getLife() == 0) {
						bomberman->setDead(true);
					}
				}

				if (map->bombDamageEnemy(bomb->getPositionBomb(), bomb->getExplosion(), langueFolle.at(i)->getPositionLangueFolle()) == true) {

					if (timeFrame < 1 && langueFolle.at(i)->getIsDead() == false) {
						gamePoints += 100;
					}
					langueFolle.at(i)->setIsDead(true);
				}
			}
		}

		else if (bomberman->getIsDead() == true) {
			bomberman->die(background, window);
			gameOver = true;
		}
		
		bomberman->showLives(background, window);

		points->showGamePoints(gamePoints);

		map->reinitialisation();

		lastTime = currentTime; // Devient le temps actuel avant d'en obtenir un nouveau
			
		SDL_UpdateWindowSurface(window); // Mettre à jour la surface 
	}
}


void Game::checkBombermanInvincibility(float currentTime) {

	if (bomberman->getIsInvincible() == true && (currentTime - bomberman->getLastTimeTookDamage()) > 6000) {
		bomberman->setIsInvincible(false);
	}
}

void Game::showEndGameScreen() {

	SDL_Rect position = { 300, 300, 0, 0 };

	SDL_SetColorKey(gameOverBMP, SDL_TRUE, SDL_MapRGB(gameOverBMP->format, 0, 255, 0)); // Set transparency

	SDL_BlitSurface(gameOverBMP, NULL, background, &position);
}

Game::~Game()
{
}
