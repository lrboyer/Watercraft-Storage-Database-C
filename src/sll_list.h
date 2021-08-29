/*
  Name: Lucas Boyer
  Course: CPSC 1020 Spring Semester
  Project #: 1
  Instructor: Cathy Kittelstad
  Program Description: Using linked list keeps inventory of watercrafts
*/

#ifndef SLL_LIST_H
#define SLL_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	double bimini;  	  // cost of the add-on
	double towbar;
	double stereo;
	double table;
	double gps;
	double anchor;
	double paddles;
} accessories_t;
		
typedef struct watercraft {
	char type[15];     // e.g. pontoon, sport boat, sailboat, fishing, 
	                   //      canoe, kayak, jetski, etc.
	char make[20];
	char model[30];
	int propulsion;    // 0 = none; 1 = outBoard; 2 = inBoard; 
	char engine[15];   // Suzuki, Yamaha, etc.
	int hp;			    // horse power	
	char color[25];
	int length;        // feet
	double base_price;
	double total_price;
	accessories_t extras;
	struct watercraft *next;
} watercraft_t;


typedef struct list {
	watercraft_t *head;
	watercraft_t *tail;
	int size;
} list_t;


int printMenu( );  
list_t *newList( );
void listInit( list_t *list, FILE *inFile );
void initializeFromFile( list_t *list, FILE *inFile );
watercraft_t *new_waterCraft( FILE *inFile );

void addToFront( list_t *list );
void addToRear( list_t *list );

void printList ( list_t *list );
void printSpecs ( list_t *list );

void deleteWatercraft( list_t *list );

int typeInInventory( list_t *list, char whichOne[] );
int motorInInventory( list_t *list, int whichOne );
void printWatercraftByType( list_t *list, char whichOne[] );
void printWatercraftByMotor( list_t *list, int whichOne );
void searchByType( list_t *list );			 // pontoon, fishing boat, etc.
void searchByMotorType( list_t *list );    // e.g. inboard vs outboard

void printByPrice( list_t *list );   		 // list from lowest to highest

int isEmpty( list_t *list );

void TAV( list_t *list );  						 // Total Asset Value 

//Pass in the list and it will free all memory in the list
void freeMem( list_t *list); //I made this function to free memory easier

#endif /* SLL_LIST_H */
