#ifndef CLASS_MYEVENTHANDLER
#define CLASS_MYEVENTHANDLER

#include <string>

#include <ncine/IAppEventHandler.h>
#include <ncine/IInputEventHandler.h>

#include <nctl/UniquePtr.h>

#include <ncine/Texture.h>
#include <ncine/Sprite.h>

#include "Input/Input.h"

#include "Renderer/Options.h"
#include "Renderer/Renderer.h"

#include "Image.h"

#include "Physic/PhysicEngine.h"

namespace ncine {

class AppConfiguration;

}

namespace nc = ncine;

/// My nCine event handler
class MyEventHandler :
    public nc::IAppEventHandler,
    public nc::IInputEventHandler
{
public:
	void onPreInit(nc::AppConfiguration &config) override;
	void onInit() override;

	void onFrameStart() override;
	
	void onKeyPressed(const nc::KeyboardEvent &event) override;
	void onKeyReleased(const nc::KeyboardEvent &event) override;

	void onMouseButtonPressed(const nc::MouseEvent &event) override;
	void onMouseButtonReleased(const nc::MouseEvent& event) override;
	void onMouseMoved(const nc::MouseState &state) override;

private:
	nctl::UniquePtr<nc::Texture> texture;
	nctl::UniquePtr<nc::Sprite> sprite;

	Image image,image2,image3;
	AABBbox* box, *box2, *box3;
	bool first=true;

	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	double elapsedTime = 0.0f;
};

#endif

//Applicare cambiamenti classe Options
//Applicare cambiamenti classe Renderer
