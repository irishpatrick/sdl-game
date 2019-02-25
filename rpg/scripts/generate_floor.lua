#!/usr/local/bin/lua

local tools = require("tools")

function print_problem(p)
    local m = p.mat
    for i, #m
    do
        for j, #m[i]
        do
            print(m[i][j])
        end
        print("")
    end
end

function generate()
    init(problem)
    print_problem(problem)
    backtrace(problem)
end

problem = {}

function init(prob)
    prob.mat = tools.generate_matrix(100, 100)
    prob.last = prob.mat
    prob.rc = 4
    prob.rs = 6
    prob.x = 0
    prob.y = 0
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
    if prob.rc ~= 0
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
    for i=0,out.rs
    do
        for j=0,out.rs
        do
            out.mat[i][j] = out.mat[i][j]+1
        end
    end
end

function next(prob)
    out = prob
    for i=x,x + out.rs
    do
        for j=y,y+out.rs
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

    for i=0,#out.mat - out.rs
    do
        for j=0,#out.mat[i] - out.rs
        do
            out.mat[i][j] = out.mat[i][j] + 1
        end
    end
end

generate()