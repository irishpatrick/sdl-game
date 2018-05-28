#include "item.hpp"

Item::Item() {

}

Item::~Item() {

}

void Item::load(const std::string& fn) {
    std::ifstream in(fn);
    if (in.fail()) {
        std::cout << "bad file: " << fn << std::endl;
        return;
    }
    // filestream to json
    in >> o;
    in.close();


}

void Item::use(engine::Sprite* s) {
    
}
