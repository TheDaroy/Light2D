#pragma once
#include <unordered_map>
#include <cstdint>
#include <memory>
#include <typeindex>
#include <array>
#include "ComponentList.h"
#include "ECS-Types.h"
#include <iostream>

namespace LightEngine::ECS
{
class ComponentManager
{
public:
	template<typename T>
	 void AddNewComponentType()
	{
		componentArray[GetComponentID<T>()] = std::make_shared<ComponentArray<T>>();
		
		
	}

	template<typename T>
	 void AddComponentToEntity(Entity entity, T& component)
	{		
		GetComponentList<T>()->AddComponent(entity, component);
	}

	template<typename T>
	 T& GetComponent(Entity entity)
	{
		 return GetComponentList<T>()->GetComponent(entity);
	
	}

	template<typename T>
	 ComponentID GetComponentID()
	{
		const static ComponentID componentID = nrOfComponentTypes++;
	
		return componentID;
	}
	template<typename T>
	 size_t GetAmountOfActiveComponents()
	{
		return GetComponentList<T>()->GetAmountOfActiveComponents();
	}

private:
	
	std::array<std::shared_ptr<ComponentListHead>, MAX_COMPONENTS> componentArray;
	ComponentID nrOfComponentTypes = 0;
	 

	template<typename T>
	 std::shared_ptr<ComponentArray<T>> GetComponentList()
	{

		return std::static_pointer_cast<ComponentArray<T>>(componentArray[GetComponentID<T>()]);
	}

};
}




