/**
 * @file main.c
 * @author Maciej Kwiecinski, Patryk Kręgiel, Olek Kurek
 * @date 29.05.2022
 * @brief Main file of the project.
 */
 
 
/*Allegro 4.2.2 Syntax*/
// https://phoxis.org/2009/02/13/allegro-422/
// Dostêp: 2017-10-29

#include <stdio.h>
#include <allegro.h>
#include "settings.h"

#define RED makecol(255,0,0)
#define GREEN makecol(0,255,0)
#define BLUE makecol(0,0,255)
#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)
#define BLACK makecol(0,0,0)

/// Function to print coordinates on the screen.
///
/// @param cordinates This is pointer to table with coordinates of the points/planets, and the order for calculated route.
void print_points(int** cordinates){
    printf("Kordynaty nie posortowane : \n");
    int i,j;
    for(i=0;i<points_number;i++){
        printf("%c""%s",65+i," : ");
        for(j=0;j<rows;j++){
            printf("%d""%s", cordinates[i][j]," ");
        }
        printf("\n");
    }
}

/// Function to clear planets order by type.
///
/// @param cordinates This is pointer to table with coordinates of the points/planets, and the order for calculated route.
/// @param type This is variable used to clear just one type of order at time. For example Closes Neighbour route - (2), BruteForce = (3)
void clear_order(int **cordinates,int type){
    int i;
    for(i=0;i<points_number;i++){
            cordinates[i][type]=0;
    }
}

/// Function to print points coordinates sorted by type. For example Closes Neighbour - (2), BruteForce = (3)
///
/// @param cordinates This is pointer to table with coordinates of the points/planets, and the order for calculated route.
/// @param type This is variable used to print just one type of order at time. For example Closes Neighbour route - (2) BruteForce = (3)
void print_sorted_points(int** cordinates,int type){
    if(type == 2 ){printf("Kordynaty posortowane metoda Najblizszy krewny : \n");}
    if(type == 3 ){printf("Kordynaty posortowane metoda BruteForce : \n");}
    int i,j,g;
    for(i=1;i<points_number+1;i++){
       for(j=0;j<points_number;j++){
            if(i==cordinates[j][type]){
                printf("%c""%s",65+j," : ");
                for(g=0;g<rows;g++){
                    printf("%d" " ",cordinates[j][g]);
                }
            printf("\n");
            }
       }
    }
}

/// Function used for test's, it will fill coordinates table with random points.
///
/// @param cordinates This is pointer to table with coordinates of the points/planets, and the order for calculated route.
void losuj_kordynaty(int** cordinates){
    int i,j;

    for(i=0;i<points_number;i++){
        for(j=0;j<rows;j++){
            if(j==2||j==3){
                cordinates[i][j]=0;
            }else{
                cordinates[i][j] = rand()%100;
            }
        }
    }
}

/// Function to swap 2 points.
///
/// @param jeden First point variable to swap.
/// @param dwa Second point variable to swap.
void swap(int *jeden, int *dwa)
{
    int i =0;
    int *temp;
    for(i=0;i<rows;i++){
        temp = jeden[i];
        jeden[i] = dwa[i];
        dwa[i] = temp;
    }
}

/// Function to check the length between two points provided by parameters.
///
/// @param x_a - Variable with X coordinate of first point.
/// @param y_a - Variable with X coordinate of second point.
/// @param x_b - Variable with Y coordinate of first point.
/// @param y_b - Variable with Y coordinate of second point.
float check_length_between(int x_a,int y_a,int x_b, int y_b){
    float length=0;
    x_a=abs(x_a-x_b);
    y_a=abs(y_a-y_b);
    length = hypot(x_a,y_a);
    return length;
}


/// Function to sum every lengths between points in order.
///
/// @param cordinates This is pointer to table with coordinates of the points/planets, and the order for calculated route.
float sum_between(int** cordinates){
    int i;
    float length=0, suma=0;
    for(i=0;i<points_number-1;i++){
        length=check_length_between(cordinates[i][0],cordinates[i][1],cordinates[i+1][0],cordinates[i+1][1]);
        //printf("%d-%d: %f\n", i+1, i+2, length);
        suma+=length;
    }
    suma+=check_length_between(cordinates[0][0],cordinates[0][1],cordinates[points_number-1][0],cordinates[points_number-1][1]);
    //printf("suma: %f\n", suma);
    return suma;
}

