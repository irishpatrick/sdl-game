#pragma once

#include <string>
#include <engine.hpp>

class StaticGM
{
public:
    static void addGroup(const std::string&, engine::Group*);
    static void setActive(const std::string&);
    static void setEntry(const std::string&);
    static void setFocus(engine::Sprite*);
    static engine::Group* getGroup(const std::string&);
    static const std::string& getActiveId();
    static engine::Group* getActive();

private:
    static std::map<std::string, engine::Group*> groupMap;
    static engine::Group* activeGroup;
    static engine::Sprite* focus;
    static std::string activeId;
};
