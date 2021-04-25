//
// Created by Will Chambers on 4/25/21.
//

#include "CollisionGraph.hpp"

void rh::CollisionGraph::track(rh::Maze &maze){
    m_maze = & maze;
}

void rh::CollisionGraph::tick(glm::vec3 newPos) {
    m_trackedPosition = newPos;
    if(collidingWithEdge())
        Messenger::asSubject().notify(exitDirection());
}
float distance(wlo::Vec3 v0, wlo::Vec3 v1){
    return (v0-v1).length();
}
//iterates over all node centers, returns a handle to the nearest one
rh::Maze::NodeHandle rh::CollisionGraph::getCurNode() {
    return m_curNode;
}

bool rh::CollisionGraph::collidingWithEdge() {
    return
    (m_trackedPosition.x > getCurNode().get().center.x +.5)||
    (m_trackedPosition.x < getCurNode().get().center.x -.5)||
    (m_trackedPosition.y > getCurNode().get().center.y +.5)||
    (m_trackedPosition.y < getCurNode().get().center.y -.5)||
    (m_trackedPosition.z > getCurNode().get().center.z +.5)||
    (m_trackedPosition.z < getCurNode().get().center.z -.5);
}

rh::Direction rh::CollisionGraph::exitDirection() {
   if (m_trackedPosition.x > getCurNode().get().center.x +.5)
       return Direction::Right;
    if(m_trackedPosition.x < getCurNode().get().center.x -.5)
        return Direction::Left;
    if(m_trackedPosition.y > getCurNode().get().center.y +.5)
        return Direction::Up;
    if(m_trackedPosition.y < getCurNode().get().center.y -.5)
        return Direction::Down;
    if(m_trackedPosition.z > getCurNode().get().center.z +.5)
        return Direction::Left;
    if(m_trackedPosition.z < getCurNode().get().center.z -.5)
        return Direction::Right;
    else{
        throw std::logic_error("No exit direction, player is within cube bounds, call exit direction only if there is a collision ");
    }
}

void rh::CollisionGraph::setCurNode(rh::Maze::NodeHandle next) {
    m_curNode = next;
}
