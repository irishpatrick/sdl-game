#include "editor.hpp"

Editor::Editor() : engine::State() {

}

Editor::~Editor() {

}

void Editor::init(engine::Context& ctx) {

}

void Editor::update(float delta, const uint8_t* keys) {
    setEntryKey.check(keys[SDL_SCANCODE_N]);

    if (setEntryKey.fire()) {
        
    }
}

void Editor::render(engine::Context& ctx) {

}
