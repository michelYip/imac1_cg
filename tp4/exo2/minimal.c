#include "minimal.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

int main(int argc, char** argv) {
    int i;
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

    // TODO: Chargement et traitement de la texture
    /* Chargement de la texture : utilisation similaire à malloc() */
    SDL_Surface * textures[SIZE];
    loadTextures(textures);
    /* Création de la texture */
    GLuint textureID[SIZE];
    glGenTextures(SIZE, textureID);

    for (i = 0; i < SIZE ; i++){
        /* Configuration des paramètres de textures */
        glBindTexture(GL_TEXTURE_2D, textureID[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        /* Envoie des données vers la carte graphique */
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            textures[i]->w,
            textures[i]->h,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            textures[i]->pixels);
        glBindTexture(GL_TEXTURE_2D, 0);

        SDL_FreeSurface(textures[i]);
    }
    int loop = 1;
    glClearColor(0.1, 0.1, 0.1 ,1.0);

    while(loop) {

        Uint32 startTime = SDL_GetTicks();

        // TODO: Code de dessin
        time_t rawtime;
        struct tm * t;
        time(&rawtime);
        t = localtime(&rawtime);
        int hour = t->tm_hour, minute = t->tm_min, second = t->tm_sec;

        glClear(GL_COLOR_BUFFER_BIT);

        /* Activation du texturing */
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID[1]);

        /* Dessin d'un carré avec texture */
        /*
        glPushMatrix();
            glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(-0.5,0.5);
                glTexCoord2f(1,0);
                glVertex2f(0.5,0.5);
                glTexCoord2f(1,1);
                glVertex2f(0.5,-0.5);
                glTexCoord2f(0,1);
                glVertex2f(-0.5,-0.5);
            glEnd();
        glPopMatrix();
        */

        /* Désactivation du texturing */
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Fin du code de dessin

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

    // TODO: Libération des données GPU
    glDeleteTextures(1, textureID);
    // ...

    // Liberation des ressources associées à la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}

void loadTextures(SDL_Surface * textures[SIZE]){
    if ((textures[0] = IMG_Load("numbers/0.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[1] = IMG_Load("numbers/1.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[2] = IMG_Load("numbers/2.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[3] = IMG_Load("numbers/3.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[4] = IMG_Load("numbers/4.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[5] = IMG_Load("numbers/5.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[6] = IMG_Load("numbers/6.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[7] = IMG_Load("numbers/7.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[8] = IMG_Load("numbers/8.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[9] = IMG_Load("numbers/9.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[10] = IMG_Load("numbers/colon.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image\n");
        exit(EXIT_FAILURE);
    }
}
