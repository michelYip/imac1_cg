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
	int full = 0;
	float x = 0, y = 0;

	ShapeList shapes = NULL;
	addShape(allocShape(GL_LINE_STRIP), &shapes);

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
				case SDL_MOUSEMOTION:
					x = -1 + 2. * e.motion.x / WINDOW_WIDTH;
					y = - (-1 + 2. * e.motion.y / WINDOW_HEIGHT);
					break;
				case SDL_MOUSEBUTTONUP:
					if (mode){
						color = e.button.x * NB_COLORS / WINDOW_WIDTH;
					}
					else{
						addPointToList(allocPoint(x, y, COLORS[color * 3], COLORS[color * 3 + 1], COLORS[color * 3 + 2]), &shapes->points);
						if (e.button.button == SDL_BUTTON_RIGHT){
							drawPolygon(&shapes, full);
						}
					}
					break;

				case SDL_KEYDOWN:
					if (e.key.keysym.sym == SDLK_SPACE){
						mode = 1;
					}
					else if (e.key.keysym.sym == SDLK_LSHIFT){
						full = 1;
					}
					break;

				case SDL_KEYUP:
                    if (e.key.keysym.sym == SDLK_SPACE){
                        mode = 0;
                    } else if (e.key.keysym.sym == SDLK_LSHIFT){
						full = 0;
					} else {
                        switch(e.key.keysym.sym){
                            case SDLK_q:
                                printf("Quit...\n");
                                loop = 0;
                                break;
                            case SDLK_s:
                            	drawSquare(x, y, &shapes, color, full);
                            	break;
                            case SDLK_l:
                            	drawLandmark(&shapes);
                            	break;
                            case SDLK_c:
                            	drawCircle(&shapes, color, full);
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

void drawPolygon(ShapeList * shape, int full){
	if (full)
		addShape(allocShape(GL_POLYGON), shape);
	else
		addShape(allocShape(GL_LINE_LOOP), shape);
	(*shape)->points = (*shape)->next->points;
	addShape(allocShape(GL_LINE_STRIP), shape);
}

/* Dessine un carré de coté 1 ayant pour centre les coordonnées de la souris */
void drawSquare(float x, float y, ShapeList * shape, int color, int full){
	if (full)
		addShape(allocShape(GL_QUADS), shape);
	else
		addShape(allocShape(GL_LINE_LOOP), shape);
	addPointToList(allocPoint(x-0.5, y+0.5, COLORS[color * 3], COLORS[color * 3 + 1], COLORS[color * 3 + 2]), &(*shape)->points);
	addPointToList(allocPoint(x+0.5, y+0.5, COLORS[color * 3], COLORS[color * 3 + 1], COLORS[color * 3 + 2]), &(*shape)->points);
	addPointToList(allocPoint(x+0.5, y-0.5, COLORS[color * 3], COLORS[color * 3 + 1], COLORS[color * 3 + 2]), &(*shape)->points);
	addPointToList(allocPoint(x-0.5, y-0.5, COLORS[color * 3], COLORS[color * 3 + 1], COLORS[color * 3 + 2]), &(*shape)->points);
	addShape(allocShape(GL_LINE_STRIP), shape);
}

/* Dessine un repère orthogonal au centre */
void drawLandmark(ShapeList * shape){
	addShape(allocShape(GL_LINES), shape);
	addPointToList(allocPoint(-0.5, 0, COLORS[2 * 3], COLORS[2 * 3 + 1], COLORS[2 * 3 + 2]), &(*shape)->points);
	addPointToList(allocPoint(0.5, 0, COLORS[2 * 3], COLORS[2 * 3 + 1], COLORS[2 * 3 + 2]), &(*shape)->points);
	addPointToList(allocPoint(0, -0.5, COLORS[3 * 3], COLORS[3 * 3 + 1], COLORS[3 * 3 + 2]), &(*shape)->points);
	addPointToList(allocPoint(0, 0.5, COLORS[3 * 3], COLORS[3 * 3 + 1], COLORS[3 * 3 + 2]), &(*shape)->points);
	addShape(allocShape(GL_LINE_STRIP), shape);
}

/* Dessine un cercle d'origine 0,0 et de diamètre 1 */
void drawCircle(ShapeList * shape, int color, int full){
	int i;
	float theta, x, y;
	if (full)
		addShape(allocShape(GL_POLYGON), shape);
	else
		addShape(allocShape(GL_LINE_LOOP), shape);
	for (i = 0; i < NB_VERTEX_CIRCLE; i++){
		theta = 2.0 * 3.1415926f * (float)i/(float)NB_VERTEX_CIRCLE;
		x = 0.5 * cosf(theta);
		y = 0.5 * sinf(theta);
		addPointToList(allocPoint(x, y, COLORS[color * 3], COLORS[color * 3 + 1], COLORS[color * 3 + 2]), &(*shape)->points);
	}
	addShape(allocShape(GL_LINE_STRIP), shape);
}