#include "list.h"

namespace gui {

List::List() : Widget() {
    font_w = 0;
    font_h = 0;
}

List::~List() {

}

void List::setFont(SDL_Renderer* renderer, const string& dir) {
    for (char i=32; i<123; i++) {
        cout << "loading " << dir << "/" << i << endl;
        string fn = dir + "/" + i + ".png";
        font[i] = IMG_LoadTexture(renderer, fn.c_str());
        if (font[i] == nullptr) {
            cout << "IMG_Load error: " << IMG_GetError() << endl;
        }
        SDL_QueryTexture(font['a'], nullptr, nullptr, &font_w, &font_h);
        // scale
        font_w = font_w * 0.2;
        font_h = font_h * 0.2;
        cout << "scale: " << font_w << ", " << font_h << endl;
    }
}

void List::addItem(const string& str) {
    items.push_back(str);
}

void List::draw(SDL_Renderer* renderer) {
    // draw background
    w = 100;
    h = items.size() * (font_h + 2);

    SDL_Surface* s = SDL_CreateRGBSurface(
        0, w, h, 32,
        0x00FF0000,
        0x0000ff00,
        0x000000ff,
        0
    );

    SDL_LockSurface(s);

    cairo_surface_t* c = cairo_image_surface_create_for_data(
        (unsigned char*)s->pixels,
        CAIRO_FORMAT_RGB24,
        s->w,
        s->h,
        s->pitch
    );

    cairo_t* cr = cairo_create(c);

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_rectangle(cr, 0, 0, w, h);
    cairo_stroke_preserve(cr);
    cairo_fill(cr);

    SDL_UnlockSurface(s);

    background = SDL_CreateTextureFromSurface(renderer, s);
    SDL_FreeSurface(s);

    //SDL_SetRenderTarget(renderer, background);

    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    SDL_RenderCopy(renderer, background, nullptr, &r);

    for (unsigned int i=0; i<items.size(); i++) {
        if (i == current) {
            // draw marker

        }
        // draw text
        int text_x = x;
        int text_y = y; // + (i * h);
        string word = items[i];
        for (unsigned int j=0; j<word.size(); j++) {
            SDL_Rect r;
            r.x = text_x + (font_w * j);
            r.y = text_y + (font_h * i);
            r.w = font_w;
            r.h = font_h;

            SDL_RenderCopy(renderer, font[word[j]], nullptr, &r);
        }
    }

    //SDL_SetRenderTarget(renderer, nullptr);
}

}
