#include "Stats.hpp"

Stats::Stats()
{

}

Stats::~Stats()
{

}

void Stats::reset()
{
    for (auto& e : modifiers)
    {
        e.second = 0;
    }
}

void Stats::modify(const std::string& str, uint32_t n)
{
    modifiers[str] += n;
}

void Stats::change(const std::string& str, uint32_t n)
{
    stats[str] += n;
}

void Stats::set(const std::string& str, uint32_t n)
{
    stats[str] = n;
}

uint32_t Stats::get(const std::string& str)
{
    return stats[str] + modifiers[str];
}

uint32_t Stats::getBase(const std::string& str)
{
    return stats[str];
}

void Stats::load(const std::string& str)
{
    std::ifstream in(str);
    json o;
    in >> o;

    for (json::iterator it = o.begin(); it != o.end(); it++) {
        if (boost::algorithm::ends_with(it.key(), "_mod")) {
            std::vector<std::string> v;
            const std::string& str(it.key());
            boost::algorithm::split(v, str, boost::algorithm::is_any_of("_"));
            modifiers[v[0]] = it.value();
        }
        stats[it.key()] = it.value();
    }
}

void Stats::write(const std::string& str)
{
    json o;

    for (auto const& e : stats) {
        o[e.first] = e.second;
    }

    for (auto const& e : modifiers) {
        o[e.first + "_mod"] = e.second;
    }

    std::ofstream out(str);
    out << std::setw(4) << o << std::endl;
}
