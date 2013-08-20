/* 
 * File:   UnitController.h
 * Author: Cow
 *
 * Created on April 23, 2013, 4:37 PM
 */

#ifndef UNITCONTROLLER_H
#define	UNITCONTROLLER_H

#include <Unit.h>
#include <Level.h>
#include <Virtuals.h>
#include <iostream>
using namespace std;

class UnitController;
class PlayerController;
class AIController;

class UnitController {
public:
    virtual bool tick() = 0;
    virtual Unit* getUnit() = 0;
};

class PlayerController : public UnitController, public EventHandler {
public:
    //constructor
    PlayerController(Unit* player, Level* level);
    ~PlayerController();
    //access
    Unit* getUnit();
    //control
    void doTurn();
    //UC
    bool tick();
    //events
    bool onEvent(SDL_Event* evt);
private:
    Unit* player;
    Level* level;
    int moveTimeSpacer;
    int timeElapsed;
    bool up, down, left, right;
    bool done;
};

class AIController : public UnitController {
public:
    //constructor
    AIController(Unit* u, Level* l);
    ~AIController();
    //manips
    void setTarget(Unit* u, int awareness);
    //access
    Unit* getUnit();
    //events
    //UC
    bool tick();
private:
    Unit* monster;
    Unit* target;
    Level* level;
};

#endif	/* UNITCONTROLLER_H */

