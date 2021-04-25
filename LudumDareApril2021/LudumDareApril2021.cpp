// LudumDareApril2021.cpp : Defines the entry point for the application.
//

#include "willow.hpp"
#include "Maze.hpp"
using namespace std;
using namespace wlo;
using namespace rh;
class RabbitHole : public wlo::Application{
	Maze maze;
	rendering::Scene startScene;
	
public:

	RabbitHole(std::string argv_0) :Application(Application::Info{ .appName = "RabbitHole",.windowDimensions = {800,800} }, argv_0) {}
	
	void setup() override {
		startScene.add(m_assets.TexturedQuad().get(),)
	};
    void stepSim(float elapsedTime) override {};
    void draw() override {};

};



int main(int argc, char *  argv[])
{
	UniquePointer<Application> gameInstance = CreateUniquePointer<RabbitHole>(argv[0]);
	gameInstance->run();
}
