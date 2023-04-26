//
//  main.c
//  Oregon Trail Game
//
//  Created by Caleb Ke-A on 4/3/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//to make something harder to get make it a certain number if easier use modulo = 1 or 0 or just choose a lot of numbers

void WeatherUDF(void);
void SuppliesUDF(int* waterPtr, int* foodPtr); //- every two days (modulo) easier
int BanditsUDF(void); //- they come day 5 medium
char NextDayUDF(int day);
void GoodPersonUDF(int *waterPtr, int *foodPtr);
void DeathUDF(void); //day 3 or 9 roll a certain number 8
int DiseaseUDF(int* counterPointer); //- day 3 or 9 roll a certain number 4/10 roll for a number to see chance of suevival 3/5(Death)
void StateMenuUDF(char *statePtr[11]); //Add a menu to choose between going to California or to Oregon
//EquipmentDamageUDF- day 4, 6 medium
//TradingUDF- 2, 6, 7, 9 medium
//FaithUDF- every day choice y/n gives easier chance of somethings happening (Pray)
//TurnsUDF - (wrong or right turns) random hard
char WinnerUDF(char charName[10]); //- (made it to oregon) last day
//make a "Miles to Oregon" counter- start at 150 decrease by 15 every day- FINISHED


int main(void) {
    
    char charName[10];
    char state[12];
    int i;
    int water = 4, food = 8;
    int waterPtr = 0, foodPtr = 0;
    int banditDay = 5, stolenSuplies;
    int milesUntil = 135;
    char restart = 'y';
    int deathChance;
    int diseaseChance;
    int diseaseCounter;
    int diseaseDeath = 0;
    
    srand(time(0));
    
    do{
        water = 4;
        food = 8;
        milesUntil = 135;
        diseaseCounter = 100;
    //Start
        printf("Hello!\n Enter your character name:\n");
        scanf("%s", charName);
        
        printf("\nWelcome %s!\n", charName);
        
    //Choose between going to Oregon or Cali
        StateMenuUDF(&state[0]);
        printf("%s", state);
        
        
        banditDay = (rand() % 8) + 3; //10
        
        for(i = 1; i < 11; i++){
            
            --water;
            food = food - 2;
            
            
            printf("\nDay %d\n", i);
            printf("Miles to Oregon: %d\n", milesUntil);
            
        //Weather
            WeatherUDF();
            
        //Supply days
            if(i % 2 == 0){
                SuppliesUDF(&waterPtr, &foodPtr);
                
                water += waterPtr;
                food += foodPtr;
            }
        //Stops water from being negative
            if(water < 0){
                water = 0;
            }
        //Stops food from being negative
            if(food < 0){
                food = 0;
            }
        //Good People are Welcome!
            if (water < 1 || food < 1){
                GoodPersonUDF(&waterPtr, &foodPtr);
                
                water += waterPtr;
                food += foodPtr;
            }
            
        //Shows how much food and Water
            printf("Water Count: %d\n", water);
            printf("Food Count: %d\n\n", food);
            
        //Bandits!
            if(i == banditDay){
                stolenSuplies = BanditsUDF();
            //Makes if food has more supplies get stolen from it and vice versa
                if(food > water){
                    printf("Bandits took %d food\n", stolenSuplies);
                    food -= stolenSuplies;
                }
                
                else{
                    printf("Bandits took %d water\n", stolenSuplies);
                    water -= stolenSuplies;
                }
            }
        //Lost (Ran out of Supplies)
            if((water <= 0) || (food <= 0)){            //Lose Case
                printf("You ran out of supplies :(\n");
                printf("You lost on Day %d\n", i);
                
                printf("\nWant to restart? y/n:");
                scanf(" %c", &restart);
                printf("\n\n\n\n\n");
                
                break;
            }
        //Death
            if(i == 3 || i == 5 || i == 9){
                deathChance = rand() % 10; //0-9
            // 8 is unlucky
                if( deathChance == 8){
                    DeathUDF();
                    
                    printf("You Died :(\n");
                    printf("You lost on Day %d\n", i);
                    
                    printf("\nWant to restart? y/n:");
                    scanf(" %c", &restart);
                    printf("\n\n\n\n\n");
                    
                    break;
                }
            }
        //Disease
            if(i==3){
                diseaseChance = rand() % 5;
                    
                if( diseaseChance == 3){
                    diseaseCounter = 4;
                }
            }
                if(diseaseCounter > -1 && diseaseCounter <= 4){
                    diseaseCounter--;
                    diseaseDeath = DiseaseUDF(&diseaseCounter);
                    
                    if (diseaseDeath == 1){
                        printf("You lost on Day %d\n", i);
                        
                        printf("\nWant to restart? y/n:");
                        scanf(" %c", &restart);
                        printf("\n\n\n\n\n");
                        
                        break;
                    }
                }
            
        //Miles until Oregon
            milesUntil = milesUntil - 15;
        //Next day
            if (i < 10){
                if(NextDayUDF(i) == 'n'){
                    break;
                }
            }
        //End Screen
            if(i == 10){
                restart = WinnerUDF(charName);
                
            }
            
            
            
        }
        
    }while ((restart == 'y')||(restart == 'Y'));
    
    return 0;
}

