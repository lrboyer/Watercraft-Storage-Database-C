/*
  Name: Lucas Boyer
  Course: CPSC 1020 Spring Semester
  Project #: 1
  Instructor: Cathy Kittelstad
  Program Description: Using linked list keeps inventory of watercrafts
*/

#include "sll_list.h"

//prints menu and gets input and returns it
int printMenu() {
    int num;
    
    printf(" 1. load inventory of watercraft from file\n"
    " 2. add additional watercraft to front of list\n"
    " 3. add additional watercraft to end of list\n"
    " 4. number of watercraft in inventory\n"
    " 5. print inventory of watercraft\n"
    " 6. print specs of chosen watercraft\n"
    " 7. delete chosen watercraft\n"
    " 8. search watercraft by type\n"
    " 9. search watercraft by motor type\n"
    "10. sort watercraft by price\n"
    "11. total asset value in inventory\n"
    "12. quit program\n");

    printf("\n- - > ");
    scanf("%d", &num);
    printf("\n\n");
    return num;
}

//This creates a new list, allocates memory, and returns it
list_t *newList() {
    list_t* list = (list_t*)malloc(sizeof(list_t));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;
}

//Reads file and scans for input for all data then adds it to the list
void listInit(list_t *list, FILE *inFile) {
    watercraft_t* newVehicle = new_waterCraft(inFile);

    fscanf(inFile, " %[^,],", newVehicle->type);
    fscanf(inFile, "%[^,],", newVehicle->make);
    fscanf(inFile, "%[^,],", newVehicle->model);
    fscanf(inFile, "%d ,", &newVehicle->propulsion);
    fscanf(inFile, "%[^,],", newVehicle->engine);
    fscanf(inFile, "%d ,", &newVehicle->hp);
    fscanf(inFile, "%[^,],", newVehicle->color);
    fscanf(inFile, "%d ,", &newVehicle->length);
    fscanf(inFile, "%lf ,", &newVehicle->base_price);
    fscanf(inFile, "%lf ,", &newVehicle->total_price);
    
    //accessories
    fscanf(inFile, "%lf ,", &newVehicle->extras.bimini);
    fscanf(inFile, "%lf ,", &newVehicle->extras.towbar);
    fscanf(inFile, "%lf ,", &newVehicle->extras.stereo);
    fscanf(inFile, "%lf ,", &newVehicle->extras.table);
    fscanf(inFile, "%lf ,", &newVehicle->extras.gps);
    fscanf(inFile, "%lf ,", &newVehicle->extras.anchor);
    fscanf(inFile, "%lf\n", &newVehicle->extras.paddles);
    
    //if list is empty then set node to head and tail
    if (isEmpty(list) == 1) {
        newVehicle->next = NULL;
        list->head = newVehicle;
        list->tail = newVehicle;
    }
    //else add to end of list
    else {
        list->tail->next = newVehicle;
        list->tail = list->tail->next;
    }
    list->size++;
}

//loops listInit until end of file
void initializeFromFile(list_t *list, FILE *inFile) {
    //until reaching the end of file it calls the listInit func to scan file
    while (!feof(inFile)) {
        listInit(list, inFile);
    }
}

//makes a new watercraft, allocates memory then returns it
watercraft_t *new_waterCraft(FILE *inFile) {
    //makes new watercraft and allocates memory and returns it
    watercraft_t* newVehicle;
    newVehicle = (watercraft_t*)malloc(sizeof(watercraft_t));

    return newVehicle;
}

