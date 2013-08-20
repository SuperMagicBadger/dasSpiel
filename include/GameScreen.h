/* 
 * File:   GameScreen.h
 * Author: Cow
 *
 * Created on April 17, 2013, 3:31 PM
 */

#ifndef GAMESCREEN_H
#define	GAMESCREEN_H

#include <Frame.h>
#include <Virtuals.h>
#include <Sprites.h>
#include <Level.h>
#include <UnitController.h>
#include <Text.h>

class GameScreen : public Frame, public Renderable, public EventHandler, public Updateable{
public:
    //constructor
    GameScreen();
    ~GameScreen();
    //manips
    Level* setLevel(Level* l);
    void bindLevel();
    //frame
    void bind();
    void release();
    //renderable
    void onRender(SDL_Surface* surf);
    //event handler
    bool onEvent(SDL_Event* evt);
    //updater
    void onUpdate(int miliD);
    //controll
    void init();
    void addPlayer(Unit* u);
    void addUnit(Unit* u);
private:
    void update();
    //level data
    Level* l;
    //unit lists
    int playerindex;
    PlayerController* player;
    vector<AIController*> monsters;
    //update timer
    int timeStart, timeNext;
    //player text
    Line* name;
    Line* HP;
    Line* plevel;
    Line* stats;
    
};

#endif	/* GAMESCREEN_H */