void StateMenuUDF(char *statePtr[11]){
    int stateSelect;
    
    printf("Choose which state you are gonna be traveling to!\n");
    printf("1. Oregon\n");
    printf("2. California\n");
    scanf("%d", &stateSelect);
    
    switch(stateSelect){
        case 1:
            *statePtr = "Oregon";
            break;
            
        case 2:
            *statePtr = "California";
            break;
    }
    
}


void WeatherUDF(void){
    int weatherType;
    
    weatherType = rand() % 6;
    weatherType++; //1-6
    
    switch(weatherType){
        case 1:
            printf("Today it is Sunny.\n\n");
            break;
            
        case 2:
            printf("Today it is Overcast.\n\n");
            break;
            
        case 3:
            printf("Today it is Raining.\n\n");
            break;
            
        case 4:
            printf("Today it is Thundering but no rain.\n\n");
            break;
            
        case 5:
            printf("Today it is Snowing.\n\n");
            break;
            
        case 6:
            printf("Today it is Windy.\n\n");
            break;
            
    }
    
}

void SuppliesUDF(int* waterPtr, int* foodPtr){
        
        
        printf("Time to Search for water!\n");
        
        *waterPtr = rand() % 6; //5
        
        if (*waterPtr == 1){
            printf("You found %d water\n", *waterPtr);
        }
        
        else{
            printf("You found %d waters\n", *waterPtr);
        }
        
        printf("Time to hunt for food!\n");
        
        *foodPtr = rand() % 6; //5
        
        if ((*foodPtr == 1) || (*foodPtr == 0)){
            printf("You found %d food \n\n", *foodPtr);
        }
        
        else{
            printf("You found %d foods\n\n", *foodPtr);
        }
        
}


int BanditsUDF(void) {
    
    int numBandits, numAliveBandits;
    int numAmmo;
    
    numBandits = rand() % 6; //5
    numAmmo = rand() % 4; //4
    
    printf("\nOH NO! %d BANDITS!\n", numBandits);
    printf("You have %d ammo so you can fight off %d bandits\n", numAmmo, numAmmo);
    
    numAliveBandits = numBandits - numAmmo;
    
    if(numAliveBandits <= 0){
        numAliveBandits = 0;
    }
    
    printf("%d bandits got away! They took %d supplies\n", numAliveBandits, numAliveBandits);
    
    return numAliveBandits;
}

char NextDayUDF(int day){
    char nextDay = 'y';
    
    printf("Do you want to continue to the next day? y/n: \n");
    scanf(" %c", &nextDay);
    
    if((nextDay == 'y')||(nextDay == 'Y')){
        return 'y';
    }
    
    else{
        printf("\nYou chose to quit on Day %d\n", day);
       
        return 'n';
    }
    
}

