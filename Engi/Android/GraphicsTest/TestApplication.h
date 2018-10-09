/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_TEST_APPLICATION_H_
#define _ENGINE_TEST_APPLICATION_H_

#include <graphics/GraphicsApplication.h>
#include <core/Log.h>
#include <android/asset_manager.h>
#include <Engine/Include/SpriteBatch.h>

namespace engine
{
	class Window;
	class GraphicsSystem;
	
	class TestApplication :
		public GraphicsApplication
	{
	public:
		TestApplication(Window* window, GraphicsSystem* graphics, AAssetManager* asset);

		~TestApplication();

		/// Updates application. Returns true, if application is running.
		virtual bool update(float deltaTime);
		
		/// Renders application.
		virtual void render(Window* window, GraphicsSystem* graphics);

	private:
		float m_totalTime;
		AAssetManager* m_asset;
	};

}

#endif

