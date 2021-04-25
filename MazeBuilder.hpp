//
// Created by Will Chambers on 4/25/21.
//

#ifndef LUDUMDAREAPRIL2021_MAZEBUILDER_HPP
#define LUDUMDAREAPRIL2021_MAZEBUILDER_HPP
#include"willow/scripting/LuaBinding.hpp"
#include"Maze.hpp"
class MazeBuilder {
    wlo::LuaBinding<MazeBuilder> m_scriptBinding;
    rh::Maze m_maze;
    void startMaze(wlo::Vec3 origin, std::string texturePath);
    void AddNode(std::string texturePath);
    void AddEdge(int n0, int direction, int n1);
public:
    MazeBuilder(wlo::ScriptEnvironment& env);
    rh::Maze build(wlo::Vec3 MazeOrigin);
};


#endif //LUDUMDAREAPRIL2021_MAZEBUILDER_HPP
