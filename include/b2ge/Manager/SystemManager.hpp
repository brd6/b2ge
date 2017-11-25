//
// Created by brd6 on 30/08/2017.
//

#ifndef B2GE_SYSTEMMANAGER_HPP
#define B2GE_SYSTEMMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include "b2ge/Core/System.hpp"
#include "b2ge/Core/SystemUpdatable.hpp"
#include "b2ge/Core/SystemDrawable.hpp"
#include "b2ge/Core/SystemEventable.hpp"

namespace b2ge
{
  class World;

  class SystemManager
  {
   private:
    friend class World;

    using SystemPtr = std::unique_ptr<System>;

    std::unordered_map<SystemId, SystemPtr> mSystems;

    std::unordered_map<SystemId, SystemUpdatable *> mSystemUpdatables;
    std::unordered_map<SystemId, SystemDrawable *> mSystemDrawables;
    std::unordered_map<SystemId, SystemEventable *> mSystemEventables;

    World *mWorld{nullptr};

   public:
    SystemManager() = default;
    ~SystemManager() = default;

    template <typename TSystem, typename... TArgs>
    TSystem &add(TArgs &&... args)
    {
      if (has<TSystem>())
	throw std::logic_error("System already exist");

      TSystem *system(new TSystem(std::forward<TArgs>(args)...));

      system->mId = getClassTypeId<TSystem>();
      system->mWorld = mWorld;

      system->initialize();

      registerSystemFilterGroupId(system);

      std::unique_ptr<System> systemPtr{system};

      mSystems[system->mId] = std::move(systemPtr);

      auto systemUpdatable = dynamic_cast<SystemUpdatable *>(system);
      if (systemUpdatable != nullptr)
	mSystemUpdatables[system->mId] = systemUpdatable;

      auto systemDrawable = dynamic_cast<SystemDrawable *>(system);
      if (systemDrawable != nullptr)
	mSystemDrawables[system->mId] = systemDrawable;

      auto systemEventable = dynamic_cast<SystemEventable *>(system);
      if (systemEventable != nullptr)
	mSystemEventables[system->mId] = systemEventable;

      return *system;
    }

    template<typename TSystem>
    TSystem &get()
    {
      SystemId systemId = getClassTypeId<TSystem>();

      if (!has(systemId))
	throw std::logic_error("System doesn't exist");

      return *static_cast<TSystem *>(mSystems[systemId].get());
    }

    // TODO : ! Check delete on update? Delete system after a update
    template<typename TSystem>
    void remove()
    {
      SystemId systemId = getClassTypeId<TSystem>();

      if (!has(systemId))
	throw std::logic_error("System doesn't exist");

      mSystems[systemId].reset();
      mSystems.erase(systemId);

      if (mSystemUpdatables.count(systemId) == 1)
	mSystemUpdatables.erase(systemId);

      if (mSystemDrawables.count(systemId) == 1)
	mSystemDrawables.erase(systemId);
    }

    template <typename TSystem>
    bool has()
    {
      auto systemId = getClassTypeId<TSystem>();

      return mSystems.count(systemId) > 0;
    }

    bool has(SystemId id);

    void registerSystemFilterGroupId(System *system);

    void update(float deltaTime);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void processEvents(sf::Event event);
  };
}

#endif //B2GE_SYSTEMMANAGER_HPP
