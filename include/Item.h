/* 
 * File:   Item.h
 * Author: Cow
 *
 * Created on April 21, 2013, 2:16 PM
 */

#ifndef ITEM_H
#define	ITEM_H

#include <map>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

namespace itemEnum {
    enum item_type {
        it_weapon = 0, it_armor, it_trinket, it_max
    };
    enum weapon_mods {
        wm_str = 0, wm_dex, wm_magic, wm_max
    };
    enum armor_type {
        at_head = 0, at_torso, at_arms, at_legs, at_feet, at_belt, at_max
    };
}

class Item {
public:
    //constructor
    Item(itemEnum::item_type type);
    ~Item();
    //access
    itemEnum::item_type getType();
    string getName();
    int getWeight();
    int getLevel();
    //manips
    void setName(string name);
    void setWeight(int weight);
    void setLevel(int level);
protected:
    string name;
    itemEnum::item_type type;
    int weight;
    int level;
};

class Weapon : public Item {
public:
    //constructor
    Weapon();
    ~Weapon();
    //manips
    void setDamage(int damage);
    void setDamageModifier(itemEnum::weapon_mods, float mod);
    void setSpeed(int speed);
    //access
    int getDamage(int strength, int dexerity, int magic);
    int getAttackCount(int dexterity);
    //control

private:
    int damage;
    float modifiers[itemEnum::wm_max];
    int speed;
};

class Armor : public Item {
public:
private:
};

class ItemFactory{
    class SpawnGroup{
    public:
        //Constructor
        SpawnGroup();
        //
    private:
        
    };
public:
    //constructors
    static ItemFactory* getSingleton();
    ItemFactory();
    ~ItemFactory();
    //spawners
    Item* spawnItem(string spawnGroup, int level);
    Item* spaenItem(string item);
    //loaders
    void loadFile(string filename);
private:
    void loadWeapon(ifstream& strm);
    void loadArmor(ifstream& strm);
    static ItemFactory* single;
    map<string, vector<string> > spawnGroups;
    map<string, Item*> items;
};


#endif	/* ITEM_H */

