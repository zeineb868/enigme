#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include "enigme.h"


int main()
{

char quest[200], rep1 [50],  rep2 [50],  solution [50];

       SDL_Surface *screen;
        SDL_Surface *background;

        SDL_Rect positionbackground;
  
        SDL_Event event ,event1;
        TTF_Font *police =NULL;
        char pause;
        int k,x ;
        int done=1;
        enigme e;

     
	
 screen=SDL_SetVideoMode(738,766,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
SDL_FillRect (screen,NULL,SDL_MapRGB(screen->format,128,0,0));
if(screen==NULL)
{
printf("Unable to set video mode: %s ",SDL_GetError());
return 1;
}
	 
      if(SDL_Init(SDL_INIT_VIDEO)!=0)
     {
	printf("Unable to inizialize SDL: %s \n",SDL_GetError());
     return 1;
    }

    
       background=IMG_Load("back.jpg");
         if (background==NULL)
        {
           printf("Unable to load on :%s \n",SDL_GetError());
          return 1;
        }
     positionbackground.x=0;
     positionbackground.y=0;

	SDL_BlitSurface(background,NULL,screen,&positionbackground);

//return_question_repense(screen,"fichier.txt",quest, rep1,rep2, solution);
int r=resolution ("fichier.txt",quest,rep1,rep2,solution,screen);
afficher_resultat (screen,r);

	 SDL_Flip(screen); 
	

SDL_FreeSurface(screen);
SDL_FreeSurface(background);
pause=getchar();

SDL_Quit();
	return 0;
}

     
        
    
