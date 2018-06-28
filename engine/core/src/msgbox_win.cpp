#ifdef _WIN32 

#include "msgbox.hpp"
#include <windows.h>

namespace core {

    UINT getIcon(int style) {
        switch (style) {
            case MsgBox::INFO:
                return MB_ICONINFORMATION;
            case MsgBox::WARNING:
                return MB_ICONWARNING;
            case MsgBox::ERROR:
                return MB_ICONERROR;
            case MsgBox::QUESTION:
                return MB_ICONQUESTION;
            default:
                return MB_ICONINFORMATION;
        }
    }

    UINT getButtons(int buttons) {
        switch (buttons) {
            case MsgBox::OK:
                return MB_OK;
            case MsgBox::OKCANCEL:
                return MB_OKCANCEL;
            case MsgBox::YESNO:
                return MB_YESNO;
            default:
                return MB_OK;
        }
    }

    int getSelection(int response) {
        switch (response) {
            case IDOK:
                return MsgBox::OK;
            case IDCANCEL:
                return MsgBox::CANCEL;
            case IDYES:
                return MsgBox::YES;
            case IDNO:
                return MsgBox::NO;
            default:
                return MsgBox::NONE;
        }
    }

    int MsgBox::show(int style, int buttons, std::string& title, std::string& content) {
        UINT flags = MB_TASKMODAL;
        flags |= getIcon(style);
        flags |= getButtons(buttons);

        return getSelection(MessageBox(nullptr, content.c_str(), title.c_str(), flags));
    }

}

#endif /* _WIN32 */