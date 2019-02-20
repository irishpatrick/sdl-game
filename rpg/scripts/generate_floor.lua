local tools = require("tools")

floor = {}

function backtrace(mat)
    if reject(mat) then return end
    if accept(mat) then output(mat) end
    s = first(mat)
    while s != nil do
        backtrace(s)
        s = next(s)
    end
end

function reject(mat)

end

function accept(mat)

end

function output(mat)

end

function first(mat)

end

function next(mat)

end
