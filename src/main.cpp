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
	config.resolution = { 1080, 720 };

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
	//BattleHandler::getInstance().createEntity(Options::getInstance().getImageFilePath() + "black.png", { 200, 200 }, { 40, 40}, 20.0f, 1.0f);
	
	BattleHandler::getInstance().createPlayerEntity(Options::getInstance().getImageFilePath() + "black.png", { 200, 200 }, { 40, 40 }, 20.0f, 20.0f);
	BattleHandler::getInstance().createStaticRectangleWalls(Options::getInstance().getImageFilePath() + "white.png", { 400, 400 }, { 40, 40 }, 20.0f, 20.0f);
	BattleHandler::getInstance().createStaticRectangleWalls(Options::getInstance().getImageFilePath() + "white.png", { 900, 400 }, { 40, 40 }, 20.0f, 20.0f);

	BattleHandler::getInstance().createEntity(Options::getInstance().getImageFilePath() + "red.png", { 400, 600 }, { 40, 40 }, 20.0f, 20.0f);

	BattleHandler::getInstance().createLimitLine(0.0f, Axis::x);
	BattleHandler::getInstance().createLimitLine(1080, Axis::x);
	BattleHandler::getInstance().createLimitLine(0.0f, Axis::y);
	BattleHandler::getInstance().createLimitLine(720, Axis::y);

	//Physic Engine Init

	//CoolDown Init
	coolDown = CoolDown(0.1f);
	coolDownHitbox = CoolDown(0.2f);
	coolDown.registerInit();
	coolDownHitbox.registerInit();
	//CoolDown Init

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

	BattleHandler::getInstance().applyFrictionOnPlayerEntities(elapsedTime);

	//Take Command
	if (Input::isPressed(nc::KeySym::W))
	{
		BattleHandler::getInstance().applyForceOnPlayerEntities(elapsedTime, { 0.0f, 50.0f }, 0);
	}
	if (Input::isPressed(nc::KeySym::S))
	{
		BattleHandler::getInstance().applyForceOnPlayerEntities(elapsedTime, { 0.0f, -50.0f }, 0);
	}
	if (Input::isPressed(nc::KeySym::A))
	{
		BattleHandler::getInstance().applyForceOnPlayerEntities(elapsedTime, { -50.0f, 0.0f }, 0);
	}
	if (Input::isPressed(nc::KeySym::D))
	{
		BattleHandler::getInstance().applyForceOnPlayerEntities(elapsedTime, { 50.0f, 0.0f }, 0);
	}
	//Take Command

	//Update AABB
	if (coolDown.isEnd() && Input::isPressed(Input::KeyMouse::rightKey))
	{
		int index = BattleHandler::getInstance().createParticle(Options::getInstance().getImageFilePath() + "pgstaticfront.png", { Input::getMousePos().x, Input::getMousePos().y }, { 30, 30 }, 20.0f, 2.5f, 1.0f);
		BattleHandler::getInstance().applyForceOnParticle(0.5f, { 0.5f, 0.5f }, index);
		coolDown.registerInit();
	}

	if (coolDownHitbox.isEnd() && Input::isPressed(Input::KeyMouse::leftKey))
	{
		//int index = BattleHandler::getInstance().createRectangleHitbox(Options::getInstance().getImageFilePath() + "white.png", { Input::getMousePos().x, Input::getMousePos().y }, { 30, 30 }, 2.5f, 1.0f);
		int index = BattleHandler::getInstance().createPlayerRectangleHitbox(Options::getInstance().getImageFilePath() + "white.png", 
			{ (int)BattleHandler::getInstance().getPlayerRectangleEntities(0)->m_box.m_max.x - 10, (int)BattleHandler::getInstance().getPlayerRectangleEntities(0)->m_box.m_max.y - 10},
			{ 30, 30 }, 2.5f, 1.0f);
		coolDownHitbox.registerInit();
	}

	BattleHandler::getInstance().moveParticle(elapsedTime);
	BattleHandler::getInstance().movePlayerEntities(elapsedTime);

	BattleHandler::getInstance().updateLifeRectangleHitbox();
	BattleHandler::getInstance().updateLifePlayerRectangleHitbox();
	
	BattleHandler::getInstance().detectCollisionParticle();
	BattleHandler::getInstance().detectCollisionEntity();
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
	Renderer::debugLayer.setDebugString("life: " + std::to_string(BattleHandler::getInstance().getPlayerRectangleEntities(0)->m_currentLife), 1);
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
