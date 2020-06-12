#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include "enigme.h"


int aleatoire(int n)
{
int alea;
do{
    srand(time(NULL));
     alea=1+rand()%n;
}while(alea==0||alea>n);
    return alea;
}

int compter_nombre_de_ligne_fichier(char* nom_fich)
{
int i;
char quest[200], rep1 [50],  rep2 [50],  solution[50];
  FILE* f=NULL;
char chaine[265]="";
f=fopen(nom_fich,"r");
if(f!=NULL)
{
//  (fscanf(f,"%s.%s.%s.%s. \n",quest,rep1,rep2,solution)!=EOF )
   while(fgets(chaine,256,f)!=NULL)
    {
        i++;  // i contient le nmbre de ligne de ton fichier
    }
fclose(f);
}

return i;
}



void return_question_repense(SDL_Surface *screen,char* nom_fich,char quest[200], char rep1 [50],  char rep2 [50], char solution [50])
{
FILE* f=NULL;
TTF_Font *police1 =NULL;
TTF_Font *police2 =NULL;
SDL_Surface *fonds=NULL;
SDL_Surface *question=NULL;
SDL_Surface *r1=NULL;
SDL_Surface *r2=NULL;
SDL_Surface *solu=NULL;

SDL_Rect position_question;
SDL_Rect position_r1;
SDL_Rect position_r2;
SDL_Rect position_solution;

 SDL_Color coulerNoir= {255,0,0};
TTF_Init();

  police1 = TTF_OpenFont("police1.ttf",45);
  police2 = TTF_OpenFont("police2.ttf",65);



SDL_Rect position_fonds;
position_fonds.x=0;
position_fonds.y=0;
fonds=IMG_Load("font.png");


int n_ligne=0;
int ligne,j,k=0;
int trouve;

n_ligne=0;
trouve=0;
char chaine[256]="";
char caractere;

ligne=compter_nombre_de_ligne_fichier("fichier.txt");
j=aleatoire(ligne);      
f=fopen(nom_fich,"r");
if(f!=NULL)
{

//fscanf(f,"%s/%s/%s/%s/\n",quest,rep1,rep2,solution)!=EOF && (j!=n_ligne) ;

while (fgets(chaine,256,f)!=NULL && j!=n_ligne)

   { n_ligne ++;}

if(j==n_ligne)
{
k=0;

do {
     caractere=fgetc(f);
     quest[k]=caractere;
     k++;
   }while(caractere!='?');


k=0;

do {
     caractere=fgetc(f);
     rep1[k]=caractere;
     k++;
   }while(caractere!='.');

k=0;

do {
     caractere=fgetc(f);
     rep2[k]=caractere;
     k++;
   }while(caractere!='.');

k=0;

do {
     caractere=fgetc(f);
     solution[k]=caractere;
     k++;
   }while(caractere!='.');

}

fclose(f);
}


question =TTF_RenderText_Blended(police1,quest,coulerNoir);
position_question.x=110;
position_question.y=200;

 r1 =TTF_RenderText_Blended(police2,rep1,coulerNoir);

 position_r1.x=200;
 position_r1.y=300;
 
r2 =TTF_RenderText_Blended(police2,rep2,coulerNoir);


 position_r2.x=200;
 position_r2.y=450;
printf("rep 1 x: %d y:%d\n", position_r1.x, position_r1.y);
 printf("rep 2 x: %d y:%d\n", position_r2.x, position_r2.y);


SDL_BlitSurface(fonds,NULL,screen,&position_fonds);
SDL_BlitSurface(question,NULL,screen,&position_question);
SDL_BlitSurface(r1,&position_fonds,screen,&position_r1);
SDL_BlitSurface(r2,&position_fonds,screen,&position_r2);

SDL_Flip(screen);

TTF_CloseFont(police1);
TTF_CloseFont(police2);
TTF_Quit();


}

int resolution (char* nom_fich,char quest[200], char rep1 [50],  char rep2 [50], char solution [50], SDL_Surface *screen)
{
char p,v;
SDL_Surface *fonds=NULL;
SDL_Surface *question=NULL;
SDL_Surface *r1=NULL;
SDL_Surface *r2=NULL;
SDL_Surface *solu=NULL;

SDL_Rect position_question;
SDL_Rect position_r1;
SDL_Rect position_r2;
SDL_Rect position_solution;

position_question.x=110;
position_question.y=200;

position_r2.x=200;
 position_r2.y=450;

position_r1.x=200;
 position_r1.y=300;

SDL_Event event;


int r=-1;
int continuer=1;
int a,b;
return_question_repense(screen,"fichier.txt",quest, rep1,rep2, solution);

while(continuer)
{


while(SDL_PollEvent(&event))
        {

switch(event.type)
        {
            case SDL_QUIT:
               { continuer = 0;
                break;
               }
            case SDL_MOUSEBUTTONDOWN:
{
a=event.button.x;
b=event.button.y ;


if (a > position_r1.x && a< position_r1.x + position_r1.w && b >position_r1.y && b < position_r1.y+45)
    {

    if(strcmp(rep1,solution)==0)
     {
      r=0;
continuer=0;
      }
    else
     {r=1;
     continuer=0;}


     }
else if (a > position_r2.x && a< position_r2.x+position_r2.w && b >position_r2.y && b <position_r2.y+45)
    {

if(strcmp(rep2,solution)==0)
      {r=0;
continuer=0;
}
    else
     {r=1;continuer=0;
     }


     }
break;
}
}
}
}
return r;

}
void afficher_resultat (SDL_Surface * screen,int r)
 {SDL_Surface *res=NULL;
SDL_Rect position;

 if (r==0)

{
res=IMG_Load("00.png");
        position.x = 00;
        position.y = 00;
 SDL_BlitSurface(res, NULL, screen, &position) ;
        SDL_Flip(screen);
 }
 else
 {
 res=IMG_Load("11.png");
 position.x = 00;
        position.y = 00;
 SDL_BlitSurface(res, NULL, screen, &position) ;
        SDL_Flip(screen);
 }
 }
