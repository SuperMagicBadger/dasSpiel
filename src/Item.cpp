
#include <Item.h>
#include <math.h>
#include <iostream>

using namespace std;

#define item_prefix  "../res/items/"
#define item_postfix ".item"

#define WEAPON_META_TAG "[weapon]"
#define END_WEAPON_META_TAG "[/weapon]"
#define LEVEL_META_TAG "[level]"
#define WEIGHT_META_TAG "[weight]"
#define SPEED_META_TAG "[speed]"
#define DAMAGE_META_TAG "[damage]"
#define MODIFIER_META_TAG "[modifier]"
#define STR_META_TAG "[str]"
#define DEX_META_TAG "[dex]"
#define MAG_META_TAG "[mag]"
#define INCLUDE_TAG "[include]"

using namespace itemEnum;
//item-------------------------------------------
//constructors-----
Item::Item(item_type _type) {
    type = _type;
}
Item::~Item() { }
//access-----------
item_type Item::getType() {
    return type;
}
string Item::getName() {
    return name;
}
int Item::getLevel() {
    return level;
}
int Item::getWeight() {
    return weight;
}
//manips-----------
void Item::setName(string _name) {
    name = _name;
}
void Item::setWeight(int _weight) {
    weight = _weight;
}
void Item::setLevel(int _level) {
    level = _level;
}
//item===========================================
//Weapon-----------------------------------------
Weapon::Weapon() : Item(it_weapon) { }
Weapon::~Weapon() { }
//access-----------
int Weapon::getDamage(int str, int dex, int mag) {
    return damage + str * modifiers[wm_str] + dex * modifiers[wm_dex] + mag * modifiers[wm_magic];
}
int Weapon::getAttackCount(int dex) {
    return ((speed - 1) / 20.0) * dex + 1;
}
//manips-----------
void Weapon::setDamage(int dmg) {
    damage = dmg;
}
void Weapon::setDamageModifier(weapon_mods wm, float mod) {
    modifiers[wm] = mod;
}
void Weapon::setSpeed(int _speed) {
    speed = _speed;
}
//Weapon=========================================
//Armor------------------------------------------

//Armor==========================================
//Item Factory-----------------------------------
//constructors-----
ItemFactory* ItemFactory::single;
ItemFactory* ItemFactory::getSingleton() {
    if (single == NULL) {
        single = new ItemFactory();
    }
    return single;
}
ItemFactory::ItemFactory() { }
ItemFactory::~ItemFactory() { }
//spawners---------
//loaders----------
void ItemFactory::loadFile(string filename) {
    ifstream strm((item_prefix + filename + item_postfix).c_str(), ifstream::in);
    if (strm.good()) {
        cout << "loading file " << filename << endl;
    } else {
        cout << "could not load item file " << item_prefix + filename + item_postfix << endl;
    }
    string token;

    while (strm.good()) {
        strm >> token;
        if (token.compare(WEAPON_META_TAG) == 0) {
            loadWeapon(strm);
        }
    }
}
void ItemFactory::loadWeapon(ifstream& strm) {
    Weapon* w = new Weapon();
    string token;
    int iTemp;
    float fTemp;

    strm >> token;
    w->setName(token);

    cout << "loading [weapon] " << token << endl;

    while (strm.good()) {
        strm >> token;
        if (token.compare(LEVEL_META_TAG) == 0) {
            strm >> iTemp;
            w->setLevel(iTemp);
        } else if (token.compare(WEIGHT_META_TAG) == 0) {
            strm >> iTemp;
            w->setWeight(iTemp);
        } else if (token.compare(DAMAGE_META_TAG) == 0) {
            strm >> iTemp;
            w->setDamage(iTemp);
        } else if (token.compare(SPEED_META_TAG) == 0) {
            strm >> iTemp;
            w->setSpeed(iTemp);
        } else if (token.compare(MODIFIER_META_TAG) == 0) {
            strm >> token >> fTemp;
            if (token.compare(STR_META_TAG)) {
                w->setDamageModifier(itemEnum::wm_dex, fTemp);
            } else if (token.compare(DEX_META_TAG)) {
                w->setDamageModifier(itemEnum::wm_str, fTemp);
            }
        } else if (token.compare(END_WEAPON_META_TAG) == 0) {
            items[w->getName()] = w;
            return;
        } else if(token.compare(INCLUDE_TAG) == 0){
            strm >> token;
            loadFile(token);
        }
    }
}
//Item Factory===================================