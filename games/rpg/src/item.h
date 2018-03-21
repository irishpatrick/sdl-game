#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "engine.h"
#include "nlohmann/json.hpp"

using namespace std;

class Item {

public:
    Item();
    virtual ~Item();

    string getDescription();
    bool isUsable();
    virtual void use(engine::Sprite*);

protected:
    string m_description;
    string m_name;
    bool m_usable;
};

#endif /* ITEM_H */
