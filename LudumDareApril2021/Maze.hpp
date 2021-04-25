#include<string>
#include<unordered_map>
#include"willow/root/Root.hpp"
#include"willow/rendering/Scene.hpp"

namespace rh{
	//k-ary tree with parent pointers, most will have 8 children, null children will be a concrete extension of nodes;
	enum class Direction : size_t{
		Forward, Backward, Left, Right, Up, Down	
	};
	class Maze{
	public:
		struct Node{
			wlo::rendering::Scene scene;
			wlo::Vec3 BLF;
		};

		class NodeHandle{
		public:
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
		NodeHandle setRoot(wlo::rendering::Scene, wlo::Vec3 BL);
		NodeHandle addNode(wlo::rendering::Scene, wlo::Vec3 BL, NodeHandle parent,Direction Dir);
		NodeHandle fetch(NodeHandle cur, Direction);

	private:

		std::vector<Node> m_nodes;
		std::unordered_map<size_t, std::unordered_map<Direction, size_t> > Adj;
	
	};

}