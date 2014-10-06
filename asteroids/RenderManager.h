#ifndef RenderManager_h
#define RenderManager_h

#include <vector>
#include <memory>
#include "Math.h"

#include "Entity.h"
#include "EngineManager.h"
#include "RendererComponent.h"

/**
@brief Графический движок
@detailed Содержит функциональность для инициализации вьюпорта и рендеринга объектов
*/
class RenderManager : public EngineManager<HandleRenderer>
{
private:
	Mat4							CameraView;					/**< Позиция и ориентация камеры*/
	Mat4							_projection;				/**< Матрица проекции */
	
	int								_widthScreen;				/**< ширина экрана в пискселях */
	int								_heightScreen;				/**< высота экрана в пискселях */

	float							_widthView;					/**< ширина экрана в пискселях */
	float							_heightView;				/**< высота экрана вьюпорта */
public:
	const float						ScaleX = 100.0f;			/**< Масштаб по оси X */
	const float						ScaleY = 100.0f;			/**< Масштаб по оси Y */

	RenderManager();
	virtual ~RenderManager();

	void InitView(int width, int height);
	void Render();

	float GetViewWidth();
	float GetViewHeight();
};

#endif

