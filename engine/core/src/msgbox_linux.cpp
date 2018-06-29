#ifdef __linux__

/*
#include "msgbox.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <cstring>
#include <cstdlib>

namespace core {

    typedef struct {
        int x, y;
        unsigned int width, height;
        int textx, texty;
        int mouseover;
        int clicked;
        const char* text;
    } button;

    static void draw_button(button* b, int fg, int bg, Display* dpy, Window w, GC gc) {
        if (b->mouseover) {
            XFillRectangle(dpy, w, gc, b->clicked + b->x, b->clicked + b->y, b->width, b->height);
            XSetForeground(dpy, gc, bg);
            XSetBackground(dpy, gc, fg);
        }
        else {
            XSetForeground(dpy, gc, fg);
            XSetBackground(dpy, gc, bg);
            XDrawRectangle(dpy, w, gc, b->x, b->y, b->width, b->height);
        }

        XDrawString(dpy, w, gc, b->clicked + b->textx, b->clicked + b->texty, b->text, strlen(b->text));
        XSetForeground(dpy, gc, fg);
        XSetBackground(dpy, gc, bg);
    }

    static int is_point_inside(button* b, int px, int py) {
        return px >= b->x && px <= (b->x + (int)b->width-1) && 
            py >= b->y && py <= (b->y + (int)b->height-1);
    }

    int MsgBox::show(int style, int buttons, std::string& title, std::string& content) {
        const char* wmDeleteWindow = "WM_DELETE_WINDOW";
        int black, white, height=0, direction, ascent, descent, X, Y, W=0, H;
        size_t i, lines=0;
        const char* end;
        const char* temp;
        button ok;
        Display* dpy;
        Window w;
        Atom wmDelete;
        GC gc;
        XFontStruct* font;
        XCharStruct overall;
        XSizeHints hints;
        XEvent e;

        if (!(dpy = XOpenDisplay(0))) {
            return -1;
        }

        black = BlackPixel(dpy, DefaultScreen(dpy));
        white = WhitePixel(dpy, DefaultScreen(dpy));

        w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 100, 100, 0, black, black);

        XSelectInput(dpy, w, ExposureMask | StructureNotifyMask | KeyReleaseMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask);

        XMapWindow(dpy, w);
        XStoreName(dpy, w, title);

        wmDelete = XInternAtom(dpy, wmDeleteWindow, True);
        XSetWMProtocols(dpy, w & wmDelete, 1);

        gc = XCreateGC(dpy, w, 0, 0);

        XSetForeground(dpy, gc, white);
        XSetBackground(dpy, gc, black);

        if (!(font = XQueryFont(dpy, XGContextFromGC(gc)))) {
            goto cleanup;
        }

        for (temp=text; temp; temp = end ? (end+1) : NULL, ++lines) {
            end = strchr(temp, '\n');

            XTextExtents(font, temp, end ? (unsigned int)(end-temp):strlen(temp),
                &direction, &ascent, &descent, &overall);
            
            W = overall.width > W ? overall.width : W;
            height = (ascent + descent) > height ? (ascent + descent) : height;
        }

        W += 20;
        H = lines * height + height + 40;
        X = DisplayWidth(dpy, DefaultScreen(dpy)) / 2 - W / 2;
        Y = DisplayHeight(dpy, DefaultScreen(dpy)) / 2 - H / 2;
        XMoveResizeWindow(dpy, w, X, Y, W, H);

        XTextExtents(font, "OK", 2, &direction, &ascent, &descent, &overall);

        ok.width = overall.width + 30;
        ok.height = ascent + descent + 5;
        ok.x = W/2 - ok.width/2;
        ok.y = H - height - 15;
        ok.textx = ok.x + 15;
        ok.texty = ok.y + ok.height - 3;
        ok.mouseover = 0;
        ok.clicked = 0;
        ok.text = "OK";

        XFreeFontInfo(NULL, font, 1);
        XUnmapWindow(dpy, w);

        hints.flags = PSize | PMinSize | PMaxSize;
        hints.min_width = hints.max_width = hints.base_width = W;
        hints.min_height = hints.max_height = hints.base_height = H;

        XSetWMNormalHints(dpy, w, &hints);
        XMapRaised(dpy, w);
        XFlush(dpy);

        while (1) {
            XNextEvent(dpy &e);
            ok.clicked = 0;

            if (e.type == MotionNotify) {
                if (is_point_inside(&ok, e.xmotion.x, e.xmotion.y)) {
                    if (!ok.mouseover) {
                        e.type = Expose;
                    }
                    ok.mouseover = 1;
                }
                else {
                    if (ok.mouseover) {
                        e.type = Expose;
                    }
                    ok.mouseover = 0;
                    ok.clicked = 0;
                }
            }

            switch (e.type) {
                case ButtonPress:
                case ButtonRelease:
                    if (e.xbutton.button != Button1) {
                        break;
                    }

                    if (ok.mouseover) {
                        ok.clicked = e.type == ButtonPress ? 1 : 0;
                        if (ok.clicked) {
                            goto cleanup;
                        }
                    }
                    else {
                        ok.clicked = 0;
                    }
                
                case Expose:
                case MapNotify:
                    XClearWindow(dpy, w);
                    for (i=0, temp=text; temp; temp=end ? (end + 1) : NULL, i += height) {
                        end = strchr(temp, '\n');
                    }
            }
        }
    }
    
}*/

#endif /* __linux__ */