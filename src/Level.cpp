#include <Level.h>
#include <iostream>
#include <fstream>
using namespace std;

#define LEVEL_PREFIX "../res/level/"
#define LEVEL_POSTFIX ".level"
#define SIZE_TAG "[size]"
#define PALLET_TAG "[palatte]"
#define BLANKET_TAG "[blanket]"
#define POINT_TAG "[point]"
#define FIELD_TAG "[field]"
#define FIELD_END_TAG "[\field]"
#define BLANKET_PASS_TAG "[blanket_pass]"
#define POINT_PASS_TAG "[point_pass]"
#define FIELD_PASS_TAG "[field_pass]"
#define FIELD_PASS_END_TAG "[\field_pass]"
#define TRANSITION_TAG "[transition]"
#define ENTRANCE_TAG "[entrance]"
#define MONSTER_TAG "[monster]"

//constructor
Level::Level(int width, int height, int depth) {
    moveable = NULL;
    tileset = NULL;
    offsetX = offsetY = 0;
    tile_width = tile_height = 64;
    player = NULL;
    setMapDims(width, height, depth);
}
Level::Level(string levelName) {
    moveable = NULL;
    tileset = NULL;
    offsetX = offsetY = 0;
    tile_width = tile_height = 64;
    player = NULL;
    loadLevel(levelName);
}
Level::~Level() {
    for (int i = 0; i < tile_palatte.size(); i++) {
        delete tile_palatte[i];
    }
    for (int i = 0; i < getW(); i++) {
        delete tileset[i];
    }
    delete tileset;
}
//loaders
void Level::loadLevel(string filename) {
    cout << "loading level " << filename << endl;
    ifstream file((LEVEL_PREFIX + filename + LEVEL_POSTFIX).c_str(), ifstream::in);
    if (!file.good()) {
        cout << "could not load file: " << LEVEL_PREFIX + filename + LEVEL_POSTFIX << endl;
        return;
    }

    //clean up
    transitions.clear();
    entrances.clear();

    string token, sheetName, spriteName;
    int x, y, z, w, h, d, tag;
    while (file.good()) {
        file >> token;

        if (token.compare(SIZE_TAG) == 0) {
            file >> w >> h >> d;
            setMapDims(w, h, d);
            cout << "size set: " << w << ", " << h << ", " << d << endl;
        } else if (token.compare(PALLET_TAG) == 0) {
            file >> sheetName >> spriteName;
            cout << "palatting " << sheetName << ":" << spriteName << endl;
            tile_palatte.push_back(SpriteFactory::getSingleton()->createSprite(sheetName, spriteName));
        } else if (token.compare(BLANKET_TAG) == 0) {
            file >> x >> y >> z >> w >> h >> d >> tag;
            for (int i = x; i < x + w; i++) {
                for (int j = y; j < y + h; j++) {
                    for (int k = z; k < z + d; k++) {
                        setTileTag(i, j, k, tag);
                    }
                }
            }
        } else if (token.compare(BLANKET_PASS_TAG) == 0) {
            file >> x >> y >> z >> w >> h >> d >> tag;
            for (int i = x; i < x + w; i++) {
                for (int j = y; j < y + h; j++) {
                    setPassableValue(i, j, tag == 1);
                }
            }
        } else if (token.compare(POINT_TAG) == 0) {
            file >> x >> y >> z >> tag;
            setTileTag(x, y, z, tag);
        } else if (token.compare(FIELD_TAG) == 0) {
            file >> x >> y >> z >> w >> h >> d;
            for (int i = x; i < x + w; i++) {
                for (int j = y; j < y + h; j++) {
                    for (int k = z; k < z + h; k++) {
                        file >> tag;
                        setTileTag(i, j, k, tag);
                    }
                }
            }
        } else if (token.compare(TRANSITION_TAG) == 0) {
            Transition t;
            int tag, k;
            file >> t.nextLevel >> t.gx >> t.gy >> k >> t.entrance >> tag;
            cout << "adding exit at " << t.nextLevel << " " << t.gx << " " << t.gy << endl;
            transitions.push_back(t);
            setTileTag(t.gx, t.gy, k, tag);
        } else if (token.compare(ENTRANCE_TAG) == 0) {
            Entrance e;
            file >> e.gx >> e.gy;
            cout << "adding an entrance at " << e.gx << " " << e.gy << endl;
            entrances.push_back(e);
        } else if (token.compare(MONSTER_TAG) == 0) {
            file >> token;
            int x, y;
            file >> x >> y;
            cout << "loading a " << token << "at " << x << " " << y << endl;
            Unit* u = UnitFactory::getSingleton()->genUnit(token);
            u->gridPlace(x, y);
            addUnit(u);
        }
    }

    for (int k = 0; k < map_depth; k++) {
        for (int i = 0; i < map_height; i++) {
            for (int j = 0; j < map_width; j++) {
                cout << " " << tileset[j][i][k];
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {
            cout << " " << moveable[j][i];
        }
        cout << endl;
    }
}
//manips
void Level::addTile(Sprite* s) {
    cout << s << endl;
    tile_palatte.push_back(s);
}
void Level::addUnit(Unit* u) {
    units.push_back(u);
}
void Level::setPlayer(Unit* u) {
    player = u;
    player->gridPlace(entrances[0].gx, entrances[0].gy);
}
Unit* Level::remUnit(Unit* u) {
    for (int i = 0; i < units.size(); i++) {
        if (units[i] == u) {
            units.erase(units.begin() + i);
        }
    }
    return u;
}
Unit* Level::remUnit(int i) {
    if (i >= units.size()) return NULL;
    Unit* u = units[i];
    units.erase(units.begin() + i);
    return u;
}
void Level::scroll(int deltaX, int deltaY) {
    offsetX += deltaX;
    offsetY += deltaY;
}
void Level::setTileTag(int x, int y, int z, int tileTag) {
    if (x < 0 || x >= map_width) return;
    if (y < 0 || y >= map_height) return;
    if (z < 0 || z >= map_depth) return;
    if (tileset != NULL && tileTag < tile_palatte.size() + 1) {
        tileset[x][y][z] = tileTag;
    } else {
        cout << "shitfuck\n";
    }
}
void Level::setPassableValue(int x, int y, bool passable) {
    if (x < 0 || x >= map_width) return;
    if (y < 0 || y >= map_height) return;
    if (moveable != NULL) {
        moveable[x][y] = passable;
    }
}
//access
int Level::getMapW() {
    return map_width;
}
int Level::getMapH() {
    return map_height;
}
bool Level::validMove(int gx, int gy) {
    if (gx < 0 || gx > map_width - 1 || gy < 0 || gy > map_height - 1) {
        return false;
    }
    if (!moveable[gx][gy]) {
        return false;
    }
    if (player != NULL && player->getGridX() == gx && player->getGridY() == gy) {
        return false;
    }
    for (int i = 0; i < units.size(); i++) {
        if (units[i]->getGridX() == gx && units[i]->getGridY() == gy)
            return false;
    }
    return true;
}
bool Level::validTransition(int gx, int gy) {
    for (int i = 0; i < transitions.size(); i++) {
        if (transitions[i].gx == gx && transitions[i].gy == gy) {
            return true;
        }
    }
    return false;
}
Unit* Level::getUnit(int gx, int gy) {
    if (player != NULL && player->getGridX() == gx && player->getGridY() == gy) {
        return player;
    }
    for (int i = 0; i < units.size(); i++) {
        if (units[i]->getGridX() == gx && units[i]->getGridY() == gy) {
            return units[i];
        }
    }
    return NULL;
}
Unit* Level::getUnit(int i) {
    if (i < 0 || i >= units.size()) return NULL;
    return units[i];
}
Unit* Level::getPlayer() {
    return player;
}
//renderable
void Level::onRender(SDL_Surface* surf) {
    SDL_Rect oldclip = surf->clip_rect;
    surf->clip_rect = pos_rect;
    //draw map
    if (tile_palatte.size() > 0) {
        for (int j = 0; j < map_height; j++) {
            for (int i = 0; i < map_width; i++) {
                for (int k = 0; k < map_depth; k++) {
                    if (tileset[i][j][k] > 0) {
                        Sprite* s = tile_palatte[tileset[i][j][k] - 1];
                        s->setPosition(
                                i * tile_width + offsetX + getX(),
                                j * tile_height + offsetY + getY()
                                );
                        s->onRender(surf);
                    }
                }
            }
        }
    }
    //draw units
    for (int i = 0; i < units.size(); i++) {
        units[i]->getSprite()->setPosition(
                units[i]->getGridX() * tile_width + offsetX + getX(),
                units[i]->getGridY() * tile_height + offsetY + getY()
                );
        units[i]->getSprite()->onRender(surf);
    }
    if (player != NULL) {
        player->getSprite()->setPosition(
                player->getGridX() * tile_width + offsetX + getX(),
                player->getGridY() * tile_height + offsetY + getY()
                );
        player->getSprite()->onRender(surf);
    }
    surf->clip_rect = oldclip;
}
//placeable
void Level::setMapDims(int w, int h, int z) {
    if (moveable != NULL) {
        for (int i = 0; i < map_width; i++) {
            delete[] moveable[i];
        }
        delete[] moveable;
    }
    if (tileset != NULL) {
        for (int i = 0; i < map_width; i++) {
            for (int j = 0; j < map_height; j++) {
                delete[] tileset[i][j];
            }
            delete[] tileset[i];
        }
        delete[] tileset;
    }
    map_width = w;
    map_height = h;
    map_depth = z;
    tileset = new unsigned short**[w];
    moveable = new bool*[w];
    for (int i = 0; i < w; i++) {
        tileset[i] = new unsigned short*[h];
        moveable[i] = new bool[h];
        for (int j = 0; j < h; j++) {
            tileset[i][j] = new unsigned short[z];
            for (int k = 0; k < z; k++) {
                tileset[i][j][k] = 0;
            }
            moveable[i][j] = false;
        }
    }
}
//control
void Level::doTransition(int i) {
    if (i < 0 && i >= transitions.size()) return;

    int entrance = transitions[i].entrance;
    string level = transitions[i].nextLevel;
    cout << "load level: " << level << " at entrance " << entrance << endl;
    //clearUnits(false);
    loadLevel(level);
    placePlayer(entrance);
}
void Level::doTransition(int gx, int gy) {
    for (int i = 0; i < transitions.size(); i++) {
        if (transitions[i].gx == gx && transitions[i].gy == gy) {
            doTransition(i);
            return;
        }
    }
}
void Level::centerOnGrid(int gx, int gy) {
    int centerScreenX = (getW() - getX()) / 2;
    int centerScreenY = (getH() - getY()) / 2;

    int realX = gx * tile_width - tile_width / 2;
    int realY = gy * tile_height + tile_height / 2;

    int deltaX = centerScreenX - realX;
    int deltaY = centerScreenY - realY;

    offsetX = deltaX;
    offsetY = deltaY;
}
void Level::placePlayer(int gx, int gy) {
    if (player != NULL) {
        player->gridPlace(gx, gy);
    }
}
void Level::placePlayer(int entrance) {
    if (player != NULL && entrance < entrances.size() && entrance >= 0) {
        player->gridPlace(entrances[entrance].gx, entrances[entrance].gy);
        centerOnGrid(player->getGridX(), player->getGridY());
    }
}
void Level::clearUnits(bool doDelete) {
    if (doDelete) {
        for (int i = 0; i < transitions.size(); i++) {
            delete units[i];
        }
    }
    units.clear();
}