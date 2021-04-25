//
// Created by Will Chambers on 4/24/21.
//

#include "SceneBuilder.hpp"
using namespace wlo;
SceneBuilder::SceneBuilder(wlo::Assets &assets):m_assets(assets) {
}


void SceneBuilder::startNewCube(wlo::Vec3 BLF) {
    curCubePosition = BLF;
    panelsInCurCube = 0;
    WILO_CORE_INFO("Starting New Cube with starting position: {0}",glm::to_string(BLF));
    m_CurCubeMaterials.clear();
}

void SceneBuilder::addCubePanel(std::string texturePath) {
    if(panelsInCurCube>=6){
        WILO_CORE_ERROR("FAILED TO BUILD SCENE CUBE, TOO MANY PANELS IN CUR");
        exit(-1);
    }

    WILO_CORE_INFO("New Panel with texture: {0}",texturePath);
    if(!m_loadedMaterials.contains(texturePath)) {
        auto tex = m_assets.loadTexture(FileSystem::Texture(texturePath));
        m_loadedMaterials[texturePath] = m_assets.loadMaterial(tex.id,
        FileSystem::Shader("shader.vert").string(),
                FileSystem::Shader("shader.frag").string());
    }
    m_CurCubeMaterials.push_back(m_loadedMaterials[texturePath]);
}

wlo::Mat4 panelRotation(wlo::Vec3 origin,wlo::Vec3 rAxis,wlo::Vec3 tAxis,float angle = 180.0f){
    return glm::translate(glm::mat4{1},.5f*tAxis+origin)*glm::rotate(glm::mat4{1},glm::radians(angle),rAxis);
}

wlo::Mat4 panelTransform(wlo::Vec3 BLF, size_t index){
   switch(index) {
       case 1:{ return glm::translate(glm::mat4{1},BLF+glm::vec3{0,0,-.5}); }//back
       case 0:{ return panelRotation(BLF,{0,1,0},{0,0,1});}//front
       case 2:{ return panelRotation(BLF,{1,0,0},{0,1,0},90.0f);}//top
       case 3:{ return panelRotation(BLF,{1,0,0},{0,-1,0},-90.0f);}//bottom
       case 4:{ return panelRotation(BLF,{0,1,0},{-1,0,0},90.0f);}//left
       case 5:{ return panelRotation(BLF,{0,1,0},{1,0,0},-90.0f);}//left
       default:{
           WILO_CORE_ERROR("invalid panEL INDEX TO TRANSFORM")
           exit(-1);
       }

   }

};

void SceneBuilder::finalizeCube() {
    WILO_CORE_INFO("FINALIZING CUBE")

    std::vector<std::vector<wlo::Vec2>> texCoords = {
            {{0,.5},{1.0/3,.5},{1.0/3,1},{0,1}},//forward (0)
            {{0,0},{1.0/3,0},{1.0/3,.5},{0,.5}},//backward (1)
            {{1.0/3,.5},{2.0/3,.5},{2.0/3,1},{1.0/3,1}},//left (2)
            {{1.0/3,0},{2.0/3,0},{2.0/3,.5},{1.0/3,.5}},//right (3)
            {{2.0/3,.5},{1,.5},{1,1},{2.0/3,1}},//up (4)
            {{2.0/3,0},{1,0},{1,.5},{2.0/3,.5}}//down (5)
    };
    size_t i =0;
    for(auto & mat : m_CurCubeMaterials) {
        m_builtScene.add(m_assets.TexturedQuad(texCoords[i]).get(), mat.get(), panelTransform(curCubePosition, i));
        i++;
    }
}

wlo::rendering::Scene SceneBuilder::build(rh::Maze &maze) {
    for(auto & node : maze.getNodes()){
        startNewCube(node.center);
        for(size_t i =0; i < 6; i++)
            addCubePanel(node.texturePath);
        finalizeCube();
    }
    return m_builtScene;
}
