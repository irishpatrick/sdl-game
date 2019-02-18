tools = {}

function tools.generate_matrix(N,M)
    mat = {}
    for i=1,N do
        mat[i] = {}
        for j=1,M do
            mat[i][j] = 0
        end
    end
end

return tools
