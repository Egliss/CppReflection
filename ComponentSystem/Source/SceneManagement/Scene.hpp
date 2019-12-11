#pragma once

namespace Egliss::SceneManagement
{
	class Scene
	{
	public:


	private:
		std::string _name;
		std::vector<ComponentSystem::GameObject*> _entities;
	};
}