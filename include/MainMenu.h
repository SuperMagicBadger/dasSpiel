/* 
 * File:   MainMenu.h
 * Author: Cow
 *
 * Created on April 17, 2013, 3:31 PM
 */

#ifndef MAINMENU_H
#define	MAINMENU_H

#include <Frame.h>
#include <Button.h>
#include <Virtuals.h>
#include <Sprites.h>
#include <Text.h>

class MainMenu : public Frame, public Renderable, public EventHandler {
public:
    //constructors
    MainMenu();
    ~MainMenu();
    //frame
    void bind();
    void release();
    //renderable
    void onRender(SDL_Surface* surf);
    //event handler
    bool onEvent(SDL_Event* evt);
private:
    Sprite* title;
    Button* newgame;
    Line* ngText;
    Button* loadgame;
    Line* lgText;
};

#endif	/* MAINMENU_H */

