#include "../include/geometry.h"

/**
 * Constuit un point avec les coordonnées x, y, z en paramètre
 * @return Le point Point3D construit avec les coordonnées x, y, z 
 */
Point3D pointXYZ(float x, float y, float z){
	Point3D p;
	p.x = x;
	p.y = y;
	p.z = z;
	return p;
}

/**
 * Construit un vecteur avec les coordonnée x, y, z en paramètre
 * @return Le vecteur Vector3D construit avec les coordonnées x, y, z
 */
Vector3D vectorXYZ(float x, float y, float z){
	Vector3D v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

/**
 * Construit le vecteur AB entre deux Point3D A et B
 * @return Le vecteur correspondant à AB
 */
Vector3D vector(Point3D A, Point3D B){
	Vector3D v = vectorXYZ((B.x - A.x), (B.y - A.y), (B.z - A.z));
	return v;
}

/**
 * Construit le point P + V
 * @return Le point P + V
 */
Point3D pointPlusVector(Point3D P, Vector3D V){
	Point3D p = pointXYZ(P.x + V.x, P.y + V.y, P.z + V.z);
	return p;
}

/**
 * Fonction d'addition de deux vecteurs
 * @return Le vecteur correspondant à A + B
 */
Vector3D addVectors(Vector3D A, Vector3D B){
	Vector3D v = vectorXYZ(A.x + B.x, A.y + B.y, A.z + B.z);
	return v;
}

/**
 * Fonction de soustraction de deux vecteurs
 * @return Le vecteur correspondant à A - B
 */
Vector3D subVectors(Vector3D A, Vector3D B){
	Vector3D v = vectorXYZ(A.x - B.x, A.y - B.y, A.z - B.z);
	return v;
}

/**
 * Fonction de multiplication d'un vecteur par un scalaire
 * @return Le vecteur correspondant à a*V
 */
Vector3D multVector(Vector3D V, float a){
	Vector3D v = vectorXYZ(a*(V.x), a*(V.y), a*(V.z));
	return v;
}

/**
 * Fonction de division d'un vecteur par un scalaire
 * @return Le vecteur correspondant à a/V
 */
Vector3D divVector(Vector3D V, float a){
	Vector3D v = vectorXYZ((V.x)/a, (V.y)/a, (V.z)/a);
	return v;
}

/**
 * Fonction calculant le produit scalaire de deux vecteur
 * @return Le produit scalaire de A.B
 */
float dot(Vector3D A, Vector3D B){
	return ((A.x)*(B.x))+((A.y)*(B.y))+((A.z)*(B.z));
}

/**
 * Fonction calculant la norme d'un vecteur
 * @return La norme d'un vecteur V
 */
float norm(Vector3D A){
	return sqrtf(powf(A.x,2)+powf(A.y,2)+powf(A.z,2));
}

/**
 * Construit le vecteur normalisé passé en paramètre
 * @return Le vecteur normalisé de A
 */
Vector3D normalize(Vector3D A){
	Vector3D v;
	float normA = norm(A);
	v = vectorXYZ((A.x)/normA, (A.y)/normA, (A.z)/normA);
	return v;
}

/**
 * Fonction d'affichage d'un point
 */
void printPoint3D(Point3D p){
	printf("Le point p passé en paramètre à pour composante :\n");
	printf("x = %f\n",p.x);
	printf("y = %f\n",p.y);
	printf("z = %f\n",p.z);
}

/**
 * Fonction d'affichage d'un vecteur
 */
void printVector3D(Vector3D v){
	printf("Le Vecteur v passé en paramètre à pour composante :\n");
	printf("x = %f\n",v.x);
	printf("y = %f\n",v.y);
	printf("z = %f\n",v.z);
}

