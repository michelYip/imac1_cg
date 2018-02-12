#ifndef SHAPES
#define SHAPES

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Point{
	float x,y; //Coordonnées x et y du point
	unsigned char r, g, b; //Composante colorée du point
	struct Point* next; //Point suivant à dessiner si existant
} Point, * PointList;

/* Alloue l'espace mémoire pour stocké un point */
Point * allocPoint(float x, float y, unsigned char r, unsigned char g, unsigned char b);

/* Ajoute le point en fin de liste */
void addPointToList(Point * point, PointList * list);

/* Dessine tout les points de la listes */
void drawPoints(PointList list);

/* Supprime tout les points d'une liste et libère l'espace mémoire */
void deletePoints(PointList * list);

typedef struct Shape{
	GLenum type;
	PointList points;
	struct Shape* next;
} Shape, * ShapeList;

/* Alloue l'espace mémoire pour stocké une primitive */
Shape * allocShape(GLenum type);

/* Ajoute une primitive à la liste de primitive */
void addShape(Shape * shape, ShapeList * list);

/* Dessine la primitive en paramètre */
void drawShape(ShapeList list);

/* Supprime toutes les primitives et libère l'espace mémoire */
void deleteShape(ShapeList * list);

#endif