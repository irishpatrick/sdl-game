#include "stats.h"

Stats::Stats() {

}

Stats::~Stats() {

}

void Stats::reset() {
    for (auto& e : modifiers) {
        e.second = 0;
    }
}

void Stats::modify(const string& str, uint32_t n) {
    modifiers[str] += n;
}

void Stats::change(const string& str, uint32_t n) {
    stats[str] += n;
}

void Stats::set(const string& str, uint32_t n) {
    stats[str] = n;
}

uint32_t Stats::get(const string& str) {
    return stats[str] + modifiers[str];
}

uint32_t Stats::getBase(const string& str) {
    return stats[str];
}

void Stats::load(const string& str) {
    ifstream in(str);
    json o;
    in >> o;

    for (json::iterator it = o.begin(); it != o.end(); it++) {
        stats[it.key()] = it.value();
        modifiers[it.key()] = 0;
    }
}

void Stats::write(const string& str) {
    json o;

    for (auto const& e : stats) {
        o[e.first] = e.second;
    }

    ofstream out(str);
    out << setw(4) << o << endl;
}
