#include"Maze.hpp"


namespace rh{
    wlo::Vec3 direction(Direction dir)	{
        switch(dir){
            case Direction::Forward:
                return {0,0,1};
            case Direction::Backward:
                return {0,0,-1};
            case Direction::Up:
                return {0,1,0};
            case Direction::Down:
                return {0,-1,0};
            case Direction::Left:
                return {-1,0,0};
            case Direction::Right:
                return {1,0,0};
        }
    }
    std::string dirName(Direction dir ) {
        switch (dir) {
            case Direction::Forward:
                return "Forward";
            case Direction::Backward:
                return "Backward";
            case Direction::Up:
                return "Up";
            case Direction::Down:
                return "Down";
            case Direction::Left:
                return "Left";
            case Direction::Right:
                return "Right";
        }
    }
	Maze::NodeHandle Maze::setRoot( wlo::Vec3 center ,std::string texturePath)
	{
		if (m_nodes.empty())
			m_nodes.push_back(Node{  .center = center ,.texturePath = std::move(texturePath)});
		else
			m_nodes[0] = Node{ .center = center };
		return NodeHandle(this, 0);
	}

	void Maze::addEdge(NodeHandle n1,Direction dir, NodeHandle n2)
	{
	    WILO_CORE_INFO("Adding an edge from {0} to {1} in the {2} direction", n1.index,n2.index,dirName(dir));
		Adj[n1.index][dir] = n2.index;
	}


	Maze::NodeHandle Maze::addNode(  std::string texturePath)
	{
		size_t index = m_nodes.size();
		m_nodes.push_back(Node{ .center = nextNodePosition(),.texturePath = std::move(texturePath)});
		return NodeHandle(this, index);
	}

	Maze::NodeHandle Maze::fetch(NodeHandle cur, Direction dir){
	    WILO_CORE_INFO("Fetching child in the {0} direction from node with id: {1}",dirName(dir),cur.index);
        if(Adj[cur.index].contains(dir)) {//if an edge exists in this direction
            WILO_CORE_INFO("found child with index {0}, returning...",Adj[cur.index][dir]);
            return NodeHandle(this, Adj[cur.index][dir]);
        }else{
            WILO_CORE_INFO("No child found, returning cur node");
           return cur ;
        }
	}

    Maze::NodeHandle Maze::fetch(size_t id) {
	    assert(id<m_nodes.size());
	    return NodeHandle(this,id);
    }

    const std::vector<Maze::Node> &Maze::getNodes() {
	    return m_nodes;
    }

    wlo::Vec3 Maze::nextNodePosition() {
	    float nodeCount = m_nodes.size();
	   wlo::Vec3  rootPos = m_nodes[0].center;
	    return rootPos+nodeCount*direction(Direction::Forward) ;
    }


    Maze::NodeHandle::NodeHandle(Maze* o, size_t i ):owner(o),index(i)
	{
	}

	Maze::Node& Maze::NodeHandle::get()
	{
		return owner->m_nodes[index];
	}

    Maze::NodeHandle::NodeHandle():owner(nullptr),index(-1) {

    }

}