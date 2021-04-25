#include<string>
#include<unordered_map>
#include"willow/root/Root.hpp"
#pragma once
namespace rh{
	//k-ary tree with parent pointers, most will have 8 children, null children will be a concrete extension of nodes;
	enum class Direction : size_t{
		Forward =0 , Backward, Left, Right, Up, Down
	};
	class Maze{
	public:
		struct Node{
			wlo::Vec3 center;
			std::string texturePath;
		};

		class NodeHandle{
		public:
		    NodeHandle();
			NodeHandle(Maze*, size_t);
			Node& get();
		private:
			friend class Maze;
			Maze* owner;
			size_t index;
		};

		friend class NodeHandle;
		Maze() = default;
		
		void addEdge(NodeHandle n1, Direction dir, NodeHandle n2);
		NodeHandle setRoot( wlo::Vec3 center,std::string texturePath);
		NodeHandle addNode(std::string texturePath);
		NodeHandle fetch(NodeHandle cur, Direction);
		NodeHandle fetch(size_t id);
		const std::vector<Node> & getNodes();

	private:
        wlo::Vec3 nextNodePosition();
		std::vector<Node> m_nodes;
		std::unordered_map<size_t, std::unordered_map<Direction, size_t> > Adj;
	
	};

}