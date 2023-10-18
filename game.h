#ifndef GAME_H
#define GAME_H

#include "room.h"

#include <vector>
#include <string>

using namespace std;

struct Player
{
    int x_val;
    int y_val;
    int arrows = 3;
    bool defeatWumpus = false;
    bool hasGold = false;
    bool isDead = false;
};

class Room;

class Game
{
private:
    vector<vector<Room>> cave;
    vector <int> locations;
    Player p;
    bool debugMode;
    bool leaveGame;
    int caveSize;

    bool debugInput() const;
    int sizeInput() const;
    void randomizeRooms();
    void populateCave();
    string getRoomString(int, int);
    void printCave();
    void printInstructions() const;
    void printInventory() const;
    void printPercepts();
    void move(char);
    void setPlayerCoord(char);
    void shootArrow(char);
    void noArrows();
    void checkArrow(int, int, int, int);
    bool inBounds(int, int, int, int);
    void wumpusLogic();
    void getUserInput();
    void winLosePrint() const;

public:
    Game();
    Game(vector<int>, int);
    ~Game();

    void pressEnter() const;
    int getPlayerX();
    int getPlayerY();
    bool getDefeatWumpus();
    bool getHasGold();
    int getCaveSize();
    Room getCave(int, int);
    bool getDebugSetting() const;
    vector<int> getLocations() const;
    void setLeaveGame(const bool);
    void setPlayerX(const int);
    void setPlayerY(const int);
    void setPlayerGold(const bool);
    void setPlayerDead(const bool);
    void removeGoldWumpus(string);
    void play();
    int checkContinue();
};

#endif