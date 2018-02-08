#ifndef PARTICLEENGINE_H
#define PARTICLEENGINE_H

#define MAX_PARTICLES 100

#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
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
    std::string name_;
    Particle* list_;
    uint32_t count_;
};

#endif /* PARTICLEENGINE_H */
