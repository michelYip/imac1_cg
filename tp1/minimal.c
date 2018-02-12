#include "shapes.h"

/* Dimension de la fenetre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecond separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000/60;

static const unsigned char COLORS[] = {
     0, 0, 0 ,
     255, 255, 255, 
     255, 0, 0 ,
     0, 255, 0 ,
     0, 0, 255 ,
     255, 255, 0 ,
     255, 0, 255 ,
     0, 255, 255 
};
static const unsigned int NB_COLORS = sizeof(COLORS) / (3 * sizeof(unsigned char));


void resize(){
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1., 1., -1., 1.);
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

void displayColors(){
    int i;
    GLfloat dx = 2.f / NB_COLORS;
    glBegin(GL_QUADS);
    for(i = 0; i < NB_COLORS; ++i) {
        glColor3ubv(COLORS + i * 3);  
        glVertex2f(-1 + i * dx, -1);
        glVertex2f(-1 + (i + 1) * dx, -1);
        glVertex2f(-1 + (i + 1) * dx, 1);
        glVertex2f(-1 + i * dx, 1);
    }
    glEnd();    
}

int main (int argc, char ** argv){
	/* Vérification de l'initialisation de SDL, si echec : sort du programme */
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		return EXIT_FAILURE;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

	resize_window();
	SDL_WM_SetCaption("Michel YIP - OpenGL_TP01", NULL);

	int color = 1;
	int mode = 0;

	ShapeList shapes = NULL;
	addShape(allocShape(GL_POINTS), &shapes);

	int loop = 1;
	while(loop){
		Uint32 startTime = SDL_GetTicks();

		/* On nettoie la fenetre */
		glClear(GL_COLOR_BUFFER_BIT);

		if (mode)
			displayColors();
		else
			drawShape(shapes);

		/* Echange les deux buffers */
		SDL_GL_SwapBuffers();

		/* Gestion des évènements SDL */
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT){
                loop = 0;
                break;
            }
			switch(e.type){
				case SDL_MOUSEBUTTONUP:
					if (mode){
						color = e.button.x * NB_COLORS / WINDOW_WIDTH;
					}
					else{
						addPointToList(allocPoint(-1 + 2. * e.button.x / WINDOW_WIDTH, - (-1 + 2. * e.button.y / WINDOW_HEIGHT), COLORS[color * 3], COLORS[color * 3 + 1], COLORS[color * 3 + 2]), &shapes->points);
					}
					break;

				case SDL_KEYDOWN:
					if (e.key.keysym.sym == SDLK_SPACE){
						mode = 1;
					}
					break;

				case SDL_KEYUP:
                    if (e.key.keysym.sym == SDLK_SPACE){
                        mode = 1;
                    } else {
                        switch(e.key.keysym.sym){
                            case SDLK_q:
                                printf("Quit...\n");
                                loop = 0;
                                break;
                            case SDLK_p:
                                addShape(allocShape(GL_POINTS), &shapes);
                                break;
                            case SDLK_l:
                                addShape(allocShape(GL_LINES), &shapes);
                                break;
                            case SDLK_t:
                                addShape(allocShape(GL_TRIANGLES), &shapes);
                                break;
                            default:
                                break;
                        }
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

		/*
		glBegin(GL_POINTS);
			glVertex2f(-1 + 2. * x / WINDOW_WIDTH, -(-1 + 2. * y / WINDOW_HEIGHT));
		glEnd();
		*/

		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		if (elapsedTime < FRAMERATE_MILLISECONDS){
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}
	}

	SDL_Quit();

	return EXIT_SUCCESS;
}

/* Alloue l'espace mémoire pour stocké un point */
Point * allocPoint(float x, float y, unsigned char r, unsigned char g, unsigned char b){
	Point * point;
	if ((point = malloc(sizeof(Point))) == NULL){
		fprintf(stderr,"Could not allocate memory for Point : abort...\n");
		exit(EXIT_FAILURE);
	}
	point -> x = x;
	point -> y = y;
	point -> r = r;
	point -> g = g;
	point -> b = b;
	point -> next = NULL;
	return point;
}
 
/* Ajoute le point en fin de liste */
void addPointToList(Point * point, PointList * list){
	if (*list == NULL)
		*list = point;
	else
		addPointToList(point, &(*list)->next);
}

/* Dessine tout les points de la listes */
void drawPoints(PointList list){
	while(list){
		glColor3ub(list->r,list->g,list->b);
		glVertex2f(list->x, list->y);
		list = list->next;
	}
}

/* Supprime tout les points d'une liste et libère l'espace mémoire */
void deletePoints(PointList * list){
	while(*list){
		PointList next = (*list)->next;
		free(*list);
		*list = next;
	}
}

/* Alloue l'espace mémoire pour stocké une primitive */
Shape * allocShape(GLenum type){
	Shape * shape;
	if ((shape = malloc(sizeof(Shape))) == NULL){
		fprintf(stderr, "Could not allocate memory for Shape : abort...\n");
		exit(EXIT_FAILURE);
	}
	shape -> type = type;
	shape -> points = NULL;
	shape -> next = NULL;
	return shape;
}

/* Ajoute une primitive à la liste de primitive */
void addShape(Shape * shape, ShapeList * list){
	shape->next = *list;
	*list = shape;
}

/* Dessine la primitive en paramètre */
void drawShape(ShapeList list){
	while(list){
		glBegin(list->type);
			drawPoints(list->points);
		glEnd();
		list = list->next;
	}
}

/* Supprime toutes les primitives et libère l'espace mémoire */
void deleteShape(ShapeList * list){
	while(*list){
		Shape * next = (*list)->next;
		deletePoints(&((*list)->points));
		free(*list);
		*list = next;
	}
}
