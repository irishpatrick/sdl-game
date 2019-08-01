#include "Stats.hpp"

Stats::~Stats()
{

}

void Stats::recordVolley()
{
    m_volley++;
}

void Stats::resetVolley()
{
    m_volley = 0;
}
