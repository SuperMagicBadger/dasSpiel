
#include <CharacterScreen.h>
#include <Spinner.h>

#include "GameScreen.h"
class waraction : public ButtonAction {
public:
    waraction(Unit* playerUnit, Line* cname) {
        u = playerUnit;
        l = cname;
    }
    void onPress() {
        u->setStats(15, 5, 0);
        u->setMaxHealth(10);
        u->setHealth(10);
        l->setMessage("Class: Warrior");
        u->setSprite(SpriteFactory::getSingleton()->createSprite("DasSprite", "Warrior"));
    }
private:
    Unit* u;
    Line* l;
};
class rogaction : public ButtonAction {
public:
    rogaction(Unit* playerUnit, Line* cname) {
        u = playerUnit;
        l = cname;
    }
    void onPress() {
        u->setStats(5, 15, 0);
        u->setMaxHealth(10);
        u->setHealth(10);
        l->setMessage("Class: Rogue");
        u->setSprite(SpriteFactory::getSingleton()->createSprite("DasSprite", "Zubin"));
    }
private:
    Unit* u;
    Line* l;
};
class magaction : public ButtonAction {
public:
    magaction(Unit* playerUnit, Line* cname) {
        u = playerUnit;
        l = cname;
    }
    void onPress() {
        u->setStats(0, 5, 15);
        u->setMaxHealth(8);
        u->setHealth(8);
        l->setMessage("Class: Mage");
        u->setSprite(SpriteFactory::getSingleton()->createSprite("DasSprite", "Knight"));     
        cout << "yo\n";
    }
private:
    Unit* u;
    Line* l;
};
class startaction : public ButtonAction {
public:
    startaction(Unit* player) {
        u = player;
    }
    void onPress() {
        ((GameScreen*) (FrameManager::getSingleton()->getFrame("game_screen")))->init();
        ((GameScreen*) (FrameManager::getSingleton()->getFrame("game_screen")))->addPlayer(u);
        FrameManager::getSingleton()->release("char_screen");
        FrameManager::getSingleton()->bind("game_screen");
    }
private:
    Unit* u;
};

//character screen-----------------------------------------
//constructors---------------
CharacterScreen::CharacterScreen() {
    playerUnit = new Unit();
    playerUnit->setStats(15, 5, 0);
    playerUnit->setSprite(SpriteFactory::getSingleton()->createSprite("DasSprite", "Warrior"));


    //set button sprites
    strFocus = new Button(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_standard"));
    dexFocus = new Button(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_standard"));
    magFocus = new Button(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_standard"));
    go = new Button(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_standard"));


    strFocus->setHover(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_highlight"));
    dexFocus->setHover(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_highlight"));
    magFocus->setHover(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_highlight"));
    go->setHover(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_highlight"));

    strFocus->setPress(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_down"));
    dexFocus->setPress(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_down"));
    magFocus->setPress(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_down"));
    go->setPress(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_down"));

    strFocus->setDisable(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_disable"));
    dexFocus->setDisable(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_disable"));
    magFocus->setDisable(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_disable"));
    go->setDisable(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_disable"));

    //set button text
    TTF_Font* ft = FontFactory::getSingleton()->getFont("font", 24);
    SDL_Color fg
    {
        255, 255, 255
    };
    SDL_Color bg
    {
        0, 0, 0
    };

    strLn = new Line("Warrior", ft, Line::solid, fg, bg);
    dexLn = new Line("Rogue", ft, Line::solid, fg, bg);
    magLn = new Line("Mage", ft, Line::solid, fg, bg);
    goLn = new Line("Go!", ft, Line::solid, fg, bg);

    //set the player name text
    workingName = "Name: Guy";
    name = new Line(workingName, ft, Line::solid, bg, fg);
    unitclass = new Line("Class: Warrior", ft, Line::solid, bg, fg);
    playerUnit->setName(workingName.substr(6, workingName.size()));

    //set button action
    strFocus->setActionHandler(new waraction(playerUnit, unitclass));
    dexFocus->setActionHandler(new rogaction(playerUnit, unitclass));
    magFocus->setActionHandler(new magaction(playerUnit, unitclass));
    go->setActionHandler(new startaction(playerUnit));

    //set positions
    name->setPosition(50, 50);
    unitclass->setPosition(50, name->getY() + name->getH() + 30);
    strFocus->setPosition(0, name->getY() + name->getH() + 30);
    dexFocus->setPosition(0, strFocus->getY() + strFocus->getH() + 30);
    magFocus->setPosition(0, dexFocus->getY() + dexFocus->getH() + 30);
    strLn->setPosition(strFocus->getX() + 20, strFocus->getY() + 10);
    dexLn->setPosition(dexFocus->getX() + 20, dexFocus->getY() + 10);
    magLn->setPosition(magFocus->getX() + 20, magFocus->getY() + 10);


    //add children
    addRenderableChild(name);
    addRenderableChild(unitclass);
    addRenderableChild(strFocus);
    addRenderableChild(dexFocus);
    addRenderableChild(magFocus);
    addRenderableChild(go);
    addRenderableChild(strLn);
    addRenderableChild(dexLn);
    addRenderableChild(magLn);
    addRenderableChild(goLn);

    addEventChild(strFocus);
    addEventChild(dexFocus);
    addEventChild(magFocus);
    addEventChild(go);
}
CharacterScreen::~CharacterScreen() { }
//manips---------------------
//access---------------------
//Frame----------------------
void CharacterScreen::bind() {
    eh_remove = ren_remove = false;
    Spin::getSingleton()->addRenderable(this);
    Spin::getSingleton()->addEventable(this);
    SDL_EnableUNICODE(SDL_ENABLE);
}
void CharacterScreen::release() {
    setRenderableRemove();
    setEventRemove();
    SDL_EnableUNICODE(SDL_DISABLE);
}
//Events---------------------
bool CharacterScreen::onEvent(SDL_Event* evt) {
    if (evt->type == SDL_KEYDOWN) {
        if (evt->key.keysym.sym == SDLK_BACKSPACE) {
            if (workingName.size() > 6) {
                workingName.erase(workingName.end() - 1);
            }
        } else {
            char c = evt->key.keysym.unicode;
            workingName += c;
        }
        name->setMessage(workingName);
        playerUnit->setName(workingName.substr(6, workingName.size()));
    }
    passEvent(evt);
}
//Render---------------------
void CharacterScreen::onRender(SDL_Surface* surf) {
    SDL_FillRect(surf, &surf->clip_rect, SDL_MapRGB(surf->format, 255, 255, 255));
    strFocus->setPosition(surf->w - strFocus->getW() - 30, name->getY() + name->getH() + 30);
    dexFocus->setPosition(surf->w - dexFocus->getW() - 30, strFocus->getY() + strFocus->getH() + 30);
    magFocus->setPosition(surf->w - magFocus->getW() - 30, dexFocus->getY() + dexFocus->getH() + 30);
    go->setPosition(surf->w - go->getW() - 30, magFocus->getY() + magFocus->getH() + 30);
    strLn->setPosition(strFocus->getX() + 20, strFocus->getY() + 10);
    dexLn->setPosition(dexFocus->getX() + 20, dexFocus->getY() + 10);
    magLn->setPosition(magFocus->getX() + 20, magFocus->getY() + 10);
    goLn->setPosition(go->getX() + 20, go->getY() + 10);

    passRender(surf);
}
//character screen=========================================
