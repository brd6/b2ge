//
// Created by brd6 on 25/11/17.
//

#include "b2ge/Manager/SceneManager.hpp"

namespace b2ge
{
  SceneManager::SceneManager() :
   mIsSceneLocked(false),
   mChangeSceneAtNextFrame(false)
  {
  }

  Scene& SceneManager::getCurrent()
  {
    if (!isValidSceneName(mCurrentSceneName))
      throw std::out_of_range("Scene name is not correct");

    return *mScenes[mCurrentSceneName];
  }

  void SceneManager::setStart(std::string const &sceneName)
  {
    change(sceneName);
    //doChangeScene();
  }

  void SceneManager::change(std::string const &sceneName)
  {
    mNextSceneName = sceneName;
    mChangeSceneAtNextFrame = true;
  }

  bool SceneManager::isValidSceneName(std::string const &name) const
  {
    return mScenes.count(name) > 0;
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
//    destroyCurrentScene();

    if (isValidSceneName(mCurrentSceneName))
      getCurrent().onExit();

    auto prevSceneName = mCurrentSceneName;
    mCurrentSceneName = mNextSceneName;

    getCurrent().initialize();

    getCurrent().onEnter();

    destroyScene(prevSceneName);
  }

  void SceneManager::processEvents(sf::Event event)
  {
    Scene &currentScene = getCurrent();

    currentScene.executeProcessEvents(event);
  }

  void SceneManager::update(float deltaTime)
  {
    auto &currentScene = getCurrent();

    currentScene.executeUpdate(deltaTime);
  }

  void SceneManager::destroy()
  {
//    destroyScene(mCurrentSceneIndex);
//    destroyCurrentScene();
  }

  Scene::Ptr SceneManager::createScene(const std::string &name)
  {
    if (mSceneFactories.count(name) <= 0)
      throw std::logic_error("Scene " + name + " not found");

    return mSceneFactories[name]();
  }

  void SceneManager::destroyScene(std::string const &name)
  {
    if (!isValidSceneName(name))
      return;

    getCurrent().destroy();
  }
}
