local tools = require("tools")

floor = {}

-- root of the backtracing recursion
function generate_floor()
    math.randomseed(os.time())
    floor = tools.generate_matrix(100, 100)

    backtrace(floor)
end

function backtrace(current)
    if reject() then return end
    if accept() then output()
    s = first()
    while not s == nil do
        bt(s)
        s = extend()
end

function reject()

end

function accept()

end


function validate(c)
    local N = c.getn(floor)
    local M = c.getn(floor[0])

    for i=1,N do
        for j=1,M do
            if c[i][j] > 1 then
                return false
            end
        end
    end

    return true
end

function output()

end

function extend()

end

function first()

end

-- extend
function place_room(size)

end

function connect_rooms(size)

end
