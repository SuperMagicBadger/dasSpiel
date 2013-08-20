
#include <UnitController.h>
#include <iostream>
#include <math.h>

using namespace std;
PlayerController::PlayerController(Unit* _player, Level* _level) {
    player = _player;
    level = _level;
    timeElapsed = 0;
    moveTimeSpacer = 30;
    up = down = left = right = false;
}
PlayerController::~PlayerController() {
    if (player != NULL) {
        delete player;
    }
}
Unit* PlayerController::getUnit() {
    return player;
}
bool PlayerController::onEvent(SDL_Event* evt) {
    switch (evt->type) {
        case SDL_KEYDOWN:
            switch (evt->key.keysym.sym) {
                case SDLK_UP:
                    up = true;
                    break;
                case SDLK_DOWN:
                    down = true;
                    break;
                case SDLK_LEFT:
                    left = true;
                    break;
                case SDLK_RIGHT:
                    right = true;
                    break;
                case SDLK_PERIOD:
                    if (player->activeTurn()) {
                        player->regenerateHealth();
                        player->clearSpeedCount();
                    }
                    break;
                case SDLK_SPACE:
                    if (player->activeTurn()) {
                        if (level->validTransition(player->getGridX(), player->getGridY())) {
                            cout << "aww yeah\n";
                            player->clearSpeedCount();
                            level->doTransition(player->getGridX(), player->getGridY());
                        }
                    }
                default:
                    return KEEP_EVENT;
            }
            break;
        case SDL_KEYUP:
            switch (evt->key.keysym.sym) {
                case SDLK_UP:
                    up = false;
                    break;
                case SDLK_DOWN:
                    down = false;
                    break;
                case SDLK_LEFT:
                    left = false;
                    break;
                case SDLK_RIGHT:
                    right = false;
                    break;
                default:
                    return KEEP_EVENT;
            }
            break;
        default:
            return KEEP_EVENT;
    }
    return KILL_EVENT;
}
bool PlayerController::tick() {
    if (player->getHealth() <= 0) {
        return false;
    }
    player->updateSpeedCount();
    return true;
}
void PlayerController::doTurn() {
    if (player->getHealth() > 0 && player->activeTurn() && (up || down || left || right)) {
        //pre move actions
        player->regenerateHealth();
        //current location
        int newx = player->getGridX();
        int newy = player->getGridY();
        //update plausible location based on bools
        if (up) newy--;
        else if (down) newy++;
        else if (left) newx--;
        else if (right) newx++;
        //do a test, then move if possible
        if (level->validMove(newx, newy)) {
            player->gridPlace(newx, newy);
            level->centerOnGrid(player->getGridX(), player->getGridY());
            player->clearSpeedCount();
        } else {
            Unit* u = level->getUnit(newx, newy);
            if (u != NULL) {
                player->attack(u);
                player->clearSpeedCount();
            } else {

                cout << "nope\n";
            }
        }
    }
}

//ai controller
AIController::AIController(Unit* u, Level* l) {
    monster = u;
    target = NULL;
    level = l;
}
AIController::~AIController() {
    delete monster;
}
void AIController::setTarget(Unit* u, int awareness) {
    if (u->getFaction() == monster->getFaction()) {
        return;
    }
    int x = u->getGridX() - monster->getGridX();
    int y = u->getGridY() - monster->getGridY();
    int d = x * x + y * y;
    d = sqrt(d);
    if (d <= monster->getSightRange()) {
        target = u;
    }
}
bool AIController::tick() {
    if (monster->getHealth() <= 0) {
        return false;
    }
    monster->updateSpeedCount();
    if (monster->activeTurn()) {
        if (target != NULL) {
            if (target->getHealth() <= 0) {
                target = NULL;
            } else {
                int x = 0, y = 0;
                if (target->getGridX() > monster->getGridX()) {
                    x = 1;
                } else if (target->getGridX() < monster->getGridX()) {
                    x = -1;
                } else if (target->getGridY() > monster->getGridY()) {
                    y = 1;
                } else if (target->getGridY() < monster->getGridY()) {
                    y = -1;
                }
                if (level->validMove(monster->getGridX() + x, monster->getGridY() + y)) {
                    monster->gridMove(x, y);
                } else if (target->getGridX() == monster->getGridX() + x && target->getGridY() == monster->getGridY() + y) {
                    monster->attack(target);
                }
            }
        }
        monster->clearSpeedCount();
    }
    return true;
}
Unit* AIController::getUnit() {
    return monster;
}
//ai controller