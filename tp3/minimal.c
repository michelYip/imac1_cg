#include "shapes.h"

/* Dimension de la fenetre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecond separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000/60;

void resize(){
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-150, 150, -150, 150);
}

void resize_window(){
	if (SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE | SDL_GL_DOUBLEBUFFER) == NULL){
		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		exit(EXIT_FAILURE);
	}
	resize();
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapBuffers();
}

void transform(){
	glMatrixMode(GL_MODELVIEW);
}

int main (int argc, char ** argv){
	/* Vérification de l'initialisation de SDL, si echec : sort du programme */
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		return EXIT_FAILURE;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
	resize_window();
	SDL_WM_SetCaption("Michel YIP - OpenGL_TP03", NULL);
	transform();

	int loop = 1;
	
	int alpha = 45, beta = -10, rotationSpeed = 1;
	int gammaA = 120, gammaB = 240, gammaC = 0;
	
	GLuint id = glGenLists(3);
	createFirstArmIDList(id);
	createSecondArmIDList(id+1);
	createThirdArmIDList(id+2);

    glColor3ub(255,255,255);
	
	while(loop){
		Uint32 startTime = SDL_GetTicks();
		alpha = (alpha + rotationSpeed)%360;
		beta = (beta + rotationSpeed*2)%360;
		gammaA = (gammaA + rotationSpeed)%360;
		gammaB = (gammaB + rotationSpeed*2)%360;
		gammaC = (gammaC + rotationSpeed*3)%360;

		/* Echange les deux buffers */
		SDL_GL_SwapBuffers();
		/* On nettoie la fenetre */
		glClear(GL_COLOR_BUFFER_BIT);

		drawFullArm((float)alpha, (float)beta, (float)gammaA);
		drawFullArm((float)alpha, (float)beta, (float)gammaB);
		drawFullArm((float)alpha, (float)beta, (float)gammaC);

		/* Gestion des évènements SDL */
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT){
                loop = 0;
                break;
            }
			switch(e.type){
				case SDL_KEYUP:
                    switch(e.key.keysym.sym){
                        case SDLK_q:
                            printf("Quit...\n");
                            loop = 0;
                            break;
                        default:
                            break;
                        }
					break;
				case SDL_VIDEORESIZE:
					WINDOW_WIDTH = e.resize.w;
					WINDOW_HEIGHT= e.resize.h;
					resize_window();
				default:
					break;
			}
		}
		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		if (elapsedTime < FRAMERATE_MILLISECONDS){
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}
	}

	SDL_Quit();
	return EXIT_SUCCESS;
}

/* Dessine un carré de coté 1 ayant pour centre les coordonnées de la souris */
void drawSquare(){
	glBegin(GL_QUADS);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5,0.5);
		glVertex2f(0.5,-0.5);
		glVertex2f(-.5,-0.5);
	glEnd();
}

/* Dessine un cercle d'origine 0,0 et de diamètre 1 */
void drawCircle(){
	int i;
	float theta, x, y;
	glBegin(GL_POLYGON);
	for (i = 0; i < NB_VERTEX_CIRCLE; i++){
		theta = 2.0 * 3.1415926f * (float)i/(float)NB_VERTEX_CIRCLE;
		x = 0.5 * cosf(theta);
		y = 0.5 * sinf(theta);
		glVertex2f(x,y);
	}
	glEnd();
}

/* Dessine un carré à bords arrondis canonique (1 unité de coté) */
void drawRoundedSquare(){
	glPushMatrix();
		glScalef(1,0.5,0);
		drawSquare();
	glPopMatrix();
	glPushMatrix();
		glScalef(0.5,1,0);
		drawSquare();
	glPopMatrix();
	glPushMatrix();
		glScalef(0.5,0.5,0);
		glTranslatef(-0.5,-0.5,0);
		glPushMatrix();
			drawCircle();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.,0.,0.);
			drawCircle();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.,1.,0.);
			drawCircle();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.,1.,0.);
			drawCircle();
		glPopMatrix();
	glPopMatrix();
}

/* Dessine un repère orthogonal au centre */
void drawLandmark(){
	glBegin(GL_LINES);
		glVertex2f(-0.5, 0);
		glVertex2f(0.5,0);
		glVertex2f(0,-0.5);
		glVertex2f(0,0.5);
	glEnd();
}

/* Créer l'indice de la liste permettant de dessiner le bras principal */
void createFirstArmIDList(GLuint id){
	glNewList(id, GL_COMPILE);
		glPushMatrix();
			glScalef(40,40,0);
			drawCircle();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(60,0,0);
			glScalef(20,20,0);
			drawCircle();
		glPopMatrix();
		glBegin(GL_LINE_LOOP);
			glVertex2f(0,20);
			glVertex2f(60,10);
			glVertex2f(60,-10);
			glVertex2f(0,-20);
		glEnd();
	glEndList();
}

/* Créer l'indice de la liste permettant de dessiner le bras manipulateur */
void createSecondArmIDList(GLuint id){
	glNewList(id, GL_COMPILE);
		glPushMatrix();
			glScalef(10,10,0);
			drawRoundedSquare();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(40,0,0);
			glScalef(10,10,0);
			drawRoundedSquare();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(20,0,0);
			glScalef(46,6,0);
			drawSquare();
		glPopMatrix();
	glEndList();
}

/* Créer l'indice de la liste permettant de dessiner le batteur */
void createThirdArmIDList(GLuint id){
	glNewList(id, GL_COMPILE);
		glPushMatrix();
			glScalef(6,6,0);
			drawRoundedSquare();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(20,0,0);
			glScalef(40,4,0);
			drawSquare();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(40,0,0);
			glScalef(8,8,0);
			drawCircle();
		glPopMatrix();
	glEndList();
}

/* Dessine le bras mécanique en entier */
void drawFullArm(float alpha, float beta, float gamma){
	glPushMatrix();
		glRotatef(alpha,0,0,1);
		glCallList(1);
		glPushMatrix();
			glTranslatef(60,0,0);
			glRotatef(beta,0,0,1);
			glCallList(2);
			glPushMatrix();
				glTranslatef(40,0,0);
				glRotatef(gamma,0,0,1);
				glCallList(3);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}