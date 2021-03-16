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

	//Physic Engine Init
	//PhysicEngine::getInstance().addAABBbox(AABBbox({ 50.0f, 50.0f }, { 100.0f, 100.0f }, 10.0f, TypeAABB::rigidBody));
	box = new AABBbox({ 50, 50 }, { 40, 40 }, 20.0f, TypeAABB::rigidBody);
	box2 = new AABBbox({ 300, 50 }, { 40, 40 }, 10.0f, TypeAABB::rigidBody);
	//box3 = new AABBbox({ 50, 300 }, { 40, 40 }, 10.0f, TypeAABB::rigidBody);
	//Physic Engine Init

	//Texture loading
	TextureLoader::loadTexture(Options::getInstance().getImageFilePath() + "pgstaticfront.png");
	//Texture loading

	image = Image(TextureLoader::getTexture(Options::getInstance().getImageFilePath() + "pgstaticfront.png"), Renderer::getLayer(0));
	image2 = Image(TextureLoader::getTexture(Options::getInstance().getImageFilePath() + "pgstaticfront.png"), Renderer::getLayer(0));
	image3 = Image(TextureLoader::getTexture(Options::getInstance().getImageFilePath() + "pgstaticfront.png"), Renderer::getLayer(0));

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
	if (Input::isRealesed((nc::KeySym::F)) /*&& first*/)
	{
		first = !first;
		box2->applyForce(elapsedTime, { -0.5f, 0.0f });
		//box3->applyForce(elapsedTime, { 0.0f, -1.0f });
	}
	if (Input::isPressed(Input::KeyMouse::rightKey))
	{
		box->applyForce(elapsedTime, { 1.0f, 0.0f });
		if (box->getV().x > 0.05f)
		{
			box->setV({ 0.05f, box->getV().y });
		}
	}
	else if (Input::isPressed(Input::KeyMouse::leftKey))
	{
	}
	PhysicEngine::getInstance().update(elapsedTime);
	//Update AABB

	//Update Image
	image.draw(box->getIntCenter().x, box->getIntCenter().y);
	image2.draw(box2->getIntCenter().x, box2->getIntCenter().y);
	//image3.draw(box3->getIntCenter().x, box3->getIntCenter().y);
	//Update Image

	//Update Time
	start = std::chrono::high_resolution_clock::now();
	//Update Time

	//Update Info DebugLayer
	Renderer::debugLayer.setDebugString("ElapsedTime: " + std::to_string(elapsedTime), 0);
	Renderer::debugLayer.setDebugString("Velocity.x: " + std::to_string(box->getV().x) + "Velocity.y: " + std::to_string(box->getV().y), 1);
	Renderer::debugLayer.setDebugString("Center.x: " + std::to_string(box->getIntCenter().x) + "Center.y: " + std::to_string(box->getCenter().y), 2);
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
