#ifndef MINIMAL
#define MINIMAL

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define NB_VERTEX_CIRCLE 360
#define NB_GRAD 60

/* Dessine un carré de coté 1 ayant pour centre les coordonnées de la souris */
void drawSquare();

/* Dessine un cercle d'origine 0,0 et de diamètre 1 */
void drawCircle(int full);

/* Dessine le cadran de l'horloge */
void createClockIDList(GLuint id);

/* Affiche l'heure courante */
void displayTime(int hour, int minute, int second);

#endif