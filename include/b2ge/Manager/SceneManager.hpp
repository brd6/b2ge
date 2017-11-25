//
// Created by brd6 on 25/11/17.
//

#ifndef B2GE_SCENEMANAGER_HPP
#define B2GE_SCENEMANAGER_HPP

#include <unordered_map>
#include "b2ge/Core/Scene.hpp"

namespace b2ge
{
  class SceneManager
  {
   private:
    std::vector<std::unique_ptr<Scene>> mScenes;
    unsigned int mCurrentSceneIndex;
    unsigned int mNextSceneIndex;
    bool mIsSceneLocked;
    bool mChangeSceneAtNextFrame;

   public:
    SceneManager();
    ~SceneManager() = default;

    SceneManager(SceneManager const &) = delete;
    SceneManager &operator=(SceneManager const &) = delete;

    void add(std::string const &name, Scene *scene);

    Scene &getCurrent();

    void lock();
    void unlock();

    void setStart(std::string const &sceneName);
    void change(std::string const &sceneName);

    void processEvents(sf::Event event);
    void update(float d);
   private:
    bool isValidSceneIndex(unsigned int sceneIndex) const;
    void doChangeScene();
  };
}

#endif //B2GE_SCENEMANAGER_HPP
