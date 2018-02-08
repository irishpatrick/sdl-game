#include "particleengine.h"
#include "particle.h"
#include "util.h"

ParticleEngine::ParticleEngine()
{
    list_ = nullptr;
    name_ = "";
}

ParticleEngine::~ParticleEngine()
{
    if (list_ != nullptr)
    {
        printf("delete list_\n");
        delete[] list_;
    }
}

void ParticleEngine::LoadEffect(const std::string& fn)
{
    std::ifstream i(fn);
	if (!i)
	{
		printf("failed to open %s\n", fn.c_str());
		exit(1);
	}
	nlohmann::json o;
	i >> o;

    if (!Util::JsonExists(o, "count"))
    {
        return;
    }
    uint32_t n = o["count"];
    list_ = new Particle[n];

    if (Util::JsonExists(o, "name"))
    {
        name_ = o["name"];
    }
}

void ParticleEngine::Play()
{

}