/// Function to sum every lengths between points in order.
///
/// @param cordinates This is pointer to table with coordinates of the points/planets, and the order for calculated route.
/// @param l This is variable used for permutations, it will increase every time function will call herself.
void permute(int** cordinates, int l)
{
    int i,h;
    if (l == points_number-1){
        //print_points(cordinates);
        if(sum_between(cordinates)<droga){
            droga = sum_between(cordinates);
            for(h=0;h<points_number;h++){
                cordinates[h][3]=h+1;
            }
            //printf("%1.3f\n",droga);
           //print_points(cordinates);
        }
        licznik++;//liczba permutacji
        //printf("\n\n");
    }else
    {
        for (i = l; i <= points_number-1; i++)
        {
            swap(cordinates[l], cordinates[i]);
            permute(cordinates, l+1);
            swap(cordinates[l], cordinates[i]); //backtrack
        }
    }
}

/// Function to calculate order for closes neighbour. It will also calcualte the length of that full route.
///
/// @param cordinates This is pointer to table with coordinates of the points/planets, and the order for calculated route.
/// @param first This is variable to choose with point is first in closes neighbour.
void closed_neighbouor(int** cordinates,int first){
    int i,j;
    int kolejnosc=1;
    int current_best=0;
    int index=first;
    float length=0;
    float length_2=0;
    cordinates[first][2]=1;//odwiedzony
    for(i=0;i<points_number-1;i++){
            for(j=0;j<points_number;j++){
                if(cordinates[j][2]==0){
                    if(length==0){//przypisanie odleglosci pomiedzy pierwszymi wolnymi elementami
                        length=check_length_between(cordinates[index][0],cordinates[index][1],cordinates[j][0],cordinates[j][1]);
                        current_best = j;
                    }else{
                        length_2=check_length_between(cordinates[index][0],cordinates[index][1],cordinates[j][0],cordinates[j][1]);
                        if(length>length_2){
                             length = length_2;
                             current_best = j;
                        }
                    }
                }
            }
            droga_2+=check_length_between(cordinates[index][0],cordinates[index][1],cordinates[current_best][0],cordinates[current_best][1]); //Dorga z obecnego punktu do najblizszego kolejnego
            kolejnosc++;//Licznik do kolejnosci metoda najblizszy krewny
            cordinates[current_best][2]=kolejnosc;//przypisanie kolejnosci jako kolejna kolumna oraz oznaczenie jako juz odwiedzony
            index=current_best;//obecnie odwiedzony nastepny kandydat, nastpna iteracja sprawdza najblizszy element do niego
            length=0;
    }
    droga_2+=check_length_between(cordinates[0][0],cordinates[0][1],cordinates[current_best][0],cordinates[current_best][1]); //Powrot z ostatniego punktu na poczatek
}

/// Function used to draw planet after click.
///
/// @param x X coordinate for planet to draw.
/// @param y Y coordinate for planet to draw.
/// @param buffer BITMAP used to draw planet in it.
/// @param BITMAPS_LIST BITMAP's table with all planets graphic inside.
void draw_planet(int x,int y,BITMAP *buffer,BITMAP *BITMAPS_LIST[]){
    if(number<20){
        draw_sprite(buffer,BITMAPS_LIST[number],x-25,y-25);
        number++;
        points_number++;

    }else{
        number=1;
        draw_sprite(buffer,BITMAPS_LIST[number],x-25,y-25);
        number++;
        points_number++;
    }
}

/// Function used to add point to cordinates table.
///
/// @param x X coordinate of planet.
/// @param y Y coordinate of planet.
/// @param cordinates This is pointer to table with coordinates of the points/planets, and the order for calculated route.
void dodaj_punkt(int x,int y,int** cordinates){
    cordinates[points_number] = (int*)malloc(rows*sizeof(int));
    cordinates[points_number][0]=x;
    cordinates[points_number][1]=y;
    cordinates[points_number][2]=0;
    cordinates[points_number][3]=0;
}

/// Function used to draw solution lines on the screen, depends on type.
///
/// @param cordinates This is pointer to table with coordinates of the points/planets, and the order for calculated route.
/// @param type This is variable used to draw just one type of order at time. For example Closes Neighbour route - (2), BruteForce = (3)
void draw_solution(int** cordinates, int type){
    int i,j;
    int obecny=0;
    if(type>0){
        for(i=1;i<=points_number;i++){
            for(j=1;j<points_number;j++){
                    if(cordinates[j][type]==i){
                        line(screen,cordinates[obecny][0],cordinates[obecny][1],cordinates[j][0],cordinates[j][1],makecol(10+i%10*17,30+i%10*24,20+i%10*10));
                        obecny = j;
                    }
            }
        }
        line(screen,cordinates[obecny][0],cordinates[obecny][1],cordinates[0][0],cordinates[0][1],RED);
    }else if(type==0){
        int licznik=0;
        for(i=1;i<points_number;i++){
            line(screen,cordinates[i][0],cordinates[i][1],cordinates[licznik][0],cordinates[licznik][1],makecol(10+i*17,30+i*24,20+i*10));
            licznik++;
        }
        line(screen,cordinates[0][0],cordinates[0][1],cordinates[points_number-1][0],cordinates[points_number-1][1],RED);
    }

}


