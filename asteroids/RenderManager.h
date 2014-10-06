#ifndef RenderManager_h
#define RenderManager_h

#include <vector>
#include <memory>
#include "Math.h"

#include "Entity.h"
#include "EngineManager.h"
#include "RendererComponent.h"

/**
@brief ����������� ������
@detailed �������� ���������������� ��� ������������� �������� � ���������� ��������
*/
class RenderManager : public EngineManager<HandleRenderer>
{
private:
	Mat4							CameraView;					/**< ������� � ���������� ������*/
	Mat4							_projection;				/**< ������� �������� */
	
	int								_widthScreen;				/**< ������ ������ � ��������� */
	int								_heightScreen;				/**< ������ ������ � ��������� */

	float							_widthView;					/**< ������ ������ � ��������� */
	float							_heightView;				/**< ������ ������ �������� */
public:
	const float						ScaleX = 100.0f;			/**< ������� �� ��� X */
	const float						ScaleY = 100.0f;			/**< ������� �� ��� Y */

	RenderManager();
	virtual ~RenderManager();

	void InitView(int width, int height);
	void Render();

	float GetViewWidth();
	float GetViewHeight();
};

#endif

