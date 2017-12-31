//
// Created by brd6 on 25/11/17.
//

#include "b2ge/Manager/SceneManager.hpp"

namespace b2ge
{
  SceneManager::SceneManager() :
   mCurrentSceneIndex(0),
   mNextSceneIndex(0),
   mIsSceneLocked(false),
   mChangeSceneAtNextFrame(false)
  {
  }

  /**
   * Add a scene to the sceneManager
   * @param scene
   */
  void SceneManager::add(std::string const &name, Scene *scene)
  {
    std::unique_ptr<Scene> scenePtr{scene};

    scene->mName = name;
    scene->mSceneManager = this;

    mScenes.emplace_back(std::move(scenePtr));

    if (mScenes.size() == 1)
      setStart(name);
  }

  Scene& SceneManager::getCurrent()
  {
    if (!isValidSceneIndex(mCurrentSceneIndex))
      throw std::out_of_range("Scene index is not correct");

    return *mScenes[mCurrentSceneIndex];
  }

  void SceneManager::setStart(std::string const &sceneName)
  {
    change(sceneName);
    //doChangeScene();
  }

  void SceneManager::change(std::string const &sceneName)
  {
    auto it = std::find_if(std::begin(mScenes), std::end(mScenes),
			   [sceneName](std::unique_ptr<Scene> const &scene) {
			     return scene->getName() == sceneName;
			   });

    if (it == std::end(mScenes))
      throw std::invalid_argument("Scene name not found");

    mNextSceneIndex = (unsigned int)(it - std::begin(mScenes));
    mChangeSceneAtNextFrame = true;
  }

  bool SceneManager::isValidSceneIndex(unsigned int sceneIndex) const
  {
    return (sceneIndex >= 0 && sceneIndex < mScenes.size());
  }

  void SceneManager::lock()
  {
    if (mChangeSceneAtNextFrame && !mIsSceneLocked)
      {
	doChangeScene();
	mChangeSceneAtNextFrame = false;
      }
    mIsSceneLocked = true;
  }

  void SceneManager::unlock()
  {
    mIsSceneLocked = false;
  }

  void SceneManager::doChangeScene()
  {
    // destroy current scene if possible
    if (isValidSceneIndex(mCurrentSceneIndex))
      getCurrent().destroy();

    // create new scene
    mCurrentSceneIndex = mNextSceneIndex;

    getCurrent().initialize();
  }

  void SceneManager::processEvents(sf::Event event)
  {
    Scene &currentScene = getCurrent();

    currentScene.executeProcessEvents(event);
  }

  void SceneManager::update(float deltaTime)
  {
    auto &currentScene = getCurrent();

    currentScene.update(deltaTime);
  }
}
