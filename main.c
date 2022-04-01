#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "settings.h"

const int rows = 3;

void print_points(int** cordinates)
{
    int i,j;
    for(i=0;i<points_number;i++)
    {
        for(j=0;j<rows-1;j++)
        {
            printf("%d""%s", cordinates[i][j]," ");
        }
        printf("\n");
    }
}

void print_sorted_points(int** cordinates)
{
    int i, j, g;
    for(i=1;i<points_number+1;i++)
    {
       for(j=0;j<points_number;j++)
       {
            if(i==cordinates[j][2])
            {
                for(g=0;g<rows;g++)
                {
                    printf("%d" " ",cordinates[j][g]);
                }
                printf("\n");
            }
        }
    }
}

void losuj_kordynaty(int** cordinates)
{
    int i, j;
    for(i=0;i<points_number;i++)
    {
        for(j=0;j<rows;j++)
        {
            if(j==2)
            {
                cordinates[i][j]=0;
            }
            else
            {
                cordinates[i][j] = rand()%100;
            }
        }
    }
}

float check_length_between(int x_a,int y_a,int x_b, int y_b)
{
    float length=0;
    x_a=abs(x_a-x_b);
    y_a=abs(y_a-y_b);
    length = hypot(x_a,y_a);
    return length;
}

void closed_neighbouor(int** cordinates, int first)
{
    int i, j;
    int kolejnosc=1;
    int current_best=0;
    int index=first;
    float length=0;
    float length_2=0;
    float suma;
    cordinates[first][2]=1;//odwiedzony
    for(i=0;i<points_number-1;i++)
    {
        for(j=0;j<points_number;j++)
        {
            if(cordinates[j][2]==0)
            {
                if(length==0)
                {
                    length=check_length_between(cordinates[index][0],cordinates[index][1],cordinates[j][0],cordinates[j][1]);
                    current_best = j;
                }
                else
                {
                    length_2=check_length_between(cordinates[index][0],cordinates[index][1],cordinates[j][0],cordinates[j][1]);
                    if(length>length_2)
                    {
                        length = length_2;
                        current_best = j;
                    }
                }
            }
        }
        suma+=length;
        kolejnosc++;
        //printf("kolejnosc : ""%d", kolejnosc);
        cordinates[current_best][2]=kolejnosc;
        index=current_best;
        length=0;
    }
    printf("suma: %f (powinna wypisac sie pod trasa \"po kolei\")", suma);
    printf("\n");
}

void sum_between(int** cordinates)
{
    int i;
    float length, suma;
    for(i=0;i<points_number-1;i++)
    {
        length=check_length_between(cordinates[i][0],cordinates[i][1],cordinates[i+1][0],cordinates[i+1][1]);
        printf("%d-%d: %f\n", i+1, i+2, length);
        suma+=length;
    }
    printf("suma: %f\n", suma);
}



int main()
{
    int* cordinates[points_number];
    int i;
    for(i = 0; i<points_number; i++)
    {
        cordinates[i] = (int*)malloc(rows*sizeof(int)); //dla każdegu punktu sporządz tablice 2 elementową [kordynaty x,y]
    }
    printf("Koordynaty: \nx y\n");
    losuj_kordynaty(cordinates);
    print_points(cordinates);

    printf("\nKoordynaty przydzielona kolejnosc ale nie posortowane: \nx y kolejnosc\n");
    print_points(cordinates);
    closed_neighbouor(cordinates,0);

    printf("\nKoordynaty posortowane wedlug kolejnosci: \nx y kolejnosc\n");
    print_sorted_points(cordinates);

    printf("\nTrasa po kolei: \n");
    sum_between(cordinates);

    printf("\nTrasa posortowana: \n(suma powinna wypisac sie w tym miejscu)");


    //czyszczenie pointerow
    for(i=0; i<points_number; i++)
    {
        free(cordinates[i]);
    }
    return 0;
}
