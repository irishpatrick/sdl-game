#ifndef PARTICLEENGINE_H
#define PARTICLEENGINE_H

#define MAX_PARTICLES 100

#include <vector>
#include <string>
#include <fstream>
#include <json.hpp>

class Particle;

class ParticleEngine
{
public:
    ParticleEngine();
    ~ParticleEngine();

    void LoadEffect(const std::string&);
    void Play();

private:
    Particle* list[MAX_PARTICLES];
};

#endif /* PARTICLEENGINE_H */
