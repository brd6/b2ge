//
// Created by bberd on 30/08/2017.
//

#ifndef B2GE_SYSTEMMANAGER_HPP
#define B2GE_SYSTEMMANAGER_HPP

#include <vector>
#include "Core/System.hpp"
#include "Util/NonCopyable.hpp"

namespace b2ge
{
    class SystemManager :
        public NonCopyable
    {
    private:
        using systemPtr = std::unique_ptr<System>;
        std::vector<systemPtr> mSystems;

    public:
        template <typename TSystem, typename... TArgs>
        void add(TArgs&&... args)
        {

        }

        template <typename TSystem>
        void get()
        {

        }

        template <typename TSystem>
        void remove()
        {

        }

        void removeAll();

    };
}

#endif //B2GE_SYSTEMMANAGER_HPP