int main(void)
{
srand(time(NULL));
allegro_init();
install_keyboard();
install_mouse();
install_timer();
//allegro_message("This is the first allegro program (Press OK)");
set_color_depth(8);
if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,1800,1000,0,0))
{
    allegro_message(allegro_error);
    exit(0);
}

if(test == 1){
        points_number = 2;
        int* cordinates[points_number];
        int i;
        for(i = 0; i<points_number; i++){
            cordinates[i] = (int*)malloc(rows*sizeof(int)); //dla każdegu punktu sporządz tablice 2 elementową [kordynaty x,y]
        }
        losuj_kordynaty(cordinates);
        permute(cordinates, 1);
        closed_neighbouor(cordinates,first_point_Closes_Neighbour);
        print_points(cordinates);
        printf("\n");
        print_sorted_points(cordinates,2);
        printf("\n");
        print_sorted_points(cordinates,3);
        printf("\n");
        printf("Droga podstawowa (Nie sortowane): %1.3f \n",sum_between(cordinates));
        printf("Droga optymalna (Najblizsy krewny) : %1.3f \n",droga_2);
        printf("Droga najkrotsza (BruteForce) : %1.3f \n",droga);
        printf("Liczba permutacji : %d na liczbe punktow ( pierwszy jest staly ) : %d\n",licznik, points_number);
    }

show_mouse(screen);
//START_OF_BITMAP's
BITMAP *space_background = create_bitmap(1800,1000);
space_background = load_bitmap("bitmaps/space_background.bmp",NULL);
BITMAP *BITMAPS_LIST[20];

BITMAPS_LIST[1] = create_bitmap(100,100);//Stworzenie wirtualnego ekranu o rozmiarach 25,25
BITMAPS_LIST[1] = load_bitmap("bitmaps/1.bmp",NULL);//Ponieważ grafika zajmuje całą bitmape to nie trzeba jej czyścić.
BITMAPS_LIST[2] = create_bitmap(100,100);
BITMAPS_LIST[2] = load_bitmap("bitmaps/2.bmp",NULL);
BITMAPS_LIST[3] = create_bitmap(100,100);
BITMAPS_LIST[3] = load_bitmap("bitmaps/3.bmp",NULL);
BITMAPS_LIST[4] = create_bitmap(100,100);
BITMAPS_LIST[4] = load_bitmap("bitmaps/4.bmp",NULL);
BITMAPS_LIST[5] = create_bitmap(100,100);
BITMAPS_LIST[5] = load_bitmap("bitmaps/5.bmp",NULL);
BITMAPS_LIST[6] = create_bitmap(100,100);
BITMAPS_LIST[6] = load_bitmap("bitmaps/6.bmp",NULL);
BITMAPS_LIST[7] = create_bitmap(100,100);
BITMAPS_LIST[7] = load_bitmap("bitmaps/7.bmp",NULL);
BITMAPS_LIST[8] = create_bitmap(100,100);
BITMAPS_LIST[8] = load_bitmap("bitmaps/8.bmp",NULL);
BITMAPS_LIST[9] = create_bitmap(100,100);
BITMAPS_LIST[9] = load_bitmap("bitmaps/9.bmp",NULL);
BITMAPS_LIST[10] = create_bitmap(100,100);
BITMAPS_LIST[10] = load_bitmap("bitmaps/10.bmp",NULL);
BITMAPS_LIST[11] = create_bitmap(100,100);
BITMAPS_LIST[11] = load_bitmap("bitmaps/11.bmp",NULL);
BITMAPS_LIST[12] = create_bitmap(100,100);
BITMAPS_LIST[12] = load_bitmap("bitmaps/12.bmp",NULL);
BITMAPS_LIST[13] = create_bitmap(100,100);
BITMAPS_LIST[13] = load_bitmap("bitmaps/13.bmp",NULL);
BITMAPS_LIST[14] = create_bitmap(100,100);
BITMAPS_LIST[14] = load_bitmap("bitmaps/14.bmp",NULL);
BITMAPS_LIST[15] = create_bitmap(100,100);
BITMAPS_LIST[15] = load_bitmap("bitmaps/15.bmp",NULL);
BITMAPS_LIST[16] = create_bitmap(100,100);
BITMAPS_LIST[16] = load_bitmap("bitmaps/16.bmp",NULL);
BITMAPS_LIST[17] = create_bitmap(100,100);
BITMAPS_LIST[17] = load_bitmap("bitmaps/17.bmp",NULL);
BITMAPS_LIST[18] = create_bitmap(100,100);
BITMAPS_LIST[18] = load_bitmap("bitmaps/18.bmp",NULL);
BITMAPS_LIST[19] = create_bitmap(100,100);
BITMAPS_LIST[19] = load_bitmap("bitmaps/19.bmp",NULL);



BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);//Buffer czyli zastępczy wirutalny ekran na którym rysowana jest kolejna klatka - zapobiega migotaniu ekranu
clear(buffer);//Standardowa bitmapa nie jest wyczyszczona i może zawierać zbędny szum, dlatego należy ją wyczyścić0
draw_sprite(buffer,space_background,0,0);
//END_OF_BITMAPS

draw_sprite(screen,space_background,0,0);
int* cordinates[100];
        int i;
        //for(i = 0; i<points_number; i++){
        //  cordinates[i] = (int*)malloc(rows*sizeof(int)); //dla każdegu punktu sporządz tablice 2 elementową [kordynaty x,y]
        //}
     textprintf(screen,font,1450,885,WHITE,"ESC -> EXIT PROGRAMs");
     textprintf(screen,font,1450,900,WHITE,"LEFT CLICK -> ADDING PLANET");
     textprintf(screen,font,1450,915,WHITE,"SPACE -> CALCULATING ROUTE BruteForce");
     textprintf(screen,font,1450,930,WHITE,"B -> Draw BruteForce solution");
     textprintf(screen,font,1450,945,WHITE,"N -> Draw ClosesNeighbour solution");
     textprintf(screen,font,1450,960,WHITE,"S -> DRAW Standard not sorted 'solution'");

     draw_sprite(buffer,screen,0,0);
while(!key[KEY_ESC]){

 if(test == 0){

        if(key[KEY_ESC]){
            break;
        }


        if(mouse_b&1){//Wykrycie klikniecia lewym przyciskiem myszki
            draw_sprite(screen,buffer,0,0);
            dodaj_punkt(mouse_x,mouse_y,cordinates);
            draw_planet(mouse_x,mouse_y,buffer,BITMAPS_LIST);
            draw_sprite(screen,buffer,0,0);
            rest(250);
        }
        if(key[KEY_SPACE]){//start calculating
             clear_order(cordinates,2);
             clear_order(cordinates,3);
             draw_sprite(screen,buffer,0,0);
             rest(300);
             droga=1500000;
             droga_2=0;
             closed_neighbouor(cordinates,first_point_Closes_Neighbour);
             permute(cordinates,1);
        }

        if(key[KEY_B]){
            if(cordinates[points_number-1][3]==0){
                clear_order(cordinates,3);
                droga=1500000;
                permute(cordinates,1);
                clear_order(cordinates,2);
                droga_2=0;
                closed_neighbouor(cordinates,first_point_Closes_Neighbour);
            }
            draw_sprite(screen,buffer,0,0);
            draw_solution(cordinates,3);
        }
         if(key[KEY_N]){
            clear_order(cordinates,2);
            droga_2=0;
            closed_neighbouor(cordinates,first_point_Closes_Neighbour);
            draw_sprite(screen,buffer,0,0);
            draw_solution(cordinates,2);
        }
         if(key[KEY_S]){
             draw_sprite(screen,buffer,0,0);
            draw_solution(cordinates,0);
        }




        if(points_number>0){
                textprintf(screen,font,0,3,WHITE,"Liczba pkt %d Podstawowa droga : %1.3f Najkrotsza droga : %1.3f Droga najblizszegokrewnego : %1.3f",points_number,sum_between(cordinates),droga,droga_2);
            int h=0;
            for(h=0;h<points_number;h++){
                   textprintf(screen,font,15,15+h*15,WHITE,"Punkt %d %d %d %d",cordinates[h][0],cordinates[h][1],cordinates[h][2],cordinates[h][3]);
            }
        }
        if(points_number>0){
            textprintf(screen,font,cordinates[0][0]-18,cordinates[0][1]-35,WHITE,"EARTH");
            if(points_number>1){
                textprintf(screen,font,700,60,RED,"RED ARROW IS A TRACK_BACK ARROW");
            }
        }
    }
}
allegro_exit();
return 0;
}
END_OF_MAIN();







