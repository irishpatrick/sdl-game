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
        print("reject")
        return
    end

    if accept(prob)
    then
        print("accept")
        output(prob)
    end

    print("generate first")
    local s = first(prob)

    while s ~= nil
    do
        print("backtrace")
        backtrace(s)
        print("next")
        s = next(s)
    end
    prob.rc = prob.rc - 1
end

function reject(prob)
    for i=1,#prob.mat
    do
        for j=1,#prob.mat[i]
        do
            if prob.mat[i][j] > 1
            then
                return true
            end
        end
    end

    return false
end

function accept(prob)
    if prob.rc > 0
    then
        return false
    end

    if reject(prob)
    then
        return false
    end

    return true
end

function output(prob)
    print("done")
end

function first(prob)
    local out = prob
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
    local out = prob

    for i=out.y, out.y + out.rs
    do
        for j=out.x, out.x + out.rs
        do
            print(string.format("%d, %d", out.x, out.y))
            out.mat[i][j] = out.mat[i][j] - 1
        end
    end

    out.x = out.x + 1
    if out.x >= #out.mat[1] - out.rs
    then
        out.x = 1
        out.y = out.y + 1
    end

    if out.y >= #out.mat - out.rs
    then
        return nil
    end

    for i=out.y, out.y + out.rs
    do
        for j=out.x, out.x + out.rs
        do
            out.mat[i][j] = out.mat[i][j] + 1
        end
    end

    return out
end

local problem = {}
generate(problem)
