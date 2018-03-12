#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>

typedef struct shape{
	float r, g, b, a;
	float x, y;
	struct shape * next;
}Shape, * ShapeList;

void initShape(ShapeList * shape, float r, float g, float b, float a, float x, float y);
void addShape(ShapeList * shape, float r, float g, float b, float a, float x, float y);
void deleteShape(ShapeList * list);
void addShapeToTail(ShapeList * list);
void drawShape(ShapeList list);

// Dimensions de la fenêtre
static unsigned int WINDOW_WIDTH = 600;
static unsigned int WINDOW_HEIGHT = 600;

// Nombre de bits par pixel de la fenêtre
static const unsigned int BIT_PER_PIXEL = 32;

// Nombre minimal de millisecondes separant le rendu de deux images
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1, 1);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}


void drawSquare(int full) {
    if (full == 0) {
        glBegin(GL_LINE_LOOP);
    }
    else {
        glBegin(GL_TRIANGLE_FAN);
    }
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(-0.5f, -0.5f);
    glEnd();
} 


int main(int argc, char** argv) {

    // Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    // Ouverture d'une fenêtre et création d'un contexte OpenGL
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    SDL_WM_SetCaption("td06", NULL);

    resizeViewport();

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    /* Activation de l'option blanding OpenGL */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ShapeList shapes;
    initShape(&shapes, 1,0,0,.5,0,0);
    addShape(&shapes,0,1,0,.6,0.1,0.1);

    int loop = 1;
    while(loop) {

        Uint32 startTime = SDL_GetTicks();

        // Code de dessin
        glClear(GL_COLOR_BUFFER_BIT);
        drawShape(shapes);
        
        // Event loop

        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }

            switch(e.type) {

                case SDL_MOUSEBUTTONUP:
                    break;

                case SDL_KEYDOWN:

                    switch(e.key.keysym.sym) {

                        case SDLK_q:
                            loop = 0;

                        default:
                            break;
                    }

                    break;

                case SDL_KEYUP:
                	switch(e.key.keysym.sym) {

                        case SDLK_UP:
                            shapes->y += 0.1;
                            break;
                        case SDLK_DOWN:
                        	shapes->y -= 0.1;
                        	break;
                        case SDLK_RIGHT:
                        	shapes->x += 0.1;
                        	break;
                        case SDLK_LEFT:
                        	shapes->x -= 0.1;
                        	break;
                        case SDLK_KP_PLUS:
                        	shapes->a += 0.1;
                        	break;
                        case SDLK_KP_MINUS:
                        	shapes->a -= 0.1;
                        	break;
                        case SDLK_SPACE:
                        	addShapeToTail(&shapes);
                        	break;

                        default:
                            break;
                    }

                    break;

                case SDL_VIDEORESIZE:
                    WINDOW_WIDTH = e.resize.w;
                    WINDOW_HEIGHT = e.resize.h;
                    resizeViewport();

                default:
                    break;
            }
        }

        SDL_GL_SwapBuffers();
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    // Liberation des ressources associées à la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}

void initShape(ShapeList * shape, float r, float g, float b, float a, float x, float y){
	ShapeList tmp;
	if ((tmp = malloc(sizeof(Shape))) == NULL){
		fprintf(stderr, "could not allocate new shape, abort program...\n");
		exit(EXIT_FAILURE);
	}
	tmp->r = r;
	tmp->g = g;
	tmp->b = b;
	tmp->a = a;
	tmp->x = x;
	tmp->y = y;
	tmp->next = (*shape);
	*shape = tmp;
}

void addShape(ShapeList * shape, float r, float g, float b, float a, float x, float y){
	ShapeList tmp;
	if ((tmp = malloc(sizeof(Shape))) == NULL){
		fprintf(stderr, "could not allocate new shape, abort program...\n");
		exit(EXIT_FAILURE);
	}
	tmp->r = r;
	tmp->g = g;
	tmp->b = b;
	tmp->a = a;
	tmp->x = x;
	tmp->y = y;
	tmp->next = NULL;
	(*shape)->next = tmp;
}

void deleteShape(ShapeList * list){
	ShapeList tmp = (*list);
	*list = (*list)->next;
	free(tmp);
}

void addShapeToTail(ShapeList * list){
	ShapeList tmp = (*list);
	while(tmp->next)
		tmp = tmp->next;
	addShape(&tmp, (*list)->r, (*list)->g, (*list)->b, (*list)->a, (*list)->x, (*list)->y);
	deleteShape(list);
}

void drawShape(ShapeList list){
	while (list){
		glPushMatrix();
			glColor4f(list->r, list->g, list->b, list->a);
			glTranslatef(list->x, list->y,0);
			drawSquare(1);
		glPopMatrix();
		list = list->next;
	}
}