//
// Created by brd6 on 25/11/17.
//

#ifndef B2GE_RESOURCEMANAGER_HPP
#define B2GE_RESOURCEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <memory>

namespace b2ge
{
    class ResourceManager
    {
    private:
        std::map<std::string, std::unique_ptr<sf::Texture>> mResourceTextures;
        std::map<std::string, std::unique_ptr<sf::Font>> mResourceFonts;
        std::map<std::string, std::unique_ptr<sf::SoundBuffer>> mResourceSoundBuffers;
        std::map<std::string, std::unique_ptr<sf::Music>> mResourceMusics;
        std::map<std::string, std::unique_ptr<sf::Image>> mResourceImages;

    private:
        ResourceManager() = default;

    public:
        ~ResourceManager() = default;

        // delete
        ResourceManager(ResourceManager const &) = delete;
        ResourceManager &operator=(ResourceManager const &) = delete;

        sf::Texture &getTexture(std::string const &name);
        sf::Font &getFont(std::string const &name);
        sf::SoundBuffer &getSoundBuffer(std::string const &name);
        sf::Music &getMusic(std::string const &name);
        sf::Image &getImage(std::string const &name);

        static ResourceManager *getInstance();

    };
}

#endif //B2GE_RESOURCEMANAGER_HPP
