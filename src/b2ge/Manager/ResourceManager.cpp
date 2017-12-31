//
// Created by brd6 on 25/11/17.
//

#include "b2ge/Manager/ResourceManager.hpp"

namespace b2ge
{
  sf::Texture &ResourceManager::getTexture(std::string const &name)
  {
    auto it = mResourceTextures.find(name);

    if (it != std::end(mResourceTextures))
      return *(it->second);

    auto resource = new sf::Texture();

    if (!resource->loadFromFile(name))
      throw std::runtime_error("Unable to load '" + name + "' resource.");

    std::unique_ptr<sf::Texture> resourcePtr(resource);

    mResourceTextures[name] = std::move(resourcePtr);
    return *resource;
  }

  sf::Font &ResourceManager::getFont(std::string const &name)
  {
    auto it = mResourceFonts.find(name);

    if (it != std::end(mResourceFonts))
      return *(it->second);

    auto resource = new sf::Font();

    if (!resource->loadFromFile(name))
      throw std::runtime_error("Unable to load '" + name + "' resource.");

    std::unique_ptr<sf::Font> resourcePtr(resource);

    mResourceFonts[name] = std::move(resourcePtr);
    return *resource;
  }

  sf::SoundBuffer &ResourceManager::getSoundBuffer(std::string const &name)
  {
    auto it = mResourceSoundBuffers.find(name);

    if (it != std::end(mResourceSoundBuffers))
      return *(it->second);

    auto resource = new sf::SoundBuffer();

    if (!resource->loadFromFile(name))
      throw std::runtime_error("Unable to load '" + name + "' resource.");

    std::unique_ptr<sf::SoundBuffer> resourcePtr(resource);

    mResourceSoundBuffers[name] = std::move(resourcePtr);
    return *resource;
  }

  sf::Music &ResourceManager::getMusic(std::string const &name)
  {
    auto it = mResourceMusics.find(name);

    if (it != std::end(mResourceMusics))
      return *(it->second);

    auto resource = new sf::Music();

    if (!resource->openFromFile(name))
      throw std::runtime_error("Unable to load '" + name + "' resource.");

    std::unique_ptr<sf::Music> resourcePtr(resource);

    mResourceMusics[name] = std::move(resourcePtr);
    return *resource;
  }

  sf::Image &ResourceManager::getImage(std::string const &name)
  {
    auto it = mResourceImages.find(name);

    if (it != std::end(mResourceImages))
      return *(it->second);

    auto resource = new sf::Image();

    if (!resource->loadFromFile(name))
      throw std::runtime_error("Unable to load '" + name + "' resource.");

    std::unique_ptr<sf::Image> resourcePtr(resource);

    mResourceImages[name] = std::move(resourcePtr);
    return *resource;
  }

  ResourceManager *ResourceManager::getInstance()
  {
    static ResourceManager instance;

    return &instance;
  }
}