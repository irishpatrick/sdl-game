#!/usr/local/bin/lua

local tools = require("tools")

function print_problem(p)
    for i=1, #p.mat
    do
        for j=1, #p.mat[i]
        do
            io.write(p.mat[i][j])
            io.write(" ")
        end
        io.write("\n")
    end
end

function generate(prob)
    init(prob)
    print_problem(prob)
    backtrace(prob)
    --first(prob)
    print_problem(prob)
end

function init(prob)
    prob.mat = tools.generate_matrix(100, 100)
    prob.last = prob.mat
    prob.rc = 4
    prob.rs = 6
    prob.x = 1
    prob.y = 1
end

function backtrace(prob)
    if reject(prob)
    then
        return
    end

    if accept(prob)
    then
        output(prob)
    end

    s = first(mat)

    while s ~= nil
    do
        backtrace(s)
        s = next(s)
    end
end

function reject(prob)
    for i=1,#mat
    do
        for j=1,#mat[i]
        do
            if mat[i][j] > 1
            then
                return false
            end
        end
    end

    return true
end

function accept(prob)
    if prob.rc > 0
    then
        return false
    end

    if  reject(prob)
    then
        return false
    end

    return true
end

function output(prob)
    print("done")
end

function first(prob)
    out = prob
    for i=1, out.y + out.rs
    do
        for j=1, out.x + out.rs
        do
            print(string.format("%d, %d", j, i))
            out.mat[i][j] = out.mat[i][j] + 1
        end
    end
    return out
end

function next(prob)
    out = prob
    for i=out.x, out.x + out.rs
    do
        for j=out.y, out.y+out.rs
        do
            out.mat[i][j] = out.mat[i][j] - 1
        end
    end

    out.x = out.x + 1
    if out.x == out.rs
    then
        out.x = 0
        out.y = out.y + 1
    end

    for i=1, #out.mat - out.rs
    do
        for j=1,#out.mat[i] - out.rs
        do
            out.mat[i][j] = out.mat[i][j] + 1
        end
    end
end

problem = {}
generate(problem)
