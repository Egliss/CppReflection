#include <iostream>
#include "TestHelper.h"
#include "CppUnitTest.h"
#include "../../ComponentSystem/Source/ComponentSystem/ComponentSystem.hpp"
#include "../../ComponentSystem/Source/Game/Dummy/Dummy.hpp"
#include "../../ComponentSystem/Source/SceneManagement/SceneManagement.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Egliss::ComponentSystem;
using namespace Egliss::SceneManagement;

namespace Egliss
{
namespace Reflection
{
#pragma region Types
	class Dummy0
	{
	public:virtual ~Dummy0() {}
	};
	class Dummy1 : public Dummy0
	{
	public:virtual ~Dummy1() {}
	};
	class Dummy2 : public Dummy1
	{
	public:virtual ~Dummy2() {}
	};
	class Dummy3 : public Dummy0
	{
	public:virtual ~Dummy3() {}
	};
	class Dummy4 : public Dummy0
	{
	public:virtual ~Dummy4() {}
	};
	class Dummy5 : public Dummy4
	{
	public:virtual ~Dummy5() {}
	};
	class Dummy6 : public Dummy5
	{
	public:virtual ~Dummy6() {}
	};
	class Dummy7 : public Dummy0
	{
	public:virtual ~Dummy7() {}
	};
	class Dummy8 : public Dummy7
	{
	public:virtual ~Dummy8() {}
	};
#pragma endregion

	TEST_CLASS(DynamicCast)
	{
		inline static auto Dummies = std::vector<Dummy0*>();
	public:
		TEST_METHOD_INITIALIZE(DynamicCastInitialize)
		{
			std::array<Dummy0*, 9> types;
			types[0] = new Dummy0();
			types[1] = new Dummy1();
			types[2] = new Dummy2();
			types[3] = new Dummy3();
			types[4] = new Dummy4();
			types[5] = new Dummy5();
			types[6] = new Dummy6();
			types[7] = new Dummy7();
			types[8] = new Dummy8();

			Dummies.reserve(1000);
			Dummies.resize(1000);
			for (int L10 = 0; L10 < 1000; L10++) {
				auto ii = L10 % 1;
				Dummies[L10] = types[ii];
			}
		}
		EGL_TEST_MRTHOD_BENCHMARK(_10000x1000, L"RTTI")
		{
			for (int L11 = 0; L11 < 10000; L11++) 
			{
				for (int L10 = 0; L10 < 1000; L10++) 
				{
					const auto ptr = Dummies[L10];
					//最適化抑止
					volatile auto x = dynamic_cast<Dummy6*>(ptr);
				}
			}
		}
		TEST_METHOD_CLEANUP(DynamicCastCleanUp)
		{
			Dummies.clear();
		}
	};

