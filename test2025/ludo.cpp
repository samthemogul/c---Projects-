// ludo.h - Header file
#ifndef LUDO_H
#define LUDO_H

#include <iostream>
#include <string>
using namespace std;

// Enum for house colors
enum Colour { RED, YELLOW, GREEN, BLUE };

// Structure for House
struct House {
    Colour color;
    int members;
    bool assigned;
    
    House(Colour c = RED, int m = 4, bool a = false) : color(c), members(m), assigned(a) {}
};

// Structure for Player
struct Player {
    string name;
    House house;
};

void assignHouses(Player players[], int numPlayers);
void displayResults(Player players[], int numPlayers);
void updateMembers(Player players[], int numPlayers);

#endif

// ludo.cpp - Implementation file
// #include "ludo.h"

void assignHouses(Player players[], int numPlayers) {
    Colour availableHouses[] = {RED, YELLOW, GREEN, BLUE};
    bool houseAssigned[4] = {false};
    
    for (int i = 0; i < numPlayers; ++i) {
        cout << "Enter name for player " << (i + 1) << ": ";
        cin >> players[i].name;
        
        char colorChoice;
        cout << "Choose house for " << players[i].name << " (R/Y/G/B): ";
        cin >> colorChoice;
        
        Colour chosenColor;
        switch (toupper(colorChoice)) {
            case 'R': chosenColor = RED; break;
            case 'Y': chosenColor = YELLOW; break;
            case 'G': chosenColor = GREEN; break;
            case 'B': chosenColor = BLUE; break;
            default: cout << "Invalid choice, assigning default (RED)." << endl; chosenColor = RED;
        }
        
        if (!houseAssigned[chosenColor]) {
            players[i].house = House(chosenColor, 4, true);
            houseAssigned[chosenColor] = true;
        } else {
            cout << "House already assigned. Assigning another available house." << endl;
            for (int j = 0; j < 4; ++j) {
                if (!houseAssigned[j]) {
                    players[i].house = House(static_cast<Colour>(j), 4, true);
                    houseAssigned[j] = true;
                    break;
                }
            }
        }
    }
}

void displayResults(Player players[], int numPlayers) {
    cout << "\nGame Configuration:" << endl;
    cout << "----------------------------------" << endl;
    cout << "Name\tHouse\tMembers" << endl;
    cout << "----------------------------------" << endl;
    for (int i = 0; i < numPlayers; ++i) {
        string colorStr;
        switch (players[i].house.color) {
            case RED: colorStr = "Red"; break;
            case YELLOW: colorStr = "Yellow"; break;
            case GREEN: colorStr = "Green"; break;
            case BLUE: colorStr = "Blue"; break;
        }
        cout << players[i].name << "\t" << colorStr << "\t" << players[i].house.members << endl;
    }
}

void updateMembers(Player players[], int numPlayers) {
    for (int i = 0; i < numPlayers; ++i) {
        players[i].house.members -= (i + 1);
    }
    cout << "\nUpdated Members after deduction:" << endl;
    displayResults(players, numPlayers);
}

// main.cpp - Main file
// #include "ludo.h"

int main() {
    int numPlayers;
    cout << "Enter number of players (2 or 4): ";
    cin >> numPlayers;
    if (numPlayers != 2 && numPlayers != 4) {
        cout << "Invalid number of players. Defaulting to 2." << endl;
        numPlayers = 2;
    }
    
    Player players[numPlayers];
    assignHouses(players, numPlayers);
    displayResults(players, numPlayers);
    updateMembers(players, numPlayers);
    
    return 0;
}
