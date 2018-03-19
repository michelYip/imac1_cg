#include "../include/colors.h"

/* ------ Fonction auxiliaire ------ */
/**
 * Renvoie la bonne valeur entre MIN et MAX
 */
float rightValue(float a){
	if (a > MIN && a < MAX) return a;
	else if (a < MIN) return MIN;
	return MAX;
}

/* ------ Fonction colors.h ------ */
/**
 * Construit une couleur avec les composante r, g, b
 * @return la couleur avec les composante r g b
 */
Color3f colorRGB(float r, float g, float b){
	Color3f c;
	c.r = rightValue(r);
	c.g = rightValue(g);
	c.b = rightValue(b);
	return c;
}

/**
 * Fonction qui calcul la somme de deux couleurs
 * @return la somme de deux couleurs c1 et c2
 */
Color3f addColors(Color3f c1, Color3f c2){
	Color3f c = colorRGB(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b);
	return c;
}

/**
 * Fonction qui calcul la soustraction de deux couleurs
 * @return la soustraction de deux couleurs c1 et c2
 */
Color3f subColors(Color3f c1, Color3f c2){
	Color3f c = colorRGB(c1.r-c2.r, c1.g-c2.g, c1.b-c2.b);
	return c;
}

/**
 * Fonction qui calcul la multiplication de deux couleurs
 * @return la multiplication de deux couleurs c1 et c2
 */
Color3f multColors(Color3f c1, Color3f c2){
	Color3f c = colorRGB(c1.r*c2.r, c1.g*c2.g, c1.b*c2.b);
	return c;
}

/**
 * Fonction qui calcul la division de deux couleurs
 * @return la division de deux couleurs c1 et c2
 */
Color3f divColors(Color3f c1, Color3f c2){
	Color3f c = colorRGB(c1.r/c2.r, c1.g/c2.g, c1.b/c2.b);
	return c;
}

/**
 * Fonction qui calcul la multiplication d'une couleur avec un scalaire
 * @return la multiplication d'une couleur par un scalaire
 */
Color3f multColor(Color3f c, float a){
	Color3f color = colorRGB(c.r*a, c.g*a, c.b*a);
	return color;
}

/**
 * Fonction qui calcul la division d'une couleur avec un scalaire
 * @return la division d'une couleur par un scalaire
 */
Color3f divColor(Color3f c, float a){
	Color3f color = colorRGB(c.r/a, c.g/a, c.b/a);
	return color;
}