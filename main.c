#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <myconio.h>
/*
---------------------
--@jeux du demineur--
---------------------
réalisée dans le cadre d'un TP SIO/DEV 1er année IMC année 2013
créé par michael elbaz
*/

/* initialisation tableau global de *12X12* */
int tab[12][12];
/* init variable de test global */
int BOL = TRUE;
/* fonction creation initialisation du tableau en mémoire non visivble par l'utilisateur */
void tab_()
{
    /* tab 12 in memory */
    int i,j;
    for(i=0;i<12;i++)
    {
        for(j=0;j<12;j++)
        {
            tab[i][j] = 45/* '-' */;
        }
    }
}
/* affichage du tableau pour l'utilisateur */
void show_grid()
{
    int a,b;
    for(a=1;a<11;a++)
    {
        for(b=1;b<11;b++)
        {
            if(tab[a][b]==42)
            {
                textcolor(LIGHTRED);
            }
            else
            {
                textcolor(WHITE);
            }
            printf("%c",tab[a][b]);
        }
        printf("\n");
    }

}
/* mis en place de 10 MINES  de facon aléatoire~ */
void place_mine()
{
    int s,c,f;
    for(s=1;s<11;s++)
    {
        /* EMPECHE LIGNE EN 0 ET 11 */
        c = rand()% 10 + 1;
        f = rand()% 10 + 1;
        /* if->empeche d'ecraser une mine */
        if(tab[c][f] != 42) tab[c][f] = 42/* '*' */;
        else s--;
    }

}
/* devoilement des mines si l'utilisateur clique dessus */
int dev_mine(int o, int p)
{
    int b,n;
    if(tab[p][o]==42)
    {
        gotoxy(1,1);
        for(b=1;b<11;b++)
        {
            for(n=1;n<11;n++)
            {
              if(tab[b][n]==42)
              {
                tab[b][n]=42;
              }
              else
              {
                tab[b][n]=46/* '.' */;
              }
            }
             printf("\n");
        }
        gotoxy(1,1);
        show_grid();
        gotoxy(12,2);
        textcolor(LIGHTRED);
        printf("YOU LOSE ");
        system("pause");
        BOL = FALSE;
    }
}
/* on se deplace dans le tablau afficher à l'utilisateur */
void deplac_grid()
{
  int x=1,y=1,count=0,h,v,nb_coup=90,flag=10;
  char touch;
  gotoxy(x,y);
  do
  {
      touch=getch();
      /* cas des fléches de direction */
      if(touch==-32)
      {
          touch = getch();
          switch(touch)
          {
              case 75:
                if(x>1)x--;
                gotoxy(x,y);
              break;
              case 77:
                if(x<10)x++;
                gotoxy(x,y);
              break;
              case 80:
                if(y<10)y++;
                gotoxy(x,y);
              break;
              case 72:
                if(y>1)y--;
                gotoxy(x,y);
              break;
          }
          /*---utile pour déboger---*/
            //gotoxy(20,20);
            //printf("x :%i  y :%i ", x, y);
          /*---fin utile pour déboger---*/
          gotoxy(x,y);
      }
      /* cas de la touche espace */
      if(touch==32)
      {
         /* affiche le nombre de case qu'il rest a decouvrire moins les mines */
         if(tab[x][y]!=46 && BOL==TRUE)
         {
            nb_coup--;
            gotoxy(12,2);
            textcolor(LIGHTGREEN);
            printf("%i ",nb_coup);
            gotoxy(x,y);
         }
         /* si l'utilisateur a decouvert toutes les cases sans touucher a une mine il a gagné */
         if(nb_coup == 0)
         {
            gotoxy(12,2);
            textcolor(LIGHTGREEN);
            printf("YOU WIN ");
            system("pause");
            BOL=FALSE;
         }
         textcolor(WHITE);
         /* affichage d'un point sur les cases déja découverte */
         if(tab[x][y]==45) tab[x][y]=46;
         if(nb_coup != 0)  printf("%c",46);
         gotoxy(x,y);
         /* affiche le nombre de mine dans les 8 cases autour de celle découverte (si il y en a) */
         for(h=x-1;h<x+2;h++)
         {
            for(v=y-1;v<y+2;v++)
            {
                if(tab[v][h]==42)
                count++;
                if(count>0)
                {
                    switch(count)
                    {
                        case 1:textcolor(CYAN);break;
                        case 2:textcolor(LIGHTGREEN);break;
                        case 3:textcolor(YELLOW);break;
                        case 4:textcolor(LIGHTRED);break;
                        case 5:textcolor(LIGHTRED);break;
                        case 6:textcolor(LIGHTRED);break;
                        case 7:textcolor(LIGHTRED);break;
                        case 8:textcolor(LIGHTRED);break;
                        default:textcolor(WHITE);
                    }
                    printf("%i",count);
                    gotoxy(x,y);
               }
            }
         }
         count=0;
         dev_mine(x,y);
      }
     /* make flag (dans cette fonction l'utilisateur ne peut pas revenir en arriere
        si il use un drapeau il le perd) */
     if(touch==102)
     {
        flag--;
        if(x<=10&&y<=10&&flag>=0)
        {
            textcolor(LIGHTCYAN);
            printf("!");
            gotoxy(12,1);
            printf("flag : %i",flag);
            gotoxy(x,y);
        }
        gotoxy(x,y);
     }

  }while(touch!=27 && BOL == TRUE);
  getch();
}
main()
{
    system("title minesweeper");
    /* init rand with function time */
    srand(time(NULL));
    /* init tab in memory */
    tab_();
    /* show tab for user */
    show_grid();
    /* place mine after show tab */
    place_mine();
    /* move tab */
    deplac_grid();
}
