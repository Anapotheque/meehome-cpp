#ifndef H_DEFINE
#define H_DEFINE

#include <iostream>
#include <fstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h> 
#include <SDL/SDL_framerate.h>

#include <string>

using namespace std;

//Taille de la fenetre
const int HEIGHT = 800;
const int WIDTH  = 600;

const int LIMIT_MIN_X = 10;
const int LIMIT_MIN_Y = 10;

const int LIMIT_MAX_X = WIDTH - 10;
const int LIMIT_MAX_Y = HEIGHT - 10; 

#endif
