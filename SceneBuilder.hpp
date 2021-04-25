//
// Created by Will Chambers on 4/24/21.
//

#ifndef LUDUMDAREAPRIL2021_SCENEBUILDER_HPP
#define LUDUMDAREAPRIL2021_SCENEBUILDER_HPP
#include"willow/root/Root.hpp"
#include"willow/rendering/Scene.hpp"
#include"willow/Assets.hpp"
#include"willow/scripting/LuaBinding.hpp"
#include"Maze.hpp"
#include<array>
class SceneBuilder {
    wlo::Assets &m_assets;
    std::map<std::string, wlo::MaterialHandle> m_loadedMaterials;
    wlo::rendering::Scene m_builtScene;
    std::vector<wlo::MaterialHandle> m_CurCubeMaterials;
    wlo::Vec3 curCubePosition = {0,0,0};

    void startNewCube(wlo::Vec3 BLF);
    void addCubePanel(std::string texturePath);
    void finalizeCube();

    size_t panelsInCurCube = 0;


public:
    explicit SceneBuilder(wlo::Assets &);
    wlo::rendering::Scene build(rh::Maze & maze);


};


#endif //LUDUMDAREAPRIL2021_SCENEBUILDER_HPP
