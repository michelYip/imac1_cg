#include "minimal.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10., 10., -10., 10.);
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
    SDL_WM_SetCaption("td05 - exo1", NULL);
    resizeViewport();

    GLuint id = glGenLists(1);
    createClockIDList(id);

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

        glCallList(id);

        /* Affichage de l'heure courante */
        displayTime(t->tm_hour, t->tm_min, t->tm_sec);

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

/* Créer l'identifiant pour le cadran de l'horloge */
void createClockIDList(GLuint id){
    int grad;
    float marge = 360/NB_GRAD;
    glNewList(id, GL_COMPILE);
        glPushMatrix();
            glScalef(20,20,0);
            glColor3ub(0,0,0);
            drawCircle(1);
            glPushMatrix();
                glScalef(0.97,0.97,0);
                glColor3ub(255,255,255);
                drawCircle(1);
            glPopMatrix();
            glPushMatrix();
                glScalef(0.95,0.95,0);
                glColor3ub(0,0,0);
                drawCircle(0);
            glPopMatrix();
        glPopMatrix();
        for (grad = 0; grad < NB_GRAD; grad++){
            glPushMatrix();
                glRotatef(grad*marge,0,0,1);
                glTranslatef(8,0,0);
                if (grad % 5 == 0)
                    glScalef(0.8,0.175,0);
                else
                    glScalef(0.5,0.125,0);
                drawSquare();
            glPopMatrix();
        }
        glPushMatrix();
            glScalef(0.4,0.4,0);
            drawCircle(1);
        glPopMatrix();
    glEndList();
}

/* Affiche l'heure courante */
void displayTime(int hour, int minute, int second){
    float grad = 360./NB_GRAD;
    glPushMatrix();
        glRotatef(90,0,0,1);
        glPushMatrix();
            glRotatef(-1.*(grad)*second,0,0,1);
            glTranslatef(4.5,0,0);
            glScalef(9,0.1,0);
            drawSquare();
        glPopMatrix();
        glPushMatrix();
            glRotatef(-1.*(grad*minute+((grad/60)*second)),0,0,1);
            glTranslatef(3.5,0,0);
            glScalef(7,0.2,0);
            drawSquare();
        glPopMatrix();
        glPushMatrix();
            glRotatef(-1.*((grad*5)*hour+(grad*5/60)*minute),0,0,1);
            glTranslatef(2.5,0,0);
            glScalef(5,0.3,0);
            drawSquare();
        glPopMatrix();
    glPopMatrix();
}