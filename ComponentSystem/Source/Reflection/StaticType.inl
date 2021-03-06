#pragma once
// This file generated by CppReflection.ClassExpoter.
namespace Egliss::ComponentSystem { class Component; }
namespace Egliss::ComponentSystem { class Transform; }
namespace Egliss::ComponentSystem { class RectTransform; }
namespace Egliss::Game { class Dummy; }

namespace Egliss::Reflection
{
    template<> class StaticTypeDescription<Egliss::ComponentSystem::Component>
    {
    public:
        static constexpr int Id = 0;
        static constexpr std::string_view Name = "Egliss::ComponentSystem::Component";
    };
        template<> class StaticTypeDescription<Egliss::ComponentSystem::Transform>
        {
        public:
            static constexpr int Id = 1;
            static constexpr std::string_view Name = "Egliss::ComponentSystem::Transform";
        };
            template<> class StaticTypeDescription<Egliss::ComponentSystem::RectTransform>
            {
            public:
                static constexpr int Id = 2;
                static constexpr std::string_view Name = "Egliss::ComponentSystem::RectTransform";
            };
        template<> class StaticTypeDescription<Egliss::Game::Dummy>
        {
        public:
            static constexpr int Id = 3;
            static constexpr std::string_view Name = "Egliss::Game::Dummy";
        };
    
}
