/* 
 * File:   main.cpp
 * Author: Cow
 *
 * Created on April 17, 2013, 3:14 PM
 */

#include <windows.h>
#include <Spinner.h>

#include <MainMenu.h>
#include <GameScreen.h>
#include <Unit.h>
#include <Text.h>

#include "CharacterScreen.h"
#include "ItemScreen.h"

using namespace std;
/*
 * 
 */
#ifdef __cplusplus
extern "C" {
#endif
#if __WIN32__
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        Spin* s = Spin::getSingleton();
        
        if(s->init()) {
            SDL_WM_SetCaption("Das Spiel", "asshat");

            //load fonts
            FontFactory::getSingleton()->loadFont("font", 24);


            //load sprites
            SpriteFactory* f = SpriteFactory::getSingleton();
            f->loadSheet("SpritePackage");

            //load items
            ItemFactory* ifact = ItemFactory::getSingleton();
            ifact->loadFile("ItemPackage");
            
            //load unit prototypes
            UnitFactory* uf = UnitFactory::getSingleton();
            uf->loadSheet("Warrior");
            uf->loadSheet("Rogue");
            uf->loadSheet("Kobold");
            
            //load frames
            FrameManager* fm = FrameManager::getSingleton();
            MainMenu* mainMenu = new MainMenu();
            GameScreen* gamescr = new GameScreen();
            CharacterScreen* charscr = new CharacterScreen();
            InventoryScreen* invscr = new InventoryScreen();
            

            fm->addFrame("main_menu", mainMenu);
            fm->addFrame("game_screen", gamescr);
            fm->addFrame("char_screen", charscr);
            fm->addFrame("inventory_screen", invscr);
            mainMenu->bind();
            s->go();
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

