num_particles = 100
particles = {}

-- initialize random
math.randomseed(os.time())
math.random(); math.random(); math.random()

function init()
    r = loadTexture("../../runner/assets/particle.png")
    if r == -1 then
        print("loadTexture error!")
    end

    for i=0,num_particles-1 do

    end
end

function update()

end

function get_particle(index)

end

function reset_particle(index)

end