//adds watercraft with data in it to front of list
void addToFront(list_t *list) {
    watercraft_t* newVehicle = (watercraft_t*)malloc(sizeof(watercraft_t));
    
    char type[16];
    char make[21];
    char model[31];

    printf("\n\nEnter watercraft type:\n\t");
    getchar(); //it skips input b\c of a newline so this prevents that
    fgets(type, 15, stdin); //this scans for input with spaces
    strtok(type, "\n"); //this removes new line char from end of input
    strcpy(newVehicle->type, type); //then copies into the watercraft data

    printf("\n\nEnter watercraft make:\n\t");
    fgets(make, 20, stdin);
    strtok(make, "\n");
    strcpy(newVehicle->make, make);

    printf("\n\nEnter watercraft model:\n\t");
    fgets(model, 30, stdin);
    strtok(model, "\n");
    strcpy(newVehicle->model, model);

    printf("\n\nEnter 0 for no motor, 1 for out-board, 2 for in-board:\n\t");
    scanf("%d", &newVehicle->propulsion);
    printf("\n\nEnter engine make:\n\t");
    scanf("%s", newVehicle->engine);
    printf("\n\nHow much horsepower does the engine have?\n\t");
    scanf("%d", &newVehicle->hp);
    printf("\n\nEnter color of watercraft:\n\t");
    scanf("%s", newVehicle->color);
    printf("\n\nLength of watercraft:\n\t");
    scanf("%d", &newVehicle->length);
    printf("\n\nBase price of watercraft:\n\t");
    scanf("%lf", &newVehicle->base_price);
    printf("\n\nCost of bimini (if there is an extra cost):\n\t");
    scanf("%lf", &newVehicle->extras.bimini);
    printf("\n\nCost of towbar (if there is an extra cost):\n\t");
    scanf("%lf", &newVehicle->extras.towbar);
    printf("\n\nCost of stereo (if there is an extra cost):\n\t");
    scanf("%lf", &newVehicle->extras.stereo);
    printf("\n\nCost of table (if there is an extra cost):\n\t");
    scanf("%lf", &newVehicle->extras.table);
    printf("\n\nCost of gps (if there is an extra cost):\n\t");
    scanf("%lf", &newVehicle->extras.gps);
    printf("\n\nCost of anchor (if there is an extra cost):\n\t");
    scanf("%lf", &newVehicle->extras.anchor);
    printf("\n\nCost of paddles (if there is an extra cost):\n\t");
    scanf("%lf", &newVehicle->extras.paddles);
    printf("\n\n\n");
    
    //this calculates the total price
    newVehicle->total_price = newVehicle->base_price + newVehicle->extras.bimini
     + newVehicle->extras.towbar + newVehicle->extras.stereo + newVehicle->extras.table 
      + newVehicle->extras.gps + newVehicle->extras.anchor + newVehicle->extras.paddles;

    if (isEmpty(list) == 1) {
        newVehicle->next = NULL;
        list->head = newVehicle;
        list->tail = newVehicle;
    }
    else {
        newVehicle->next = list->head;
        list->head = newVehicle;
    }
    list->size++;
}

//this is same to addToFront except inserts the watercraft to the rear of the list
void addToRear(list_t *list) {
    watercraft_t* newVehicle = (watercraft_t*)malloc(sizeof(watercraft_t));

    char type[15];
    char make[20];
    char model[30];

    printf("\n\nEnter watercraft type:\n\t");
    getchar();
    fgets(type, 15, stdin); 
    strtok(type, "\n");
    strcpy(newVehicle->type, type);

    printf("\n\nEnter watercraft make:\n\t");
    fgets(make, 20, stdin);
    strtok(make, "\n");
    strcpy(newVehicle->make, make);

    printf("\n\nEnter watercraft model:\n\t");
    fgets(model, 30, stdin);
    strtok(model, "\n");
    strcpy(newVehicle->model, model);

    printf("\n\nEnter 0 for no motor, 1 for out-board, 2 for in-board:\n\t");
    scanf("%d", &newVehicle->propulsion);
    printf("\n\nEnter engine make:\n\t");
    scanf("%s", newVehicle->engine);
    printf("\n\nHow much horsepower does the engine have?\n\t");
    scanf("%d", &newVehicle->hp);
    printf("\n\nEnter color of watercraft:\n\t");
    scanf("%s", newVehicle->color);
    printf("\n\nLength of watercraft:\n\t");
    scanf("%d", &newVehicle->length);
    printf("\n\nBase price of watercraft:\n\t");
    scanf("%lf", &newVehicle->base_price);
    printf("\n\nCost of bimini (if there is an extra cost):\n\t");
    scanf("%lf", &newVehicle->extras.bimini);
    printf("\n\nCost of towbar (if there is an extra cost):\n\t");
    scanf("%lf", &newVehicle->extras.towbar);
    printf("\n\nCost of stereo (if there is an extra cost):\n\t");
    scanf("%lf", &newVehicle->extras.stereo);
    printf("\n\nCost of table (if there is an extra cost):\n\t");
    scanf("%lf", &newVehicle->extras.table);
    printf("\n\nCost of gps (if there is an extra cost):\n\t");
    scanf("%lf", &newVehicle->extras.gps);
    printf("\n\nCost of anchor (if there is an extra cost):\n\t");
    scanf("%lf", &newVehicle->extras.anchor);
    printf("\n\nCost of paddles (if there is an extra cost):\n\t");
    scanf("%lf", &newVehicle->extras.paddles);
    printf("\n\n\n");

    newVehicle->total_price = newVehicle->base_price + newVehicle->extras.bimini
     + newVehicle->extras.towbar + newVehicle->extras.stereo + newVehicle->extras.table 
      + newVehicle->extras.gps + newVehicle->extras.anchor + newVehicle->extras.paddles;

    if (list->head == NULL) {
        newVehicle->next = NULL;
        list->head = newVehicle;
        list->tail = newVehicle;
    }
    else {
        newVehicle->next = NULL;
        list->tail->next = newVehicle;
    }
    list->size++;
}

