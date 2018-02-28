#include "minimal.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10., 10., -5., 5.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

int main(int argc, char** argv) {
    char * strTime;
    if ((strTime = malloc(sizeof(char) * TIME_SIZE)) == NULL){
        fprintf(stderr, "Could not allocate string for time\n");
        return EXIT_FAILURE;
    }
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


    SDL_Surface * textures[SIZE];
    loadTextures(textures);
    /* Création de la texture */ 
    GLuint textureID[SIZE];
    glGenTextures(SIZE, textureID);
    configTextures(textures, textureID);


    int loop = 1;
    glClearColor(0.1, 0.1, 0.1 ,1.0);
    while(loop) {

        Uint32 startTime = SDL_GetTicks();

        /* Récupération de l'heure courante */
        time_t rawtime;
        struct tm * t;
        time(&rawtime);
        t = localtime(&rawtime);
        strftime(strTime, TIME_SIZE, "%T", t);

        glClear(GL_COLOR_BUFFER_BIT);

        /* Affichage de l'heure courante */
        displayTime(strTime, textureID);      

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

    glDeleteTextures(1, textureID); 

    SDL_Quit();

    return EXIT_SUCCESS;
}

/* Chargement de la texture : utilisation similaire à malloc() */
void loadTextures(SDL_Surface * textures[SIZE]){
    if ((textures[0] = IMG_Load("numbers/0.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image : numbers/0.png\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[1] = IMG_Load("numbers/1.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image : numbers/1.png\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[2] = IMG_Load("numbers/2.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image : numbers/2.png\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[3] = IMG_Load("numbers/3.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image : numbers/3.png\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[4] = IMG_Load("numbers/4.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image : numbers/4.png\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[5] = IMG_Load("numbers/5.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image : numbers/5.png\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[6] = IMG_Load("numbers/6.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image : numbers/6.png\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[7] = IMG_Load("numbers/7.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image : numbers/7.png\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[8] = IMG_Load("numbers/8.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image : numbers/8.png\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[9] = IMG_Load("numbers/9.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image : numbers/9.png\n");
        exit(EXIT_FAILURE);
    }
    if ((textures[10] = IMG_Load("numbers/colon.png")) == NULL){
        fprintf(stderr,"An error occured when loading the image : numbers/colong.png\n");
        exit(EXIT_FAILURE);
    }
}

/* Configuration + Traitement des textures et libération mémoire CPU */
void configTextures(SDL_Surface * textures[SIZE], GLuint textureID[SIZE]){
    int i;
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
}

/* Affiche l'heure courante */
void displayTime(char strTime[TIME_SIZE], GLuint textureID[SIZE]){
    int i, iTexture;
    glPushMatrix();
        glTranslatef(-4,0,0);
        /* Activation du texturing */
        glEnable(GL_TEXTURE_2D);
        for (i = 0; i < TIME_SIZE-1; i++){
            if (strTime[i] == ':'){
                iTexture = SIZE-1;
            }
            else {
                iTexture = strTime[i] - 48;
            }
            glBindTexture(GL_TEXTURE_2D, textureID[iTexture]);
            glPushMatrix();
                glBegin(GL_QUADS);
                    glTexCoord2f(0,0);
                    glVertex2f(i,0.25);
                    glTexCoord2f(1,0);
                    glVertex2f(i+1,0.25);
                    glTexCoord2f(1,1);
                    glVertex2f(i+1,-0.25);
                    glTexCoord2f(0,1);
                    glVertex2f(i,-0.25);
                glEnd();
            glPopMatrix();  
        }
        /* Désactivation du texturing */
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}
