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
        static constexpr bool IsAbstract = false;
        static constexpr std::string_view Name = "Component";
        static constexpr std::array<int,1> ParentTypeIds = std::array<int,1> { 0};
    };
        template<> class StaticTypeDescription<Egliss::ComponentSystem::Transform>
        {
        public:
            static constexpr int Id = 1;
            static constexpr bool IsAbstract = false;
            static constexpr std::string_view Name = "Transform";
            static constexpr std::array<int,2> ParentTypeIds = std::array<int,2> { 1 ,0};
        };
            template<> class StaticTypeDescription<Egliss::ComponentSystem::RectTransform>
            {
            public:
                static constexpr int Id = 2;
                static constexpr bool IsAbstract = false;
                static constexpr std::string_view Name = "RectTransform";
                static constexpr std::array<int,3> ParentTypeIds = std::array<int,3> { 2 ,1 ,0};
            };
        template<> class StaticTypeDescription<Egliss::Game::Dummy>
        {
        public:
            static constexpr int Id = 3;
            static constexpr bool IsAbstract = false;
            static constexpr std::string_view Name = "Dummy";
            static constexpr std::array<int,2> ParentTypeIds = std::array<int,2> { 3 ,0};
        };
    
}