//prints out all watercrafts in list
void printList (list_t *list) {
    int i = 0;
    
    if (isEmpty(list) == 1) {
        printf("The list is empty\n");
    }
    else {
        watercraft_t* current = list->head;
        printf("Watercraft in list:\n\n");
        
        //until current node reaches end of list it prints out the data
        while (current != NULL) {
            printf("%2d. ", i+1);
            printf("%-15s", current->type);
            printf("%-20s", current->make);
            printf("%-25s", current->model);
            printf("%-13s", current->engine);
            printf("%4dhp    ", current->hp);
            printf("%-20s", current->color);
            printf("%3dft  ", current->length);
            printf("$%10.2lf", current->total_price);
            printf("\n");
            i++;
            current = current->next;
        }
    }
    printf("\n\n");
}

//prints specs of the selected watercraft
void printSpecs (list_t *list) {
    watercraft_t* current = list->head;
    int num;
    
    if (isEmpty(list) == 1) {
        printf("The list is empty\n\n\n");
    }
    else {
        printList(list);
        printf("Enter the # of the watercraft for the specs:");
        printf("\n- - > ");
        scanf("%d", &num);
        
        //checks to see if num entered is a valid watercraft # in the list
        if (num > 0 && num <= list->size) {
            //starts at head of list and goes until on the selected watercraft
            for (int i = 0; i < num - 1; i++) {
                current = current->next;
            }

            printf("%2d. ", num);
            printf("%-15s", current->type);
            printf("%-20s", current->make);
            printf("%-25s", current->model);
            printf("%-13s", current->engine);
            printf("%4dhp    ", current->hp);
            printf("%-20s", current->color);
            printf("%3dft  ", current->length);
            printf("$%10.2lf", current->total_price);

        //prints out: 0 for no motor, 1 for out-board motor, and 2 for in-board 
            if (current->propulsion == 0) {
                printf("\n\tno motor");
            }
            if (current->propulsion == 1) {
                printf("\n\tout-board motor");
            }
            if (current->propulsion == 2) {
                printf("\n\tin-board motor");
            }

            printf("\n\tbase price: $%12.2lf\n", current->base_price);

            //these will check to see if the price of the accessory isn't
            // 0 so it doesn't print out 0 for the price of an accessory
            if (current->extras.bimini != 0) {
                printf("\tbimini:     $%12.2lf\n", current->extras.bimini);
            }
            if (current->extras.towbar != 0) {
                printf("\ttowbar:     $%12.2lf\n", current->extras.towbar);
            }
            if (current->extras.stereo != 0) {
                printf("\tstereo:     $%12.2lf\n", current->extras.stereo);
            }
            if (current->extras.table != 0) {
                printf("\ttable:      $%12.2lf\n", current->extras.table);
            }
            if (current->extras.gps != 0) {
                printf("\tgps:        $%12.2lf\n", current->extras.gps);
            }
            if (current->extras.anchor != 0) {
                printf("\tanchor:     $%12.2lf\n", current->extras.anchor);
            }
            if (current->extras.paddles != 0) {
                printf("\tpaddles:    $%12.2lf\n", current->extras.paddles);
            }

            printf("\n\n\n");
        }
        else {
            printf("That watercraft doesn't exist\n\n");
        }
    }
}

//deletes selected watercraft
void deleteWatercraft(list_t *list) {
    watercraft_t* current = list->head;
    watercraft_t* prev = list->head;
    int num;
    
    if (isEmpty(list) == 1) {
        printf("The list is empty\n\n\n");
    }
    else {
        printList(list); 

        printf("Enter the # of the watercraft to delete from inventory:\n");
        printf("\n- - > ");
        scanf("%d", &num);
        printf("\n\n");

        //checks to see if valid watercraft #
        if (num > 0 && num <= list->size) {
            if (current != NULL && num == 1) { //if the head node is the targeted one for deletion
                list->head = current->next; 
                free(current);
            }
            else {
                for (int i = 0; i < num - 1; i++) { //loops thru to find targeted number
                    prev = current;
                    current = current->next;
                }
                if (current != NULL && current->next == NULL) { //if tail node then it deletes it
                    free(current);
                    list->tail = prev;
                    list->tail->next = NULL;
                }
                else { //when on the target watercraft it deletes it
                    prev->next = current->next;
                    free(current);
                }
            //decrements the size of list
            list->size--;
            }
        } 
        else {
            printf("That watercraft doesn't exist\n\n");
        }
    }
}

