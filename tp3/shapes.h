#ifndef SHAPES
#define SHAPES

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NB_VERTEX_CIRCLE 50

/* Dessine un carré de coté 1 ayant pour centre les coordonnées de la souris */
void drawSquare();

/* Dessine un cercle d'origine 0,0 et de diamètre 1 */
void drawCircle();

/* Dessine un carré à bords arrondis canonique (1 unité de coté) */
void drawRoundedSquare();

/* Dessine un repère orthogonal au centre */
void drawLandmark();

/* Dessine le bras principal */
void drawFirstArm();

/* Dessine le bras manipulateur */
void drawSecondArm();

/* Dessine le batteur */
void drawThirdArm();

/* Dessine le bras mécanique en entier */
void drawFullArm(float alpha, float beta, float gamma);

#endif