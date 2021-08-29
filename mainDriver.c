 /*
  Name: Lucas Boyer
  Course: CPSC 1020 Spring Semester
  Project #: 1
  Instructor: Cathy Kittelstad
  Program Description: Using linked list keeps inventory of watercrafts
*/

#include "src/sll_list.h"

int main(int argc, char* argv[]) {
    FILE * in = fopen(argv[1], "r");
    list_t* inventory = newList();
    
    int choice;
    printf("\n");

    //this will keep printing the menu and asking for a choice until the user inputs 12
    while (choice != 12) { 
        choice = printMenu();
        //this manages each case for each one of the 12 choices on the menu
        switch(choice) {
            case 1:
                if (in != NULL) {
                    initializeFromFile(inventory, in);
                    printf("Loaded watercraft from file.\n\n\n");
                    fclose(in);
                    in = NULL; //closes file pointer and set to null so it wont be used anymore
                }
                else {
                    printf("** List is already initialized. **\n\n\n");
                }
                break;
            case 2:
                addToFront(inventory);
                break;
            case 3: 
                addToRear(inventory);
                break;
            case 4:
                printf("There are %d watercraft in inventory.\n\n\n", inventory->size);
                break;
            case 5:
                printList(inventory);
                break;
            case 6:
                printSpecs(inventory);
                break;
            case 7: 
                deleteWatercraft(inventory);
                break;
            case 8:
                searchByType(inventory);
                break;
            case 9:
                searchByMotorType(inventory);
                break;
            case 10:
                printByPrice(inventory);
                break;
            case 11: 
                TAV(inventory);
                break;
            case 12: //quits
                freeMem(inventory);
                break;
            default:
                printf("please select an option 1-12\n\n\n");
                break;
        }  
    }
    
    return 0;
}