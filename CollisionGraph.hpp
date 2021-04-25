//
// Created by Will Chambers on 4/25/21.
//

#ifndef LUDUMDAREAPRIL2021_COLLISIONGRAPH_HPP
#define LUDUMDAREAPRIL2021_COLLISIONGRAPH_HPP
#include"Maze.hpp"
#include"willow/messaging/MessageSystem.hpp"
namespace rh {
class CollisionGraph :public wlo::Messenger{
    public:
        CollisionGraph() = default;
        void track (Maze &maze);
        //tick will use the internal functions to find the next node, as well as determine the entry point of the player
        void tick(wlo::Vec3 newPos);//check state, emit messages if something interesting is happening
        Maze::NodeHandle getCurNode();
        void setCurNode(Maze::NodeHandle next);
        //is the current position colliding with an edge of the current node?

    bool collidingWithEdge();
    //then determine the exit direction
    Direction exitDirection();
    private:
        Maze *m_maze;
        wlo::Vec3 m_trackedPosition;
    std::vector<wlo::Vec3> m_cubeNormals;
    Maze::NodeHandle m_curNode;

    };
}


#endif //LUDUMDAREAPRIL2021_COLLISIONGRAPH_HPP
