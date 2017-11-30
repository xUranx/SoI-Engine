/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <TestApplication.h>

#include <graphics/GraphicsSystem.h>
#include <graphics/Window.h>
#include <math.h>
//#include <Log.h>
#include <Engine/Include/IOManager.h>
#include <GLES3/gl3.h>
namespace engine
{

	TestApplication::TestApplication(Window* window, GraphicsSystem* graphics, AAssetManager* asset)
		: GraphicsApplication(window, graphics)
		, m_totalTime(0.0f), m_asset(asset)
	{
		Engine::IOManager::m_asset = asset;
        std::string file;
        Engine::IOManager::readFileToBuffer("Shaders/colorShading.vert", file);
        LOGI("File: %s" , file.c_str());
        file.clear();
	}


	TestApplication::~TestApplication()
	{
	}


	bool TestApplication::update(float deltaTime)
	{
		m_totalTime += deltaTime;
		return true;
	}


	void TestApplication::render(Window* window, GraphicsSystem* graphics)
	{
		(void)window;	
		float val = fabsf(sinf(2.0f*m_totalTime));
		
		// Clear screen with pulsating yellow
		graphics->clearScreen(val, val, 0.0f, true);

		// Swap buffers
		graphics->swapBuffers();
	}

}