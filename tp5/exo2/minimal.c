#include "minimal.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100., 100., -100., 100.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

int main(int argc, char** argv) {
    // Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    // Ouverture d'une fenêtre et création d'un contexte OpenGL
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("td04", NULL);
    resizeViewport();

    //TODO :
    //Créer liste planete
    //Incrémenter Angle
    //Dessiner planetes

    int loop = 1;
    glClearColor(0.1, 0.1, 0.1 ,1.0);
    while(loop) {

        Uint32 startTime = SDL_GetTicks();

        /* Récupération de l'heure courante */
        time_t rawtime;
        struct tm * t;
        time(&rawtime);
        t = localtime(&rawtime);

        glClear(GL_COLOR_BUFFER_BIT);

        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            switch(e.type) {

                case SDL_KEYUP:
                    switch(e.key.keysym.sym){
                        case SDLK_q:
                            loop = 0;
                            break;
                        default:
                            break;
                    }
                    break;                    
                case SDL_QUIT:
                    loop = 0;
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

    SDL_Quit();

    return EXIT_SUCCESS;
}

/* Dessine un cercle d'origine 0,0 et de diamètre 1 */
void drawCircle(int full){
    int i;
    float theta, x, y;
    if (full)
        glBegin(GL_POLYGON);
    else
        glBegin(GL_LINE_LOOP);
    for (i = 0; i < NB_VERTEX_CIRCLE; i++){
        theta = 2.0 * 3.1415926f * (float)i/(float)NB_VERTEX_CIRCLE;
        x = 0.5 * cosf(theta);
        y = 0.5 * sinf(theta);
        glVertex2f(x,y);
    }
    glEnd();
}

void initPlanet(PlanetList * list, float radius, float distanceToCenter, float rotationSpeed, float, r, float g, float b){
    Planet tmp;
    if ((tmp = malloc(sizeof(Planet))) == NULL){
        fprintf(stderr, "could not allocate a Planet, abort program...\n");
        exit(EXIT_FAILURE);
    }
    tmp->radius = radius;
    tmp->distanceToCenter = distanceToCenter;
    tmp->angle = 0;
    tmp->rotationSpeed = rotationSpeed;
    tmp->r = r;
    tmp->g = g;
    tmp->b = b;
    tmp->next = (*list);
    (*list) = tmp;
}

/* Dessine la liste des planètes */
void drawPlanets(PlanetList list){
    while (list){
        glPushMatrix();
            glRotatef(list->angle,0,0,1);
            glTranslatef(list->distanceToCenter, 0, 0);
            glColor3f(list->r, list->g, list->b);
            drawCircle(1);
        glPopMatrix();
        list = list->next;
    }
}