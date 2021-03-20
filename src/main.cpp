#include "main.h"

#include <ncine/Application.h>
#include <ncine/AppConfiguration.h>


nctl::UniquePtr<nc::IAppEventHandler> createAppEventHandler()
{
	return nctl::makeUnique<MyEventHandler>();
}

void MyEventHandler::onPreInit(nc::AppConfiguration &config)
{
#if defined(__ANDROID__)
	config.dataPath() = "asset::";
#elif defined(__EMSCRIPTEN__)
	config.dataPath() = "/";
#else
	#ifdef PACKAGE_DEFAULT_DATA_DIR
	config.dataPath() = PACKAGE_DEFAULT_DATA_DIR;
	#else
	config.dataPath() = "data/";
	#endif
#endif

	config.withVSync = true;
	config.windowTitle = "ncTemplate";
	config.windowIconFilename = "icon48.png";

	Options::getInstance().setBaseFilePath("../../ncPhysic-data/data/");
	Options::getInstance().readFromFile("../../ncPhysic-data/data/options.txt");
	Options::getInstance().setImageFilePath("../../ncPhysic-data/data/images/");
	Options::getInstance().setFps(60);
}

void MyEventHandler::onInit()
{
	//Renderer Init
	Renderer::Renderer(2);
	Renderer::attachLayer();
	Renderer::constructDebugLayer("../../ncPhysic-data/data/fonts/OpenSans-Regular32_256.fnt", "../../ncPhysic-data/data/fonts/OpenSans-Regular32_256.png");
	Renderer::debugLayer.addDebugString("ElapsedTime: ");
	Renderer::debugLayer.addDebugString("velocity: ");
	Renderer::debugLayer.addDebugString("center: ");
	//Renderer Init

	//Texture loading
	TextureLoader::loadTexture(Options::getInstance().getImageFilePath() + "pgstaticfront.png");
	//Texture loading

	//Physic Engine Init
	BattleHandler::getInstance().createEntity(Options::getInstance().getImageFilePath() + "black.png", { 200, 200 }, { 40, 40}, 20.0f, 1.0f);
	//Physic Engine Init

	start = std::chrono::high_resolution_clock::now();
}

void MyEventHandler::onFrameStart()
{
	std::chrono::duration<double> deltaTime = std::chrono::high_resolution_clock::now() - start;
	elapsedTime = deltaTime.count();

	//Clear Screen
	Renderer::clearScreen(nc::Color(50, 50, 150, 255));
	Image::resetAllCondition();
	//Clear Screen

	//Update AABB
	int index = BattleHandler::getInstance().createParticle(Options::getInstance().getImageFilePath() + "pgstaticfront.png", { 100, 100 }, { 30, 30 }, 20.0f, 2.5f, 1.0f);
	BattleHandler::getInstance().applyForce(0.5f, { 0.5f, 0.5f }, index);

	BattleHandler::getInstance().moveParticle(elapsedTime);
	BattleHandler::getInstance().detectCollisionParticle();
	//Update AABB

	//Update Image
	BattleHandler::getInstance().draw();
	//Update Image

	//Update Time
	start = std::chrono::high_resolution_clock::now();
	//Update Time

	//Clear BattleHandler
	BattleHandler::getInstance().destroyDeadElement();
	//Clear BattleHandler

	//Update Info DebugLayer
	Renderer::debugLayer.setDebugString("ElapsedTime: " + std::to_string(elapsedTime), 0);
	//Renderer::debugLayer.setDebugString("Velocity.x: " + std::to_string(box->getV().x) + "Velocity.y: " + std::to_string(box->getV().y), 1);
	//Renderer::debugLayer.setDebugString("Center.x: " + std::to_string(box->getIntCenter().x) + "Center.y: " + std::to_string(box->getCenter().y), 2);
	//Update Info DebugLayer

	//Clear Input 
	Input::clearReleasedKey();
	Input::clearMouseEvent();
	//Clear Input 
}











void MyEventHandler::onKeyReleased(const nc::KeyboardEvent &event)
{
	Input::deleteEvent(event);
}

void MyEventHandler::onKeyPressed(const nc::KeyboardEvent &event)
{
	Input::saveEvent(event);
}

void MyEventHandler::onMouseButtonPressed(const nc::MouseEvent &event)
{
	Input::saveEvent(event);
}

void MyEventHandler::onMouseButtonReleased(const nc::MouseEvent& event)
{
	Input::deleteEvent(event);
}

void MyEventHandler::onMouseMoved(const nc::MouseState &state)
{
	Input::updateMousePos(state);
}
