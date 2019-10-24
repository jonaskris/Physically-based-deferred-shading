#include <iostream>
#include <Model.h>
#include <Camera.h>

class Scene
{ 
private:
    std::vector<Camera*> cameras;
    std::vector<Model*> models;

protected:
    template<typename SceneComponent>
    void unpackSceneComponents(SceneComponent* sceneComponent)
    {
        static_assert(std::is_base_of<Model, SceneComponent>::value || std::is_base_of<Camera, SceneComponent>::value, "SceneComponent must be of type Model or Camera!");
    
        if constexpr (std::is_base_of<Model, SceneComponent>::value) {
            models.push_back(sceneComponent);
        } else if (std::is_base_of<Camera, SceneComponent>::value) {
            cameras.push_back(sceneComponent);
        }
    }

    template<typename SceneComponent, typename... SceneComponents> 
    void unpackSceneComponents(SceneComponent* sceneComponent, SceneComponents*... sceneComponents)
    {
        static_assert(std::is_base_of<Model, SceneComponent>::value || std::is_base_of<Camera, SceneComponent>::value, "SceneComponent must be of type Model or Camera!");
    
        if constexpr (std::is_base_of<Model, SceneComponent>::value) {
            models.push_back(sceneComponent);
        } else if (std::is_base_of<Camera, SceneComponent>::value) {
            cameras.push_back(sceneComponent);
        }

        unpackSceneComponents(sceneComponents...);
    }

public:
    template<typename... SceneComponents>
    Scene(SceneComponents*... sceneComponents)
    {
        if constexpr (sizeof...(SceneComponents) > 0)
            unpackSceneComponents(sceneComponents...);
    };

    void draw();
};