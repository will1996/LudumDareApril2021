#include"Maze.hpp"


namespace rh{
	Maze::NodeHandle Maze::setRoot(wlo::rendering::Scene s, wlo::Vec3 BLF )
	{
		if (m_nodes.size() == 0)
			m_nodes.push_back(Node{ .scene = s, .BLF = BLF });
		else
			m_nodes[0] = Node{ .scene = s, .BLF = BLF };

		return NodeHandle(this, 0);
	}

	void Maze::addEdge(NodeHandle n1,Direction dir, NodeHandle n2)
	{
		Adj[n1.index][dir] = n2.index;
	}

	Maze::NodeHandle Maze::addNode(wlo::rendering::Scene s, wlo::Vec3 BLF, NodeHandle parent, Direction dir)
	{
		size_t index = m_nodes.size();
		m_nodes.push_back(Node{ .scene = s, .BLF = BLF });
		Adj[parent.index][dir] = index;

		return NodeHandle(this, index);
	}

	Maze::NodeHandle Maze::fetch(NodeHandle cur, Direction dir){
		return NodeHandle(  this,   Adj[cur.index][dir] );
	}
	
	Maze::NodeHandle::NodeHandle(Maze* o, size_t i ):owner(o),index(i)
	{
	}

	Maze::Node& Maze::NodeHandle::get()
	{
		return owner->m_nodes[index];
	}

}