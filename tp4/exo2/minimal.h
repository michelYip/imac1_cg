#ifndef MINIMAL
#define MINIMAL

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 11
#define TIME_SIZE 9

/* Chargement de la texture : utilisation similaire à malloc() */
void loadTextures(SDL_Surface * textures[SIZE]);

/* Configuration + Traitement des textures et libération mémoire CPU */
void configTextures(SDL_Surface * textures[SIZE], GLuint textureID[SIZE]);

/* Affiche l'heure courante */
void displayTime(char strTime[TIME_SIZE], GLuint textureID[SIZE]);

#endif