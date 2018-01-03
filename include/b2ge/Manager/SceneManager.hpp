//
// Created by brd6 on 25/11/17.
//

#ifndef B2GE_SCENEMANAGER_HPP
#define B2GE_SCENEMANAGER_HPP

#include <unordered_map>
#include <functional>
#include "b2ge/Core/Scene.hpp"
#include <b2ge/Util/Debug.hpp>
#include <deque>

namespace b2ge
{
  class SceneManager
  {
   private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> mScenes;
    std::string mCurrentSceneName;
    std::string mNextSceneName;
    bool mIsSceneLocked;
    bool mChangeSceneAtNextFrame;
    std::unordered_map<std::string, std::function<Scene::Ptr ()>> mSceneFactories;

   public:
    SceneManager();
    ~SceneManager() = default;

    SceneManager(SceneManager const &) = delete;
    SceneManager &operator=(SceneManager const &) = delete;

    template<typename TScene>
    void add(std::string const &name)
    {
      if (!std::is_base_of<Scene, TScene>::value)
	throw std::logic_error(name + " must be a scene");

      mSceneFactories[name] = [name, this]() {

	TScene *scene(new TScene());

	scene->mName = name;
	scene->mSceneManager = this;

	std::unique_ptr<TScene> scenePtr{scene};

	mScenes[name] = std::move(scenePtr);

	if (mScenes.size() == 1)
	  setStart(name);

	return scenePtr;

      };

      mSceneFactories[name]();
    }

    Scene &getCurrent();

    void lock();
    void unlock();

    void setStart(std::string const &sceneName);
    void change(std::string const &sceneName);

    void processEvents(sf::Event event);
    void update(float deltaTime);

    void destroy();

   private:
    bool isValidSceneName(std::string const &name) const;
    void doChangeScene();
    Scene::Ptr createScene(std::string const &name);
    void destroyScene(std::string const &name);
  };
}

#endif //B2GE_SCENEMANAGER_HPP
