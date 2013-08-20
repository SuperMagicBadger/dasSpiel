#include <GameScreen.h>
#include <Spinner.h>
#include <iostream>
#include <string>
#define TIME_STEP 500;

using namespace std;

//constructor
GameScreen::GameScreen() {
    timeStart = -1;
    timeNext = -1;
    l = NULL;
    name = HP = plevel = stats;
}
GameScreen::~GameScreen() {
    delete player;
}
//manips
Level* GameScreen::setLevel(Level* _l) {
    Level* ret = l;
    if (l != NULL) {
        l->setRenderableRemove();
    }
    l = _l;
    l->setPosition(0, 0);
    l->setDims(800, 500);
    addRenderableChild(l);
    return ret;
}
void GameScreen::bindLevel(){
    l->clearUnits(false);
    for(int i = 0; i < monsters.size(); i++){
        delete monsters[i];
    }
    monsters.clear();
    
    int i = 0;
    Unit* u = l->getUnit(i);
    while(u != NULL){
        monsters.push_back(new AIController(u, l));
        i++;
        u = l->getUnit(i);
    }
    
    if(player != NULL) {
        l->centerOnGrid(player->getUnit()->getGridX(),player->getUnit()->getGridY());
    }
}
//frame
void GameScreen::bind() {
    eh_remove = ren_remove = up_remove = false;
    Spin::getSingleton()->addRenderable(this);
    Spin::getSingleton()->addEventable(this);
    Spin::getSingleton()->addLogicable(this);
}
void GameScreen::release() {
    setRenderableRemove();
    setEventRemove();
    setUpdateRemove();
}
//renderable
void GameScreen::onRender(SDL_Surface* surf) {
    SDL_Rect r = {surf->w - 200, 0, 200, surf->h};
    SDL_FillRect(surf, &(surf->clip_rect), SDL_MapRGB(surf->format, 0, 0, 0));
    SDL_FillRect(surf, &r, SDL_MapRGB(surf->format, 0, 0, 0));

    l->setDims(surf->w - 200, surf->h);

    if (name != NULL) {
        int x = surf->w - 100 - name->getW() / 2;
        name->setPosition(x, 10);
    }
    if (HP != NULL) {
        char buff[3];
        string h = "HP: ";
        h.append(itoa(player->getUnit()->getHealth(), buff, 10));
        HP->setMessage(h);
        int x = surf->w - 100 - HP->getW() / 2;
        HP->setPosition(x, 50);
    }
    passRender(surf);
}
//eventable
bool GameScreen::onEvent(SDL_Event* evt) {
    if (player != NULL && !player->onEvent(evt)) {
        player->doTurn();
        update();
        return KILL_EVENT;
    }
    if (evt->type == SDL_KEYDOWN) {
        switch (evt->key.keysym.sym) {
            case SDLK_i:
                release();
                FrameManager::getSingleton()->bind("inventory_screen");
            case SDLK_w:
                l->scroll(0, -1);
                break;
            case SDLK_a:
                l->scroll(-1, 0);
                break;
            case SDLK_s:
                l->scroll(0, 1);
                break;
            case SDLK_d:
                l->scroll(1, 0);
                break;
        }
    }
    return true;
}
//updateable
void GameScreen::onUpdate(int miliD) {
    timeStart = SDL_GetTicks();
    if (timeStart >= timeNext || timeNext == -1) {
        player->doTurn();
        update();
    }
}
void GameScreen::update() {
    timeNext = timeStart + TIME_STEP;
    while (!player->getUnit()->activeTurn()) {
        int i = 0;
        while (i < monsters.size()) {
            monsters[i]->setTarget(player->getUnit(), 0);
            if (!monsters[i]->tick()) {
                l->remUnit(monsters[i]->getUnit());
                delete monsters[i];
                monsters.erase(monsters.begin() + i);
                continue;
            }
            i++;
        }
        if (!player->tick()) {
            l->remUnit(player->getUnit());
            if (!up_remove) {
                release();
                FrameManager::getSingleton()->bind("main_menu");
            }
            break;
        }
    }
}
//control
void GameScreen::addPlayer(Unit* u) {
    u->setFaction(2);
    player = new PlayerController(u, l);
    l->setPlayer(u);
    l->centerOnGrid(u->getGridX(), u->getGridY());

    TTF_Font* f = FontFactory::getSingleton()->getFont("font", 24);
    SDL_Color fg
    {
        255, 255, 255
    };
    SDL_Color bg
    {
        0, 0, 0
    };

    char buff[3];

    name = new Line(u->getName(), f, Line::solid, fg, bg);
    string h = "HP: ";
    h.append(itoa(u->getHealth(), buff, 10));
    HP = new Line(h, f, Line::solid, fg, bg);

    addRenderableChild(name);
    addRenderableChild(HP);
}
void GameScreen::addUnit(Unit* u) {
    u->setFaction(20);
    AIController* ai = new AIController(u, l);
    monsters.push_back(ai);
    l->addUnit(u);
}
void GameScreen::init() {
    Level* lev = new Level("levelOne");
    setLevel(lev);
    bindLevel();
}