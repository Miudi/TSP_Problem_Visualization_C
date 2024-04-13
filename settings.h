/**
 * @file settings.c
 * @author Maciej Kwiecinski, Patryk Kręgiel, Olek Kurek
 * @date 29.05.2022
 * @brief File with global variables.
 */
 
#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

/** \brief Variable to classify with point is first for Closes Neighbour method. */
int first_point_Closes_Neighbour = 0; //Pierwszy element metody najblizszy krewny
/** \brief Variable to classify how many points are there.*/
int points_number = 0;
/** \brief Variable used for table.*/
const int rows = 4;
/** \brief Variable used to count how many permutations function actually finded.*/
int licznik =0;
/** \brief Variable used to save length of bruteforce route.*/
float droga=1500000;  // droga metody bruteforce
/** \brief Variable used to save length of closes neighbour route.*/
float droga_2=0;      //droga metody najblizszy krewny
/** \brief Variable used to ON/OFF testing. For eaxmple it will calculate path for random coordinates of points.*/
int test = 0;
/** \brief Variable used for planet graphic choosing.*/
int number = 1;






#endif // SETTINGS_H_INCLUDED
