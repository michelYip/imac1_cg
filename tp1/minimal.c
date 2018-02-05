#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/* Primitive de forme */
static GLenum mode = GL_POINTS;

void resize(){
    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.,-1.,-1.,1.);
}

int main(int argc, char** argv) {

    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE | SDL_GL_DOUBLEBUFFER)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Titre de la fenêtre */
    SDL_WM_SetCaption("Michel Yip - Open GL - TP1", NULL);
    
    glClear(GL_COLOR_BUFFER_BIT);

    /* Boucle d'affichage */
    int loop = 1;
    while(loop) {
        glColor3ub(255,255,255);

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        
        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();
        
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            //float r,g,b = 0, a = 1;   
            int clickNumber = 1, i;        

            /* L'utilisateur ferme la fenêtre : */
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) {

                /* Mouvement souris */
                /*
                case SDL_MOUSEMOTION:
                    drawStart(e.button.x, e.button.y);
                    break;
                */
                /* Clic souris */
                /*
                case SDL_MOUSEBUTTONUP:
                    r = (float)(e.button.x%255)/255;
                    g = (float)(e.button.y%255)/255;
                    printf("clic en (%d, %d)", e.button.x, e.button.y);
                    glClearColor(r,g,b,a);
                    glClear(GL_COLOR_BUFFER_BIT);
                    break;
                */

                 /* Ne marhce pas !!!! */
                case SDL_MOUSEBUTTONDOWN:
                    glBegin(mode);
                    i = 0;
                    while(SDL_PollEvent(&e) && clickNumber != i) {
                        if (e.type == SDL_MOUSEBUTTONDOWN){
                            glVertex2f(-1 + 2. * e.button.x / WINDOW_WIDTH, -(-1 + 2. * e.button.y / WINDOW_HEIGHT));
                            i++;
                        }
                    }
                    glEnd();
                    break;

                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressée (code = %d)\n", e.key.keysym.sym);
                    if (e.key.keysym.sym == 113){
                        printf("button \"q\" pressed : Quit...\n");
                        loop = 0;
                        break;
                    }
                    if (e.key.keysym.sym == 112){
                        printf("Now drawing points (One click required)\n");
                        mode = GL_POINTS;
                        clickNumber = 1;
                        break;
                    }
                    if (e.key.keysym.sym == 108){
                        printf("Now drawing lines (Two click required)\n");
                        mode = GL_LINES;
                        clickNumber = 2;
                        break;
                    }
                    if (e.key.keysym.sym == 116){
                        printf("Now drawing triangles (Three click required)\n");
                        mode = GL_TRIANGLES;
                        clickNumber = 3;
                        break;
                    }
                    break;

                /* Redimensionnement de la fenetre */
                case SDL_VIDEORESIZE:
                    printf("Resizing window...\n");
                    WINDOW_WIDTH = e.resize.w;
                    WINDOW_HEIGHT = e.resize.h;
                    printf("width = %d , height = %d\n",WINDOW_WIDTH,WINDOW_HEIGHT);
                    resize();
                    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE | SDL_GL_DOUBLEBUFFER)) {
                        fprintf(stderr, "Impossible de redimensionner la fenetre. Fin du programme.\n");
                        return EXIT_FAILURE;
                    }

                default:
                    break;
            }
        }

        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}
