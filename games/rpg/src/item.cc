#include "item.h"

Item::Item() {
    m_description = "";
    m_usable = true;
}

Item::~Item() {

}

void Item::use(engine::Sprite* user) {

}

string Item::getDescription() {
    return m_description;
}

bool Item::isUsable() {
    return m_usable;
}
