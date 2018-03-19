#ifndef MINIMAL
#define MINIMAL

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct planet{
	float radius;
	float distanceToCenter;
	float angle;
	float rotationSpeed;
	float r, g, b;
	struct planet * next;
} Planet, * PlanetList;

/* Dessine un cercle d'origine 0,0 et de diamètre 1 */
void drawCircle(int full);

/* Initialise une planète */
void initPlanet(PlanetList * list, float radius, float distanceToCenter, float rotationSpeed, float, r, float g, float b);

/* Dessine la liste des planètes */
void drawPlanets(PlanetList list);

#endif