//
// Created by Will Chambers on 4/25/21.
//

#include "MazeBuilder.hpp"
using namespace rh;
void MazeBuilder::startMaze(wlo::Vec3 origin, std::string texturePath) {
    m_maze.setRoot(origin, std::move(texturePath));
}

void MazeBuilder::AddNode(std::string texturePath) {
    WILO_CORE_INFO("Adding node with texture: {0}",texturePath);
    m_maze.addNode(std::move(texturePath));
}


void MazeBuilder::AddEdge(int n0, int direction, int n1) {
        m_maze.addEdge(m_maze.fetch(n0),Direction(direction),m_maze.fetch(n1));
}

MazeBuilder::MazeBuilder(wlo::ScriptEnvironment & env):m_scriptBinding("Maze", this, env) {
    m_scriptBinding.Register<wlo::Vec3, std::string,&MazeBuilder::startMaze> ("start");
    m_scriptBinding.Register<std::string,&MazeBuilder::AddNode> ("addNode");
    m_scriptBinding.Register<int, int, int,&MazeBuilder::AddEdge> ("addEdge");
}

rh::Maze MazeBuilder::build(wlo::Vec3 mazeOrigin) {
    m_scriptBinding.getEnv().runScript(wlo::FileSystem::Script("BuildMaze.lua"));
    return m_maze;
}