	TEST_CLASS(ReflectionCast)
	{
		static inline auto Dummies = std::vector<Component*>();
	public:
		TEST_METHOD_INITIALIZE(GetComponentInitialize)
		{
			std::array<Component*, 6> types;
			types[0] = new Component();
			types[0]->TypeId(Egliss::Reflection::Static<Component>::Id);
			types[1] = new Component();
			types[1]->TypeId(Egliss::Reflection::Static<Component>::Id);
			types[2] = new Component();
			types[2]->TypeId(Egliss::Reflection::Static<Component>::Id);
			types[3] = new Game::Dummy();
			types[3]->TypeId(Egliss::Reflection::Static<Game::Dummy>::Id);
			types[4] = new Component();
			types[4]->TypeId(Egliss::Reflection::Static<Component>::Id);
			types[5] = new Component();
			types[5]->TypeId(Egliss::Reflection::Static<Component>::Id);

			Dummies.reserve(1000);
			Dummies.resize(1000);
			for (int L10 = 0; L10 < 1000; L10++) {
				auto ii = L10 % 6;
				Dummies[L10] = types.data()[ii];
			}
			Egliss::Reflection::DynamicTypeManager::Initialize();
		}
		EGL_TEST_MRTHOD_BENCHMARK(_10000x1000, L"ReleaseOnly")
		{
			const auto inputId = Egliss::Reflection::Static<Egliss::Game::Dummy>::Id;
			// TODO Debug時に1000倍程度遅くなるので計測しない
			// 主にこの辺が原因（std::コンテナ全てにオーバーヘッドが発生）
			// https://docs.microsoft.com/ja-jp/cpp/standard-library/iterator-debug-level?view=vs-2019
#ifdef _DEBUG
			for (int L11 = 0; L11 < 1; L11++) {
#else
			for (int L11 = 0; L11 < 10000; L11++) {
#endif // DEBUG
				for (int L10 = 0; L10 < 1000; L10++) {
					const auto componentTypeId = Dummies[L10]->TypeId();
					auto& result = Egliss::Reflection::DynamicTypeManager::IndexOf(componentTypeId);
					//最適化抑止
					volatile auto x = result.HasTypeRelation(inputId);
				}
			}
		}
		TEST_METHOD_CLEANUP(GetComponentCleanUp)
		{
			Dummies.clear();
		}
	};
}
	TEST_CLASS(GameObjectManagerTest)
	{
	public:
		TEST_METHOD(CreateValidObject)
		{
			GameObjectManager::Initialize();
			auto GameObject = GameObjectManager::Create();
			Assert::IsNotNull(GameObject);
			Assert::AreEqual(GameObject->Id(), 0);
			auto transform = GameObject->GetComponent<Transform>();
			Assert::IsNotNull(transform);
			Assert::AreEqual(transform->GameObject()->Id(), GameObject->Id());
			GameObjectManager::Finalize();
		}
		TEST_METHOD(Find)
		{
			GameObjectManager::Initialize();
			auto obj = GameObjectManager::Create("Object1");
			auto obj2 = GameObjectManager::Find("Object1");
			auto obj3 = GameObjectManager::Create();
			auto obj4 = GameObjectManager::Find("GameObject");
			Assert::IsNotNull(obj2);
			Assert::IsNotNull(obj4);
			Assert::AreEqual(obj->Id(), obj2->Id());
			Assert::AreEqual(obj3->Id(), obj4->Id());
			GameObjectManager::Finalize();
		}
	};

	TEST_CLASS(QuadTree)
	{
	public:
		EGL_TEST_MRTHOD_NOT_IMPLEMENT(Container)
		{
			//auto container = QuadTree<int>(0);
			//auto container2 = QuadTree<int>(1);
			//auto container3 = QuadTree<int>(2);
			//auto container4 = QuadTree<int>(3);
			//auto container5 = QuadTree<int>(11);
			//auto container6 = QuadTree<int>(12);
			//Assert::AreEqual((int)container.MortonLinearTree().size(), 1);
			//Assert::AreEqual((int)container2.MortonLinearTree().size(), 5);
			//Assert::AreEqual((int)container3.MortonLinearTree().size(), 21);
			//Assert::AreEqual((int)container3.GetByIndex(2).Hierarchy, 1);
			//Assert::AreEqual((int)container3.GetByIndex(2).MortonOrder, 1);
			//Assert::AreEqual((int)container3.GetByIndex(2).ToLinearIndex(), 2);
			//Assert::AreEqual((int)container3.GetByMortonOrder(2, 2).Hierarchy, 2);
			//Assert::AreEqual((int)container3.GetByMortonOrder(2, 2).MortonOrder, 2);
			//Assert::AreEqual((int)container3.GetByMortonOrder(2, 2).ToLinearIndex(), 7);
			//Assert::AreEqual((int)container4.MortonLinearTree().size(), 85);
			//Assert::AreEqual((int)container5.MortonLinearTree().size(), 5592405);
			//Assert::AreEqual((int)container6.MortonLinearTree().size(), 0);
		}
		EGL_TEST_MRTHOD_NOT_IMPLEMENT(Element)
		{
			//auto element = QuadTreeElement<int>(0, 0);
			//auto element2 = QuadTreeElement<int>(3, 1);
			//auto element3 = QuadTreeElement<int>(6, 2);
			//auto element4 = QuadTreeElement<int>(32, 4);
			//
			//Assert::AreEqual(element.ToLinearIndex(), 0);
			//Assert::AreEqual(element2.ToLinearIndex(), 4);
			//Assert::AreEqual(element3.ToLinearIndex(), 11);
			//Assert::AreEqual(element4.ToLinearIndex(), 117);
		}
	};
}


