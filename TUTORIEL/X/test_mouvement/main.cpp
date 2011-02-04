/*******************************************************/
/** Programme de PERRUCHON Romain pour developpez.com **/
/**               Chapitre X : Mouvement              **/
/*******************************************************/

//Les fichiers d'ent�te
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

//Les attributs de l'�cran (640 * 480)
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//Le nombre de frame par seconde
const int FRAMES_PER_SECOND = 20;

//Les dimensions du point (l'image qu'on va deplacer)
const int POINT_WIDTH = 20;
const int POINT_HEIGHT = 20;

//Les surfaces
SDL_Surface *point = NULL;
SDL_Surface *screen = NULL;

//La structure d'�v�nements que nous allons utiliser
SDL_Event event;

//Le point que nous allons bouger sur l'ecran
class Point
{
    private:
    //Les coordonn�es x et y du point
    int x, y;

    //La vitesse du point
    int xVel, yVel;

    public:
    //Initialisation des variables
    Point();

    //Recupere la touche pressee et ajuste la vitesse du point
    void handle_input();

    //Montre le point sur l'ecran
    void show();
};

//Le timer
class Timer
{
    private:
    //Le temps quand le timer est lanc�
    int startTicks;

    //Les "ticks" enregistr� quand le Timer a �t� mit en pause
    int pausedTicks;

    //Le status du Timer
    bool paused;
    bool started;

    public:
    //Initialise les variables (le constructeur)
    Timer();

    //Les diff�rentes actions du timer
    void start();
    void stop();
    void pause();
    void unpause();

    //recup�re le nombre de ticks depuis que le timer a �t� lanc�
    //ou r�cup�re le nombre de ticks depuis que le timer a �t� mis en pause
    int get_ticks();

    //Fonctions de v�rification du status du timer
    bool is_started();
    bool is_paused();
};


SDL_Surface *load_image( std::string filename )
{
    //L'image qui est charg�e
    SDL_Surface* loadedImage = NULL;

    //L'image optimis�e qu'on va utiliser
    SDL_Surface* optimizedImage = NULL;

    //Chargement de l'image
    loadedImage = IMG_Load( filename.c_str() );

    //Si l'image a bien charg�e
    if( loadedImage != NULL )
    {
        //Cr�ation de l'image optimis�e
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Lib�ration de l'ancienne image
        SDL_FreeSurface( loadedImage );

        //Si la surface a bien �t� optimis�e
        if( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //On retourne l'image optimis�e
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //On blitte la surface
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialisation de tous les sous-syst�me de SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Mise en place de l'�cran
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //S'il y a eu une erreur lors de la mise en place de l'�cran
    if( screen == NULL )
    {
        return false;
    }

    //Mise en place de la barre caption
    SDL_WM_SetCaption( "Bouge le point", NULL );

    //Si tout s'est bien pass�
    return true;
}

bool load_files()
{
    //Chargement du point
    point = load_image( "dot.bmp" );

    //S'il y a eu un probl�me au chargement du point
    if( point == NULL )
    {
        return false;
    }

    //Si tout s'est bien pass�
    return true;
}

void clean_up()
{
    //Lib�ration des surfaces
    SDL_FreeSurface( point );

    //On quitte SDL
    SDL_Quit();
}

Point::Point()
{
    //Initialisation des coordonnees
    x = 0;
    y = 0;

    //Initialisation de la vitesse
    xVel = 0;
    yVel = 0;
}

void Point::handle_input()
{
    //Si une touche a ete pressee
    if( event.type == SDL_KEYDOWN )
    {
        //ajustement de la vitesse
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel -= POINT_HEIGHT / 2; break;
            case SDLK_DOWN: yVel += POINT_HEIGHT / 2; break;
            case SDLK_LEFT: xVel -= POINT_WIDTH / 2; break;
            case SDLK_RIGHT: xVel += POINT_WIDTH / 2; break;
            default: break;
        }
    }
    //Si une touche a ete relachee
    else if( event.type == SDL_KEYUP )
    {
        //ajustement de la vitesse
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel += POINT_HEIGHT / 2; break;
            case SDLK_DOWN: yVel -= POINT_HEIGHT / 2; break;
            case SDLK_LEFT: xVel += POINT_WIDTH / 2; break;
            case SDLK_RIGHT: xVel -= POINT_WIDTH / 2; break;
            default: break;
        }
    }
}

void Point::show()
{
    //Bouge le point � gauche ou � droite
    x += xVel;

    //Si le point se rapproche trop des limites(gauche ou droite) de l'ecran
    if( ( x < 0 ) || ( x + POINT_WIDTH > SCREEN_WIDTH ) )
    {
        //On revient
        x -= xVel;
    }

    //Bouge le point en haut ou en bas
    y += yVel;

    //Si le point se rapproche trop des limites(haute ou basse) de l'ecran
    if( ( y < 0 ) || ( y + POINT_HEIGHT > SCREEN_HEIGHT ) )
    {
        //On revient
        y -= yVel;
    }

    //Affiche le point
    apply_surface( x, y, point, screen );
}

Timer::Timer()
{
    //Initialisation des variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //On demarre le timer
    started = true;

    //On enl�ve la pause du timer
    paused = false;

    //On r�cup�re le temps courant
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //On stoppe le timer
    started = false;

    //On enl�ve la pause
    paused = false;
}

void Timer::pause()
{
    //Si le timer est en marche et pas encore en pause
    if( ( started == true ) && ( paused == false ) )
    {
        //On met en pause le timer
        paused = true;

        //On calcul le pausedTicks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //Si le timer est en pause
    if( paused == true )
    {
        //on enl�ve la pause du timer
        paused = false;

        //On remet � zero le startTicks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Remise � zero du pausedTicks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //Si le timer est en marche
    if( started == true )
    {
        //Si le timer est en pause
        if( paused == true )
        {
            //On retourne le nombre de ticks quand le timer a �t� mis en pause
            return pausedTicks;
        }
        else
        {
            //On retourne le temps courant moins le temps quand il a d�marr�
            return SDL_GetTicks() - startTicks;
        }
    }

    //Si le timer n'est pas en marche
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

int main( int argc, char* args[] )
{
    //Ce qui va nous permettre de quitter
    bool quit = false;

    //Le point qu'on va utilise
    Point monPoint;

    //Le regulateur
    Timer fps;

    //Initialisation
    if( init() == false )
    {
        return 1;
    }

    //Chargement des fichiers
    if( load_files() == false )
    {
        return 1;
    }

    //Tant que l'utilisateur n'a pas quitter
    while( quit == false )
    {
        //On demarre le timer fps
        fps.start();

        //Tant qu'il y a un �v�nement
        while( SDL_PollEvent( &event ) )
        {
            //On recupere l'evenement pour le point
            monPoint.handle_input();

            //Si l'utilisateur a cliqu� sur le X de la fen�tre
            if( event.type == SDL_QUIT )
            {
                //On quitte the programme
                quit = true;
            }
        }

        //On remplit l'ecran de blanc
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

        //On affiche le point sur l'ecran
        monPoint.show();

        //Mise � jour de l'�cran
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        //Tant que le timer fps n'est pas assez haut
        while( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //On attend...
        }
    }

    //Nettoyage
    clean_up();

    return 0;
}
