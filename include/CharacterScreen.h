/* 
 * File:   CharacterScreen.h
 * Author: Cow
 *
 * Created on April 17, 2013, 3:32 PM
 */

#ifndef CHARACTERSCREEN_H
#define	CHARACTERSCREEN_H

#include <Frame.h>
#include <Virtuals.h>
#include <Button.h>
#include <Text.h>
#include <string>
#include <Unit.h>

using namespace std;

class CharacterScreen : public Frame, public EventHandler, public Renderable{
public:
    //constructor
    CharacterScreen();
    ~CharacterScreen();
    //manips
    //access
    //Frame
    void bind();
    void release();
    //Events
    bool onEvent(SDL_Event* evt);
    //Render
    void onRender(SDL_Surface* surf);
private:
    Button *strFocus, *dexFocus, *magFocus, *go;
    Line *strLn, *dexLn, *magLn, *goLn;
    Line* name, *unitclass;
    string workingName;
    Unit* playerUnit;
};

#endif	/* CHARACTERSCREEN_H */

