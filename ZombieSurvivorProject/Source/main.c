// ZombieSurvivorProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_SURVIVORS   4

typedef struct
{
    uint8_t name[30];
    uint8_t wounds;
    bool isTurn;
    bool isAlive;
    bool isPlayerSlotAvailable;
    uint8_t actionCounter; 
}survivor_attributes_t;

typedef struct 
{
    uint8_t index; // Determines whose turn
    uint8_t count; // Total players alive or dead
    survivor_attributes_t *survivorBuffer[MAX_SURVIVORS];
}survivor_turn_manager_t; 

survivor_turn_manager_t survivorQueue; 

// Names
uint8_t name_spongebob[] = "Spongebob";
uint8_t name_patrick[] = "Patrick";

//Prototypes
void init(void);
void CreateNewSurvivor(survivor_attributes_t *newSurvivor, uint8_t* name);
void AddSurvivorToGame(survivor_attributes_t *newSurvivor); 
uint8_t IncrementSurvivorIndex(void); 
void SurvivorAction(survivor_attributes_t* survivor);

void DoAction(survivor_attributes_t* survivor);
void EndTurn(survivor_attributes_t* survivor);

void PrintQueue(void);
 

int main()
{
    init(); 
}

void init(void)
{
    for (int i = 0; i < 4; i++)
    {
        strcpy(survivorQueue.survivorBuffer[i]->name, "*");
        survivorQueue.survivorBuffer[i]->wounds = 0;
        survivorQueue.survivorBuffer[i]->isAlive = false;
        survivorQueue.survivorBuffer[i]->isTurn = false;
        survivorQueue.survivorBuffer[i]->isPlayerSlotAvailable = true; 
        survivorQueue.survivorBuffer[i]->actionCounter = 0; 
    }
    survivorQueue.index = 0; 
    survivorQueue.count = 0; 
    CreateSurvivor(name_spongebob); 
}
void CreateNewSurvivor(survivor_attributes_t *newSurvivor, uint8_t *name)
{
    survivor_attributes_t newSurvivor;
    strcpy_s(newSurvivor->name, sizeof(newSurvivor->name), name);
    newSurvivor->wounds = 0;
    newSurvivor->isAlive = true;
    newSurvivor->isTurn = true;
    newSurvivor->isPlayerSlotAvailable = false; 
    newSurvivor->actionCounter = 3; 
    printf("%s wounds = %u\r\n", newSurvivor->name, newSurvivor->wounds);

    AddSurvivorToGame(newSurvivor);

}
void AddSurvivorToGame(survivor_attributes_t *newSurvivor)
{
    // Check for buffer overflow and don't overwrite existing players
    if((survivorQueue.count < 4) && (survivorQueue.survivorBuffer[survivorQueue.count]->isPlayerSlotAvailable))
    {
        survivorQueue.survivorBuffer[survivorQueue.count] = newSurvivor;
        survivorQueue.count++; 
    }
}

void SurvivorAction(survivor_attributes_t* survivor)
{
    if (survivor->actionCounter != 0)
    {
        survivor->actionCounter--;
        printf("%s did an action\r\n", survivor->name);
    }
}

void DoAction(survivor_attributes_t* survivor)
{
    SurvivorAction(survivor);
}

void EndTurn(survivor_attributes_t* survivor)
{
    if (survivor->isTurn == true)
    {
        survivor->isTurn = false;
        printf("%s ended their turn\r\n", survivor->name);   
    }
}

uint8_t IncrementSurvivorIndex(void)
{
    if(survivorQueue.index == 3)
    {
        survivorQueue.index = 0; 
    }
    else
    {
        survivorQueue.index++; 
    }
    return survivorQueue.index; 
}
void PrintQueue(void)
{
    printf("Position 0 name = %s\r\n", survivorQueue.survivorBuffer[0]->name);
    printf("Position 0 alive = %u\r\n", survivorQueue.survivorBuffer[0]->isAlive);

    printf("Position 1 name = %s\r\n", survivorQueue.survivorBuffer[1]->name);
    printf("Position 1 alive = %u\r\n", survivorQueue.survivorBuffer[1]->isAlive);

    printf("Position 2 name = %s\r\n", survivorQueue.survivorBuffer[2]->name);
    printf("Position 2 alive = %u\r\n", survivorQueue.survivorBuffer[2]->isAlive);

    printf("Position 3 name = %s\r\n", survivorQueue.survivorBuffer[3]->name);
    printf("Position 3 alive = %u\r\n", survivorQueue.survivorBuffer[3]->isAlive);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
