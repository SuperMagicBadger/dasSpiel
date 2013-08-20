/* 
 * File:   Monster.h
 * Author: Cow
 *
 * Created on April 21, 2013, 2:16 PM
 */

#ifndef MONSTER_H
#define	MONSTER_H


class Unit;
class UnitFactory;

#include <vector>
#include <Virtuals.h>
#include <Sprites.h>
#include <Item.h>
#include <Level.h>
#include <string>

using namespace std;

class Unit {
public:
    //constructor
    Unit();
    Unit(const Unit& u);
    ~Unit();
    //team manips    
    void setFaction(unsigned short faction);
    //stat manips
    void setName(string str);
    void setMaxCaryWeight(int w);
    void setStats(int str, int dex, int magic);
    void setSpeed(int s);
    void setAwareness(int aware);
    void setSightRange(int range);
    void addExp(int exp);
    void setExp(int exp);
    //draw manips
    Sprite* setSprite(Sprite* s);
    //access
    Sprite* getSprite();
    unsigned short getFaction();
    //stat access
    unsigned short getSpeed();
    string getName();
    string getClassName();
    void setClassName(string cn);
    int getAwareness();
    int getSightRange();
    int numItems();
    //position access
    int getGridX();
    int getGridY();
    //position control
    void gridMove(int delta_x, int delta_y);
    void gridPlace(int x, int y);
    //health control
    int getHealth();
    int getMaxHealth();
    void setHealth(int h);
    void setMaxHealth(int h);
    void regenerateHealth();
    void setRegenRate(float f);
    //turn control
    void updateSpeedCount();
    void halfSpeedCount();
    void clearSpeedCount();
    unsigned short getSeedCount();
    bool activeTurn();
    //combat control
    void attack(Unit* u);
    void defend(int damage);
    //inventory control
    bool pickUp(Item* i);
    Item* getItem(int i);
    Item* dropItem(int i);
    void equip(int i);
    int getInvSize();
private:
    //stat info
    string name, className;
    int health, maxHealth;
    float regenRate, regenCounter;
    unsigned short strength, dexterity, magic;
    int level, exp;
    int awareness, sight;
    //control info
    Sprite* image;
    int gridX, gridY;
    //item info
    Weapon* wep;
    Armor* armor[itemEnum::at_max];
    vector<Item*> inventory;
    //faction info
    unsigned short fid;
    //turn info
    unsigned short speed, count;
};


class UnitFactory {
public:
    //constructor
    static UnitFactory* getSingleton();
    UnitFactory();
    ~UnitFactory();
    //generators
    Unit* genUnit(string unitname);
    //access
    //manips
    void loadSheet(string filename);
private:
    static UnitFactory* single;
    map<string, Unit*> unit_list;
};

#endif	/* MONSTER_H */

