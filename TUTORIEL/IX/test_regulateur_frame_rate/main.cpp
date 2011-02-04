/*******************************************************/
/** Programme de PERRUCHON Romain pour developpez.com **/
/**      Chapitre IX-B : Regulateur de Frame Rate     **/
/*******************************************************/

//Les fichiers d'entête
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>

//Les attributs de l'écran (640 * 480)
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//Le nombre de frame par seconde
const int FRAMES_PER_SECOND = 20;

//Les surfaces
SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;

//La structure d'événements que nous allons utiliser
SDL_Event event;

//La police de caractère que nous allons utiliser
TTF_Font *font;

//La couleur de cette police de caractère
SDL_Color textColor = { 0, 0, 0 };

//Le timer
class Timer
{
    private:
    //Le temps quand le timer est lancé
    int startTicks;

    //Les "ticks" enregistré quand le Timer a été mit en pause
    int pausedTicks;

    //Le status du Timer
    bool paused;
    bool started;

    public:
    //Initialise les variables (le constructeur)
    Timer();

    //Les différentes actions du timer
    void start();
    void stop();
    void pause();
    void unpause();

    //recupére le nombre de ticks depuis que le timer a été lancé
    //ou récupére le nombre de ticks depuis que le timer a été mis en pause
    int get_ticks();

    //Fonctions de vérification du status du timer
    bool is_started();
    bool is_paused();
};

SDL_Surface *load_image( std::string filename )
{
    //L'image qui est chargée
    SDL_Surface* loadedImage = NULL;

    //L'image optimisée qu'on va utiliser
    SDL_Surface* optimizedImage = NULL;

    //Chargement de l'image
    loadedImage = IMG_Load( filename.c_str() );

    //Si l'image a bien chargée
    if( loadedImage != NULL )
    {
        //Création de l'image optimisée
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Libération de l'ancienne image
        SDL_FreeSurface( loadedImage );

        //Si la surface a bien été optimisée
        if( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //On retourne l'image optimisée
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
    //Initialisation de tous les sous-système de SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Mise en place de l'écran
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //S'il y a eu une erreur lors de la mise en place de l'écran
    if( screen == NULL )
    {
        return false;
    }

    //Initialisation de SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Mise en place de la barre caption
    SDL_WM_SetCaption( "Frame Rate Test", NULL );

    //Si tout s'est bien passé
    return true;
}

bool load_files()
{
    //Chargement du fond
    background = load_image( "background.png" );

    //Ouverture de la police de caratère (font)
    font = TTF_OpenFont( "lazy.ttf", 20 );

    //S'il y a eu un problème au chargement du fond
    if( background == NULL )
    {
        return false;
    }

    //S'il y a eu un problème au chargement du font (police de caractère)
    if( font == NULL )
    {
        return false;
    }

    //Si tout s'est bien passé
    return true;
}

void clean_up()
{
    //Libèration des surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( message );

    //Fermeture du Font
    TTF_CloseFont( font );

    //On quitte SDL_ttf
    TTF_Quit();

    //On quitte SDL
    SDL_Quit();
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

    //On enlève la pause du timer
    paused = false;

    //On récupére le temps courant
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //On stoppe le timer
    started = false;

    //On enlève la pause
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
        //on enlève la pause du timer
        paused = false;

        //On remet à zero le startTicks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Remise à zero du pausedTicks
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
            //On retourne le nombre de ticks quand le timer a été mis en pause
            return pausedTicks;
        }
        else
        {
            //On retourne le temps courant moins le temps quand il a démarré
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

    int frame = 0;

    //Ce qui va nous servir à activer/desactiver le regulateur
    bool cap = true;

    //Le regulateur
    Timer fps;

    //Initialisation de SDL
    if( init() == false )
    {
        return 1;
    }

    //Chargement des fichiers
    if( load_files() == false )
    {
        return 1;
    }


    //Generation de la surface message
    message = TTF_RenderText_Solid( font, "Appuyer sur Entrée sur mettre sur le regulateur sur OFF", textColor );

    //Tant que l'utilisateur n'a pas quitter
    while( quit == false )
    {
        //On demarre le timer fps
        fps.start();

        //Tant qu'il y a un événement
        while( SDL_PollEvent( &event ) )
        {
            //Si une touche est pressée
            if( event.type == SDL_KEYDOWN )
            {
                //Si la touche Entrée est pressée
                if( event.key.keysym.sym == SDLK_RETURN )
                {
                    //On tourne le regulateur sur on/off
                    cap = ( !cap );
                    if (cap == true) {
                        //Generation de la surface message
                        message = TTF_RenderText_Solid( font, "Appuyer sur Entrée sur mettre sur le regulateur sur OFF", textColor );
                    }
                    else {
                        //Generation de la surface message
                        message = TTF_RenderText_Solid( font, "Appuyer sur Entrée sur mettre sur le regulateur sur ON", textColor );
                    }
                }
            }

            //Si l'utilisateur a cliqué sur le X de la fenêtre
            else if( event.type == SDL_QUIT )
            {
                //On quitte the programme
                quit = true;
            }
        }

        //On pose le fond
        apply_surface( 0, 0, background, screen );

        //On pose le message
        apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( ( SCREEN_HEIGHT + message->h * 2 ) / FRAMES_PER_SECOND ) * ( frame % FRAMES_PER_SECOND ) - message->h, message, screen );

        //Mise à jour de l'écran
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        //On incremente le compteur de frame
        frame++;

        //Si nous voulons reguler le frame rate
        if( cap == true )
        {
            //Tant que le timer fps n'est pas assez haut
            while( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
            {
                //On attend...
            }
        }
    }

    //Nettoyage
    clean_up();

    return 0;
}
