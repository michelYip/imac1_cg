#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Vec3{
	float x, y, z;
} Point3D, Vector3D;

/**
 * Constuit un point avec les coordonnées x, y, z en paramètre
 * @return Le point Point3D construit avec les coordonnées x, y, z 
 */
Point3D pointXYZ(float x, float y, float z);

/**
 * Construit un vecteur avec les coordonnée x, y, z en paramètre
 * @return Le vecteur Vector3D construit avec les coordonnées x, y, z
 */
Vector3D vectorXYZ(float x, float y, float z);

/**
 * Construit le vecteur AB entre deux Point3D A et B
 * @return Le vecteur correspondant à AB
 */
Vector3D vector(Point3D A, Point3D B);

/**
 * Construit le point P + V
 * @return Le point P + V
 */
Point3D pointPlusVector(Point3D P, Vector3D V);

/**
 * Fonction d'addition de deux vecteurs
 * @return Le vecteur correspondant à A + B
 */
Vector3D addVectors(Vector3D A, Vector3D B);

/**
 * Fonction de soustraction de deux vecteurs
 * @return Le vecteur correspondant à A - B
 */
Vector3D subVectors(Vector3D A, Vector3D B);

/**
 * Fonction de multiplication d'un vecteur par un scalaire
 * @return Le vecteur correspondant à a*V
 */
Vector3D multVector(Vector3D V, float a);

/**
 * Fonction de division d'un vecteur par un scalaire
 * @return Le vecteur correspondant à a/V
 */
Vector3D divVector(Vector3D V, float a);

/**
 * Fonction calculant le produit scalaire de deux vecteur
 * @return Le produit scalaire de A.B
 */
float dot(Vector3D A, Vector3D B);

/**
 * Fonction calculant la norme d'un vecteur
 * @return La norme d'un vecteur V
 */
float norm(Vector3D A);

/**
 * Construit le vecteur normalisé passé en paramètre
 * @return Le vecteur normalisé de A
 */
Vector3D normalize(Vector3D A);

/**
 * Fonction d'affichage d'un point
 */
void printPoint3D(Point3D p);

/**
 * Fonction d'affichage d'un vecteur
 */
void printVector3D(Vector3D v);

#endif