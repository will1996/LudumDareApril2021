// LudumDareApril2021.cpp : Defines the entry point for the application.
//

#include "willow.hpp"
#include "Maze.hpp"
#include"SceneBuilder.hpp"
#include"MazeBuilder.hpp"
#include"CollisionGraph.hpp"
using namespace std;
using namespace wlo;
using namespace rh;
class RabbitHole : public wlo::Application{
	Maze maze;
	rendering::Scene m_scene;
	std::unordered_map<std::string, TextureHandle> textures;
    std::unordered_map<std::string, MaterialHandle> materials;
    wlo::LuaBinding<RabbitHole> m_scriptBinding;
    SceneBuilder sceneBuilder;
    MazeBuilder mazeBuilder;
    CollisionGraph collisionGraph;
    Maze map;


    float m_cameraSpeed;
    void setCameraSpeed(float speed){
        m_cameraSpeed = speed;
    }
    void handleMouse(const wlo::MouseMoved& msg) {
        m_mainCamera.look(msg.content.xPos,msg.content.yPos);
    }


public:

	RabbitHole(std::string argv_0) :Application(
	        Application::Info{ .appName = "RabbitHole",.windowDimensions = {800,800} }, argv_0) ,
	m_scriptBinding("Game",this,m_scriptEnv),
	sceneBuilder(m_assets),
	mazeBuilder(m_scriptEnv)
	{
        m_mainWindow.permit<wlo::MouseMoved,RabbitHole,&RabbitHole::handleMouse>(this);
        m_scriptBinding.Register<float,&RabbitHole::setCameraSpeed>("setCameraSpeed");
        collisionGraph.permit<Direction,RabbitHole,& RabbitHole::setPlayerToNewNode>(this);
    }

    void setPlayerToNewNode(const Direction & dir) {
        auto lastNode = collisionGraph.getCurNode();
        Maze::NodeHandle curNode = map.fetch(lastNode, dir);
        collisionGraph.setCurNode(curNode);
        m_mainCamera.setPosition(curNode.get().center);
    }


	void setup() override {
        map = mazeBuilder.build({0,0,0});
        m_scene = sceneBuilder.build(map);
        collisionGraph.setCurNode(map.fetch(0));
        collisionGraph.track(map);
        m_renderer.preAllocateScene(m_scene.getDescription());
        m_renderer.setClearColor({{0,0,0,1}});
        m_input.setKeyMap({
            {"Forward",wlo::Key::Code::W},
            {"Backward",wlo::Key::Code::S},
            {"Left",wlo::Key::Code::A},
            {"Right",wlo::Key::Code::D},
            {"Reset",wlo::Key::Code::SPACE}
        });
        m_mainWindow.setCursorMode(true);
        m_mainCamera.setPosition({0,0,0});
        setCameraSpeed(1.0f);
	};
    void stepSim(float elapsedTime) override {

        collisionGraph.tick(m_mainCamera.getPosition());

       if(m_input.isPressed("Forward"))
           m_mainCamera.moveAlongViewAxis(elapsedTime*m_cameraSpeed);
        if(m_input.isPressed("Backward"))
            m_mainCamera.moveAlongViewAxis(-elapsedTime*m_cameraSpeed);
        if(m_input.isPressed("Left"))
            m_mainCamera.strafe(elapsedTime*m_cameraSpeed);
        if(m_input.isPressed("Right"))
            m_mainCamera.strafe(-elapsedTime*m_cameraSpeed);
        if(m_input.isPressed("Reset"))
            m_mainCamera.setPosition({0,0,0});

    };
    void draw() override {
        m_renderer.render(m_scene);
    };

};



int main(int argc, char *  argv[])
{
	UniquePointer<Application> gameInstance = CreateUniquePointer<RabbitHole>(argv[0]);
	gameInstance->run();
}
