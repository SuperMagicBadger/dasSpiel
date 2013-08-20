#include <MainMenu.h>
#include <Spinner.h>
#include <string>

using namespace std;

class fek : public ButtonAction {
public:
    fek(Button* btn) {
        user = btn;
    }
    void onPress() {
        cout << "doing shit\n";
        FrameManager::getSingleton()->release("main_menu");
        FrameManager::getSingleton()->bind("char_screen");
        cout << "doing shit\n";
    }
    Button* user;
};
MainMenu::MainMenu() {
    title = SpriteFactory::getSingleton()->createSprite("main_menu", "title");
    title->setPosition(50, 50);

    newgame = new Button(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_standard"));
    newgame->setHover(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_highlight"));
    newgame->setPress(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_down"));
    newgame->setDisable(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_disable"));
    newgame->setActionHandler(new fek(newgame));
    newgame->setPosition(0, title->getH() + title->getY() + 50);

    loadgame = new Button(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_standard"));
    loadgame->setHover(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_highlight"));
    loadgame->setPress(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_down"));
    loadgame->setDisable(SpriteFactory::getSingleton()->getSpriteBody("main_menu", "button_disable"));
    loadgame->setPosition(0, newgame->getY() + loadgame->getH() + 50);

    SDL_Color bg;
    bg.r = 0;
    bg.g = 0;
    bg.b = 0;
    
    SDL_Color fg;
    fg.r = 255;
    fg.g = 255;
    fg.b = 255;
    
    ngText = new Line("New Game", FontFactory::getSingleton()->getFont("font", 24), Line::solid, fg, bg);
    lgText = new Line("Load Game", FontFactory::getSingleton()->getFont("font", 24), Line::solid, fg, bg);
    
    ngText->setPosition(0, title->getH() + title->getY() + 50);
    lgText->setPosition(0, newgame->getY() + loadgame->getH() + 50);
    
    addRenderableChild(title);
    addRenderableChild(newgame);
    addRenderableChild(loadgame);
    addRenderableChild(ngText);
    addRenderableChild(lgText);

    addEventChild(newgame);
    addEventChild(loadgame);
}
MainMenu::~MainMenu() {
    delete title;
    delete newgame;
}
void MainMenu::bind() {
    ren_remove = eh_remove = false;
    cout << "binding\n";
    Spin::getSingleton()->addRenderable(this);
    Spin::getSingleton()->addEventable(this);
}
void MainMenu::release() {
    setRenderableRemove();
    setEventRemove();
}
void MainMenu::onRender(SDL_Surface* surf) {
    SDL_FillRect(surf, &surf->clip_rect, SDL_MapRGB(surf->format, 255, 255, 255));

    newgame->setPosition(surf->w - newgame->getW() - 20, newgame->getY());
    loadgame->setPosition(surf->w - loadgame->getW() - 20, loadgame->getY());
    
    ngText->setPosition(newgame->getX() + 10, newgame->getY() + 10);
    lgText->setPosition(loadgame->getX() + 10, loadgame->getY() + 10);

    passRender(surf);
}
bool MainMenu::onEvent(SDL_Event* evt) {
    if(evt->type == SDL_KEYDOWN && evt->key.keysym.sym == SDLK_ESCAPE){
        Spin::getSingleton()->stop();
        return KILL_EVENT;
    }
    passEvent(evt);
    return false;
}
