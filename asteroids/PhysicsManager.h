#ifndef PhysicsManager_h
#define PhysicsManager_h

#include <memory>
#include <map>

#include "Entity.h"
#include "EngineManager.h"
#include "PhysicComponent.h"
#include "Pairs.h"

/**
@brief ���������� ������ ��� ����
@detailed 
*/
class PhysicsManager : public EngineManager<HandleBody>
{
private:
	std::vector<std::shared_ptr<BodyPair>> _pairs;
public:
	static const float Accuracy;							/**< �������� */
	static const float kAllowedPenetration;					/**< ���������� ������������������� */
	static const float kBounceFactor;						/**< ���������� ��������� */

	PhysicsManager();
	virtual ~PhysicsManager();

	virtual void OnFrame(float dt);

	virtual void AttachComponent(HandleEntity entity, HandleBody component) override;
	virtual bool DetachComponent(HandleEntity entity, HandleBody component) override;
};


#endif