//searches watercraft types in inventory and returns if it has been found
int typeInInventory(list_t *list, char whichOne[]) {
    watercraft_t* current = list->head;
    int found = 0;

    //goes thru list and checks to see if the type entered equals a type in the list
    //if founnd returns 1 if not 0
    while (current != NULL) {
        if(strcmp(current->type, whichOne) == 0) {
            found = 1;
        }
        current = current->next;
    }
        return found;
}

//searches watercraft motors in inventory and returns if found
int motorInInventory(list_t *list, int whichOne) {
    watercraft_t* current = list->head;
    int found = 0;

    //goes thru list and checks to see if the motor type entered equals a motor type in the list
    while (current != NULL) {
        if (current->propulsion == whichOne) {
            found = 1;
        }
        current = current->next;
    }
        return found;
}

//prints watercraft of the selected type
void printWatercraftByType(list_t *list, char whichOne[]) {
    watercraft_t* current = list->head;
    int i = 0;

    while (current != NULL) {
        //if type entered matches a watercraft in the list it prints it out
        if (strcmp(current->type, whichOne) == 0) {
            printf("%2d. ", i+1);
            printf("%-15s", current->type);
            printf("%-20s", current->make);
            printf("%-25s", current->model);
            printf("%-13s", current->engine);
            printf("%4dhp    ", current->hp);
            printf("%-20s", current->color);
            printf("%3dft  ", current->length);
            printf("$%10.2lf", current->total_price);
            printf("\n");
        }
        current = current->next;
        i++;
    }
    printf("\n\n");
}

//prints watercraft by the selected motor type
void printWatercraftByMotor(list_t *list, int whichOne) {
    watercraft_t* current = list->head;
    int i = 0;

    while (current != NULL) {
        //if motor entered matches a watercraft in the list it prints it out
        if (current->propulsion == whichOne) {
            printf("%2d. ", i+1);
            printf("%-15s", current->type);
            printf("%-20s", current->make);
            printf("%-25s", current->model);
            printf("%-13s", current->engine);
            printf("%4dhp    ", current->hp);
            printf("%-20s", current->color);
            printf("%3dft  ", current->length);
            printf("$%10.2lf", current->total_price);
            printf("\n");
        }
        current = current->next;
        i++;
    }
    printf("\n\n");
}

//searches list for watercraft type and prints it out
void searchByType(list_t *list) {
    int type;
    int found;

    if (isEmpty(list) == 1) {
        printf("The list is empty\n\n\n");
    }
    else {
        printf("Type of watercraft to search for:\n");
        printf(" 1. pontoon\n");
        printf(" 2. fishing\n");
        printf(" 3. sport boat\n");
        printf(" 4. kayak\n");
        printf(" 5. canoe\n");
        printf(" 6. sailboat\n\n");

        printf("- - > ");
        scanf("%d", &type);
        printf("\n\n\n");

        //each type of watercraft has a switch statement case
        switch(type) {
            case 1:
                //finds if the type is in inventory
                found = typeInInventory(list, "pontoon");

                if (found == 1) {
                    //if it is it prints the type out
                    printWatercraftByType(list, "pontoon");
                }
                else {
                    printf("Type not found\n\n");
                }
                break;
            case 2:
                found = typeInInventory(list, "fishing");
                if (found == 1) {
                    printWatercraftByType(list, "fishing");
                }
                else {
                    printf("Type not found\n\n");
                }
                break;
            case 3:
                found = typeInInventory(list, "sport boat");
                if (found == 1) {
                    printWatercraftByType(list, "sport boat");
                }
                else {
                    printf("Type not found\n\n");
                }
                break;
            case 4:
                found = typeInInventory(list, "kayak");
                if (found == 1) {
                    printWatercraftByType(list, "kayak");
                }
                else {
                    printf("Type not found\n\n");
                }
                break;
            case 5:
                found = typeInInventory(list, "canoe");
                if (found == 1) {
                    printWatercraftByType(list, "canoe");
                }
                else {
                    printf("Type not found\n\n");
                }
                break;
            case 6:
                found = typeInInventory(list, "sailboat");
                if (found == 1) {
                    printWatercraftByType(list, "sailboat");
                }
                else {
                    printf("Type not found\n\n");
                }
                break;
            default:
                printf("That is not a valid type\n\n");
                break;
        }
    }
} 

