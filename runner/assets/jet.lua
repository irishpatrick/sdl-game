num_particles = 100
particles = {}
texture = "particle.png"

-- initialize random
math.randomseed(os.time())
math.random(); math.random(); math.random()

function init()
    r = loadTexture("../../runner/assets/particle.png")
    if r == -1 then
        print("loadTexture error!")
    end

    for i=0,num_particles-1 do
        particles[i] = {}
        reset_particle(i)
    end
end

function update(delta)
    for i=0,num_particles-1 do
        particles[i]["x"] = particles[i]["x"] + (particles[i]["xvel"] * delta)
        particles[i]["y"] = particles[i]["y"] + (particles[i]["yvel"] * delta)
    end
end

function get_particle(index)
    return particles[i]
end

function reset_particle(index)
    a = math.random() * (math.pi * 2)
    particles[index] = {
        x=0,
        y=0,
        xvel=0,
        yvel=0,
        --xvel=math.random(100,200) * math.cos(a),
        --yvel=math.random(200,200) * math.sin(a),
        angle=a,
        w=10,
        h=10
    }
end
