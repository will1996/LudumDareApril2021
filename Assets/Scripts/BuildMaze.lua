--
-- Created by IntelliJ IDEA.
-- User: w
-- Date: 4/25/21
-- Time: 9:44 AM
-- To change this template use File | Settings | File Templates.
--
Dir= {
   Forward =0,
   Backward = 1,
    Left = 2,
    Right = 3,
    Up = 4,
   Down = 5
}

-- linear maze, with a loop at the end
easyMaze ={
   start = {pos = {x=0.0,y=0.0,z=0.0},
            texture = "whiteTexture.png",
            adj = {{texture = "cow.bmp",direction = Dir.Forward}} },
    nodes = {
    {texture = "kit.jpeg",adj = {{parent = 2,direction = Dir.Forward}}},
    {texture = "cow.bmp",adj = {{parent = 0,direction = Dir.Forward}}},
    }
}

function buildMaze(mazeDesc)
    Maze:start(mazeDesc.start.pos,mazeDesc.texture)
    for node in pairs(mazeDesc.start.adj) do
        Maze:addNode()
        end

end


Maze:start({x=0.0,y=0.0,z=0.0},"whiteTexture.png")
Maze:addNode("cow.bmp")
Maze:addNode("kit.jpeg")
Maze:addEdge(0,Dir.Right,2);
