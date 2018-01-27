#include "particleengine.h"
#include "particle.h"

ParticleEngine::ParticleEngine()
{
    for (int i=0; i<MAX_PARTICLES; i++)
    {
        list[i] = new Particle();
    }
}

ParticleEngine::~ParticleEngine()
{
    for (int i=0; i<MAX_PARTICLES; i++)
    {
        delete list[i];
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
}

void ParticleEngine::Play()
{

}
