/* 
 * File:   Level.h
 * Author: Cow
 *
 * Created on April 21, 2013, 2:16 PM
 */

#ifndef LEVEL_H
#define	LEVEL_H

class Level;

#include <Unit.h>
#include <Virtuals.h>
#include <vector>
#include <string>

using namespace std;

class Level : public Renderable, public Placeable{
    struct Transition{
        int gx, gy;
        int entrance;
        string nextLevel;
    };
    struct Entrance{
        int gx, gy;
    };
public:
    //constructor
    Level(int width, int height, int depth);
    Level(string levelName);
    ~Level();
    //loaders
    void loadLevel(string filename);
    //manips
    void addTile(Sprite* s);
    void addUnit(Unit* u);
    void setPlayer(Unit* u);
    Unit* remUnit(Unit* u);
    Unit* remUnit(int i);
    void setMapDims(int w, int h, int z = 1);
    void scroll(int deltaX, int deltaY);
    void setTileTag(int x, int y, int z, int tileTag);
    void setPassableValue(int x, int y, bool passable);
    //access
    int getMapW();
    int getMapH();
    bool validMove(int gx, int gy);
    bool validTransition(int gx, int gy);
    Unit* getUnit(int gx, int gy);
    Unit* getUnit(int i);
    Unit* getPlayer();
    //control
    void doTransition(int tnum);
    void doTransition(int gx, int gy);
    void centerOnGrid(int gx, int gy);
    void placePlayer(int gx, int gy);
    void placePlayer(int entrance);
    void clearUnits(bool doDelete);
    //Renderable
    void onRender(SDL_Surface* surf);
private:
    //units
    Unit* player;
    vector<Unit*> units;
    //tiles
    vector<Sprite*> tile_palatte;
    vector<Transition> transitions;
    vector<Entrance> entrances;
    unsigned short*** tileset;
    bool** moveable;
    //drawing
    int offsetX, offsetY;
    int map_width, map_height, map_depth;
    int tile_width, tile_height;
};

#endif	/* LEVEL_H */

