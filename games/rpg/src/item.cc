#include "item.h"

json Item::o = json();

Item::Item() {

}

Item::~Item() {

}

void Item::loadItems(const string& fn) {
    ifstream in(fn);
    if (!in.good()) {
        cout << "file error" << endl;
        return;
    }
    in >> o;
}

json Item::toJson() {
    json o = json::object();
    o["mode"] = mode;
    return o;
}
