num_particles = 1000
particles = {}
texture = "particle.png"

startX = 0
startY = 0

-- initialize random
math.randomseed(os.time())
math.random(); math.random(); math.random()

function init()
    r = loadTexture("/home/patrick/Desktop/sdl-game/games/runner/assets/particle.png")
    if r ~= "ok" then
        print(r)
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
        particles[i]["t"] = particles[i]["t"] + delta
        if particles[i]["t"] > particles[i]["l"] then
            reset_particle(i)
        end
    end
end

function get_particle(index)
    return particles[i]
end

function set_start(x,y)
    startX = x
    startY = y
end

function reset_particle(index)
    a = math.random() * (math.pi / 8) + (math.pi / 4) + (math.pi * 0.19625)
    particles[index] = {
        x=startX,
        y=startY,
        xvel=0,
        yvel=0,
        xvel=math.random(500,1000) * math.cos(a),
        yvel=math.random(500,1000) * math.sin(a),
        angle=a,
        w=16,
        h=16,
        texture="particle.png",
        t=0,
        l=math.random() * 2.7 + 0.3
    }
end
