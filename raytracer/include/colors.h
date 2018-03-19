#ifndef __COLORS_H__
#define __COLORS_H__

#define MIN 0.0
#define MAX 1.0

typedef struct Color3f{
	float r, g, b;
} Color3f;

/**
 * Construit une couleur avec les composante r, g, b
 * @return la couleur avec les composante r g b
 */
Color3f colorRGB(float r, float g, float b);

/**
 * Fonction qui calcul la somme de deux couleurs
 * @return la somme de deux couleurs c1 et c2
 */
Color3f addColors(Color3f c1, Color3f c2);

/**
 * Fonction qui calcul la soustraction de deux couleurs
 * @return la soustraction de deux couleurs c1 et c2
 */
Color3f subColors(Color3f c1, Color3f c2);

/**
 * Fonction qui calcul la multiplication de deux couleurs
 * @return la multiplication de deux couleurs c1 et c2
 */
Color3f multColors(Color3f c1, Color3f c2);

/**
 * Fonction qui calcul la division de deux couleurs
 * @return la division de deux couleurs c1 et c2
 */
Color3f divColors(Color3f c1, Color3f c2);

/**
 * Fonction qui calcul la multiplication d'une couleur avec un scalaire
 * @return la multiplication d'une couleur par un scalaire
 */
Color3f multColor(Color3f c, float a);

/**
 * Fonction qui calcul la division d'une couleur avec un scalaire
 * @return la division d'une couleur par un scalaire
 */
Color3f divColor(Color3f c, float a);

#endif