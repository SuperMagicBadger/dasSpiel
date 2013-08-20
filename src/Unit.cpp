
#include <Unit.h>
#include <iostream>
#include <fstream>
using namespace std;
using namespace itemEnum;

#define unit_prefix "../res/units/"
#define unit_postfix ".unit"

#define UNIT_META_TAG "[unit]"
#define UNIT_END_META_TAG "[/unit]"
#define STATS_META_TAG "[stats]"
#define HP_META_TAG "[max_hp]"
#define SPEED_META_TAG "[speed]"
#define REGEN_META_TAG "[regen]"
#define WEP_META_TAG "[base_weapon]"
#define SPRITE_META_TAG "[sprite]"

//Unit-----------------------------------------------------
//constructor
Unit::Unit() {
    fid = 0;
    count = 0;
    maxHealth = health = 8;
    strength = dexterity = magic = 8;
    speed = 10;
    gridX = gridY = 0;
    wep = NULL;
    image = NULL;
    sight = awareness = 4;
    regenCounter = 0;
    regenRate = 0.05;
}
Unit::Unit(const Unit& u) {
    name = u.name;
    className = u.className;
    health = u.health;
    maxHealth = u.maxHealth;
    regenRate = u.regenRate;
    regenCounter = u.regenCounter;
    strength = u.strength;
    dexterity = u.dexterity;
    magic = u.magic;
    level = u.level;
    exp = u.exp;
    awareness = u.awareness;
    sight = u.sight;
    if (u.image != NULL) {
        image = new Sprite(*u.image);
    }
    fid = u.fid;
    speed = u.speed;
    count = u.count;
}
Unit::~Unit() {
    if (image != NULL) {
        delete image;
    }
}
//manips
void Unit::setName(string str) {
    name = str;
}
Sprite* Unit::setSprite(Sprite* s) {
    Sprite* prev = image;
    image = s;
    return prev;
}
void Unit::setFaction(unsigned short faction) {
    fid = faction;
}
void Unit::setAwareness(int aware) {
    awareness = aware;
}
void Unit::setSightRange(int range) {
    sight = 5;
}
void Unit::setStats(int str, int dex, int magic) {
    strength = str;
    dexterity = dex;
    magic = magic;
}
void Unit::setSpeed(int s) {
    speed = s;
}
//access
unsigned short Unit::getFaction() {
    return fid;
}
string Unit::getName() {
    return name;
}
string Unit::getClassName() {
    return className;
}
void Unit::setClassName(string cn) {
    className = cn;
}
Sprite* Unit::getSprite() {
    return image;
}
unsigned short Unit::getSpeed() {
    return speed;
}
int Unit::getGridX() {
    return gridX;
}
int Unit::getGridY() {
    return gridY;
}
int Unit::getAwareness() {
    return awareness;
}
int Unit::getSightRange() {
    return sight;
}
//position control
void Unit::gridMove(int delta_x, int delta_y) {
    gridX += delta_x;
    gridY += delta_y;
}
void Unit::gridPlace(int x, int y) {
    gridX = x;
    gridY = y;
}
//health control
int Unit::getHealth() {
    return health;
}
int Unit::getMaxHealth() {
    return maxHealth;
}
void Unit::setMaxHealth(int h) {
    maxHealth = h;
    health = health > maxHealth ? maxHealth : health;
}
void Unit::setHealth(int h) {
    health = h > maxHealth ? maxHealth : h;
}
void Unit::regenerateHealth() {
    if (health < maxHealth) {
        regenCounter += regenRate;
        cout << regenRate << " " << regenCounter << endl;
        if (regenCounter >= 1) {
            health++;
            regenCounter--;
        }
    }
}
void Unit::setRegenRate(float f) {
    if (f >= 0) {
        regenRate = f;
    }
}
//turn control
void Unit::updateSpeedCount() {
    count += speed;
    count = count > 100 ? 100 : count;
}
void Unit::halfSpeedCount() {
    count /= 2;
}
void Unit::clearSpeedCount() {
    count = 0;
}
unsigned short Unit::getSeedCount() {
    return count;
}
bool Unit::activeTurn() {
    return count >= 100;
}
//combat control
void Unit::attack(Unit* u) {
    if (wep != NULL) {
        int d = wep->getDamage(strength, dexterity, magic);
        for (int i = 0; i < wep->getAttackCount(dexterity); i++) {
            u->defend(d);
        }
    } else {
        u->defend((strength / 2) + 1);
    }

}
void Unit::defend(int damage) {
    cout << "Unit took " << damage << " points of damage\n";
    health -= damage;
}
//inventory control
bool Unit::pickUp(Item* i) {
    inventory.push_back(i);
}
Item* Unit::getItem(int i) {
    return inventory[i];
}
Item* Unit::dropItem(int i) {
    Item* ret = inventory[i];
    inventory.erase(inventory.begin() + i);
    return ret;
}
void Unit::equip(int i) {
    switch (inventory[i]->getType()) {
        case it_weapon:
            wep = (Weapon*) inventory[i];
            break;
        case it_armor:
            Armor* a = (Armor*) inventory[i];
            break;
    }
}
int Unit::getInvSize() {
    return inventory.size();
}
//Unit=====================================================
//Unit Factory---------------------------------------------
//constructor-----------
UnitFactory* UnitFactory::single = NULL;
UnitFactory* UnitFactory::getSingleton() {
    if (single == NULL) {
        single = new UnitFactory();
    }
    return single;
}
UnitFactory::UnitFactory() {
 }
UnitFactory::~UnitFactory() {
 }
//generators------------
Unit* UnitFactory::genUnit(string unitname) {
    if (unit_list.find(unitname) == unit_list.end()) return NULL;

    return new Unit(*unit_list[unitname]);
}
//manips----------------
void UnitFactory::loadSheet(string filename) {
    ifstream strm((unit_prefix + filename + unit_postfix).c_str(), ifstream::in);
    string token, token2;
    int iTemp, iTemp2, iTemp3;
    ;
    float fTemp;

    Unit* u;

    while (strm.good()) {
        strm >> token;

        if (token.compare(UNIT_META_TAG) == 0) {
            strm >> token;
            u = new Unit();
            u->setClassName(token);
            cout << "loaded " << token << " class\n";
        } else if (token.compare(UNIT_END_META_TAG) == 0) {
            unit_list[u->getClassName()] = u;
            u = NULL;
        } else if (token.compare(HP_META_TAG) == 0) {
            strm >> iTemp;
            u->setMaxHealth(iTemp);
        } else if (token.compare(SPEED_META_TAG) == 0) {
            strm >> iTemp;
            u->setHealth(iTemp);
        } else if (token.compare(REGEN_META_TAG) == 0) {
            strm >> fTemp;
            u->setRegenRate(fTemp);
        } else if (token.compare(WEP_META_TAG) == 0) {
            strm >> token;
        } else if (token.compare(STATS_META_TAG) == 0) {
            strm >> iTemp >> iTemp2 >> iTemp3;
            u->setStats(iTemp, iTemp2, iTemp3);
        } else if (token.compare(SPRITE_META_TAG) == 0) {
            strm >> token >> token2;
            u->setSprite(SpriteFactory::getSingleton()->createSprite(token, token2));
        }
    }
}
//Unit Factory=============================================