//searches list for watercraft motor type and prints it out
void searchByMotorType(list_t *list) {
    int type;
    int found;

    if (isEmpty(list) == 1) {
        printf("The list is empty\n\n\n");
    }
    else {
        printf("Type of watercraft to search for:\n");
        printf(" 1. no motor\n");
        printf(" 2. out-board\n");
        printf(" 3. in-board\n\n");

        printf("- - > ");
        scanf("%d", &type);
        printf("\n\n\n");

        switch(type) {
            case 1:
                found = motorInInventory(list, 0);
                if (found == 1) {
                    printWatercraftByMotor(list, 0);
                }
                else {
                    printf("Motor type not found\n\n");
                }
                break;
            case 2:
                found = motorInInventory(list, 1);
                if (found == 1) {
                    printWatercraftByMotor(list, 1);
                }
                else {
                    printf("Motor type not found\n\n");
                }
                break;
            case 3:
                found = motorInInventory(list, 2);
                if (found == 1) {
                    printWatercraftByMotor(list, 2);
                }
                else {
                    printf("Motor type not found\n\n");
                }
                break;
            default:
                printf("That is not a valid motor type\n\n");
                break;
        }
    }
} 

//prints the list sorted by price least to greatest
//but doesnt change the original list
void printByPrice(list_t *list) {
    list_t* sorted = newList(); //makes new list that will be sorted
    watercraft_t* currentList = list->head; //creates node to traverse list

    double pos[list->size]; //creates array to store all the total prices
    double temp;
    int i = 0;
    int j = 0;

    while (currentList != NULL) { //inserts prices from list into array
        pos[i] = currentList->total_price;
        currentList = currentList->next;
        i++;
    }

    for (i = 0 ; i < list->size - 1; i++) { //this is a bubble sort to sort array
        for (j = 0 ; j < list->size - i - 1; j++) {
            if (pos[j] < pos[j+1]) {
                temp = pos[j];
                pos[j] = pos[j+1];
                pos[j+1] = temp;
            }
        }
    }
    
    //makes nodes for the size of the list
    for (int i = 0; i < list->size; i++) { 
        watercraft_t* newSortNode = (watercraft_t*)malloc(sizeof(watercraft_t)); 
        //makes new node each iteration for the new sorted list
        currentList = list->head;
        //current list traverses the original list
        for (j = 0; j < list->size; j++) {
            //if the position in the array is equal to the current 
            //list it copies everything over to sorted list
            if (pos[i] == currentList->total_price) { 
                strcpy(newSortNode->type, currentList->type);
                strcpy(newSortNode->make, currentList->make);
                strcpy(newSortNode->model, currentList->model);
                strcpy(newSortNode->engine, currentList->engine);
                strcpy(newSortNode->color, currentList->color);
                newSortNode->hp = currentList->hp;
                newSortNode->length = currentList->length;
                newSortNode->total_price = currentList->total_price;
            }
            currentList = currentList->next;
        }
        //this adds the new node to the sorted linked list
        if (isEmpty(sorted) == 1) {
            newSortNode->next = NULL;
            sorted->head = newSortNode;
            sorted->tail = newSortNode; 
        }
        else {
            newSortNode->next = sorted->head;
            sorted->head = newSortNode;
        }
        //then increments the sorted list size
        sorted->size++;
    }
    printList(sorted);
    freeMem(sorted);
}

//checks to see if the list is empty
int isEmpty(list_t *list) {
    if (list->head == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

//this goes through the list and totals all the watercraft prices and prints it
void TAV(list_t *list) {
    watercraft_t* current = list->head;
    int i = 0;
    double sum = 0;
        while (current != NULL) {
            sum += current->total_price;
            i++;
            current = current->next;
        }

    printf("Total asset value of all inventory is: $% .2lf\n\n\n", sum);
}

//this frees the memory of the list that is put in
void freeMem( list_t *list) {
    watercraft_t *current = list->head;
    watercraft_t *prev;

    //until end of list it frees memory of current node
    while (current != NULL) {
        prev = current;
        current = current->next;
        free(prev);
    }
    free(list);
}