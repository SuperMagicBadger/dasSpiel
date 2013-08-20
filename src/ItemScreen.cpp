#include <ItemScreen.h>
#include <Spinner.h>

//helpers--------------------------------------------------
Button* genWideButton() {
    SpriteFactory* sf = SpriteFactory::getSingleton();
    Button* b;
    b = new Button(sf->getSpriteBody("inventory_screen", "rest_wide"));
    b->setPress(sf->getSpriteBody("inventory_screen", "press_wide"));
    b->setHover(sf->getSpriteBody("inventory_screen", "high_wide"));
    b->setDisable(sf->getSpriteBody("inventory_screen", "deact_wide"));
    return b;
}
Button* genThinButton() {
    SpriteFactory* sf = SpriteFactory::getSingleton();
    Button* b;
    b = new Button(sf->getSpriteBody("inventory_screen", "rest_thin"));
    b->setPress(sf->getSpriteBody("inventory_screen", "press_thin"));
    b->setHover(sf->getSpriteBody("inventory_screen", "high_thin"));
    b->setDisable(sf->getSpriteBody("inventory_screen", "deact_thin"));
    return b;
}
class ba : public ButtonAction {
public:
    ba(Button* b1, Button* b2) {
        tb = b1;
        ob = b2;
    }
    void onPress() {
        if (ob->getState() == _press) {
            ob->doClick(false);
        }
    }
    void onRelease() {
        if (ob->getState() != _press)
            ob->doClick(true);
    }
    Button* ob, *tb;
};
//helpers--------------------------------------------------
//Inventory Screen-----------------------------------------
//constructors---------------
InventoryScreen::InventoryScreen() {

    //setup tab buttons
    wepTab = genThinButton();
    armTab = genThinButton();

    wepTab->setPosition(0, 0);
    armTab->setPosition(wepTab->getW() + 50, 0);

    wepTab->setTogleable(true);
    armTab->setTogleable(true);

    wepTab->setActionHandler(new ba(wepTab, armTab));
    armTab->setActionHandler(new ba(armTab, wepTab));

    //set up button labels
    TTF_Font* f = FontFactory::getSingleton()->getFont("font", 24);
    SDL_Color fg = {255, 255, 255};
    SDL_Color bg = {0, 0, 0};

    wepLine = new Line("Weapons", f, Line::solid, fg, bg);
    armLine = new Line("Armor", f, Line::solid, fg, bg);

    //add children
    addRenderableChild(wepTab);
    addRenderableChild(armTab);
    addRenderableChild(armLine);
    addRenderableChild(wepLine);

    addEventChild(wepTab);
    addEventChild(armTab);
}
InventoryScreen::~InventoryScreen() {
 }
//Frame----------------------
void InventoryScreen::bind() {
    ren_remove = eh_remove = false;
    Spin::getSingleton()->addRenderable(this);
    Spin::getSingleton()->addEventable(this);
}
void InventoryScreen::release() {
    setRenderableRemove();
    setEventRemove();
}
//Renderable-----------------
void InventoryScreen::onRender(SDL_Surface* surf) {
    wepLine->setPosition(wepTab->getCenterX() - wepLine->getW() / 2, wepTab->getCenterY() - wepLine->getH() / 2);
    armLine->setPosition(armTab->getCenterX() - armLine->getW() / 2, armTab->getCenterY() - armLine->getH() / 2);
    SDL_FillRect(surf, &surf->clip_rect, SDL_MapRGB(surf->format, 255, 255, 255));
    passRender(surf);
}
//EventHandler---------------
bool InventoryScreen::onEvent(SDL_Event* evt) {
    if (evt->type == SDL_KEYDOWN && evt->key.keysym.sym == SDLK_ESCAPE) {
        release();
        FrameManager::getSingleton()->getFrame("game_screen")->bind();
    }
    passEvent(evt);
    return KILL_EVENT;
}
//Inventory Screen=========================================