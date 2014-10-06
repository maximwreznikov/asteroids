#ifndef PhysicsManager_h
#define PhysicsManager_h

#include <memory>
#include <map>

#include "Entity.h"
#include "EngineManager.h"
#include "PhysicComponent.h"
#include "Pairs.h"

/**
@brief физический движок для игры
@detailed 
*/
class PhysicsManager : public EngineManager<HandleBody>
{
private:
	std::vector<std::shared_ptr<BodyPair>> _pairs;
public:
	static const float Accuracy;							/**< точность */
	static const float kAllowedPenetration;					/**< допустимое взаимопроникновение */
	static const float kBounceFactor;						/**< коэффициет упругости */

	PhysicsManager();
	virtual ~PhysicsManager();

	virtual void OnFrame(float dt);

	virtual void AttachComponent(HandleEntity entity, HandleBody component) override;
	virtual bool DetachComponent(HandleEntity entity, HandleBody component) override;
};


#endif

