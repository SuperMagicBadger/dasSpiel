/* 
 * File:   ItemScreen.h
 * Author: Cow
 *
 * Created on April 17, 2013, 3:31 PM
 */

#ifndef ITEMSCREEN_H
#define	ITEMSCREEN_H

#include <Sprites.h>
#include <Button.h>
#include <Text.h>
#include <Frame.h>
#include <Virtuals.h>

class InventoryScreen : public Frame, public Renderable, public EventHandler{
public:
    //constructors
    InventoryScreen();
    ~InventoryScreen();
    //Frame
    void bind();
    void release();
    //Renderable
    void onRender(SDL_Surface* surf);
    //EventHandler
    bool onEvent(SDL_Event* evt);
private:
    Button* wepTab, *armTab;
    Line* wepLine,* armLine;
};


#endif	/* ITEMSCREEN_H */

