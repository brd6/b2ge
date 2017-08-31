//
// Created by brd6 on 30/08/2017.
//

#ifndef B2GE_SYSTEMMANAGER_HPP
#define B2GE_SYSTEMMANAGER_HPP

#include <memory>
#include <unordered_map>
#include "Core/System.hpp"

namespace b2ge
{
  class World;

  class SystemManager
  {
   private:
    using SystemPtr = std::unique_ptr<System>;

    std::unordered_map<SystemId, SystemPtr> mSystems;

    friend class World;

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

      std::unique_ptr<System> systemPtr{system};

      mSystems[system->mId] = std::move(systemPtr);

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

    template<typename TSystem>
    void remove()
    {
      SystemId systemId = getClassTypeId<TSystem>();

      if (!has(systemId))
	throw std::logic_error("System doesn't exist");

      mSystems[systemId].reset();
      mSystems.erase(systemId);
    }

    template <typename TSystem>
    bool has()
    {
      auto systemId = getClassTypeId<TSystem>();

      return mSystems.count(systemId) > 0;
    }

    bool has(SystemId id);

  };
}

#endif //B2GE_SYSTEMMANAGER_HPP
