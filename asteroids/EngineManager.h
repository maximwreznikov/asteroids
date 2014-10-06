#ifndef EngineManager_h
#define EngineManager_h

#include <algorithm>

#include "Entity.h"

/**
@brief Базовый класс для подсистемы игрового движка
@detailed 
*/
template<typename H>
class EngineManager
{
protected:
	std::vector<H> EngineManager<H>::_components;
public:
	EngineManager(){};
	virtual ~EngineManager(){};

	virtual void AttachComponent(HandleEntity entity, H component)
	{
		_components.push_back(component);
	}

	virtual bool DetachComponent(HandleEntity entity, H component)
	{
		auto posObjects = std::find(_components.begin(), _components.end(), component);
		bool found = posObjects != _components.end();

		if (found)
			_components.erase(posObjects);

		return found;
	}
};


#endif