void GoodPersonUDF(int *waterPtr, int *foodPtr){
    // print statements for each (rand num for name and then switch statement)
    // print statements for how much food/water
    char userSelect = 'y';
    int NPCNameSelect;
    char NPCName[5];
    int i;
    
    printf("A stranger appeared. Would you like to talk to them? y/n: \n");
    scanf(" %c", &userSelect);
    
    if((userSelect == 'y') || (userSelect == 'Y')){
        
        NPCNameSelect = rand() % 4;
        NPCNameSelect++; //1-4
        
        switch(NPCNameSelect){
            case 1:
                NPCName[0] = 'J';
                NPCName[1] = 'o';
                NPCName[2] = 'h';
                NPCName[3] = 'n';
                NPCName[4] = '\0';
                
                break;
                
            case 2:
                NPCName[0] = 'J';
                NPCName[1] = 'i';
                NPCName[2] = 'm';
                NPCName[3] = '\0';
                break;
                
            case 3:
                NPCName[0] = 'S';
                NPCName[1] = 'a';
                NPCName[2] = 'l';
                NPCName[3] = 'l';
                NPCName[4] = 'y';
                break;
                
            case 4:
                NPCName[0] = 'M';
                NPCName[1] = 'a';
                NPCName[2] = 'r';
                NPCName[3] = 'r';
                NPCName[4] = 'y';
                break;
                
            default:
                
                break;
                
        }
        
        printf("Hi my name is ");
        
        for(i=0; i < strlen(NPCName); i++){
            printf("%c", NPCName[i]);
        }
        
        printf("! Looks like you are a little low on supplies. Let me see if I have any to spare.\n");
        
        *foodPtr = rand() % 6;
        
        *waterPtr = rand() % 6;
        
        printf("Well lucky you I happen to have %d water and %d food to spare!\n", *waterPtr, *foodPtr);
        printf("Hope this helps you on your journey to Oregon!\n\n");
    }
   
}

void DeathUDF(void){
    //make death scenes ahhhhh
    int deathScene;
    
    deathScene = rand() % 4;
    deathScene++; //1-4
    
    switch(deathScene){
        case 1:
            printf("Fred, one of your Oxen, got spooked! You lost control and fell off a cliff!\n");
            break;
            
        case 2:
            printf("A storm appeared and you weren't prepared! You drowned in the floods!\n");
            break;
            
        case 3:
            printf("You wandered onto tribal lands and the Natives hunted and killed you!\n");
            break;
            
        case 4:
            printf("You tried to befriend a rattlesnake. We all know you died because of that one...\n");
            break;
            
    }
}

int DiseaseUDF(int* counterPointer){
    int deathChance;
    int nameRoll; //Used to decide what disease name is to be used
    char diseaseName[25];
    int death = 0;
    
    if(*counterPointer == 3){
    nameRoll = rand() % 3;
    nameRoll++; //1-3
    
        switch(nameRoll){
            case 1:
                strcpy(diseaseName, "Disentary");
                
                break;
                
            case 2:
                strcpy(diseaseName, "Small Pox");
                
                break;
                
            case 3:
                strcpy(diseaseName, "Influenza");
                
                break;
        }
    
        printf("You caught %s. Hopefully you survive\n", diseaseName);
}
    
    deathChance = rand() % 8;
    if(deathChance == 3){
        printf("You Died to your disease.");
        death = 1;
        
        return death;
    }
    
    if(deathChance != 8 && *counterPointer != 0){
        printf("Starting to feel better.\n");
    }
    
    if(*counterPointer == 0){
        printf("You found a doctor and made a full recovery from your disease! You're cured!\n");
    }
    return death;
    
}

char WinnerUDF(char charName[10]){
    char restart = 'y';
    
    printf("\nCongraulations %s you survived the Oregon Trail by making it to Oregon!\n", charName);
    printf("Want to test your luck again? y/n: ");
    scanf(" %c", &restart);
    printf("\n\n\n\n\n");
    
    if((restart == 'y')||(restart == 'Y')){
        return 'y';
    }
    
    else{
        printf("\nYou chose to quit. Thanks for playing!\n");
        
        return 'n';
    }
    //Try again? return answer to main
}
   
   
