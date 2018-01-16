#include "GraphicsSystem.h"
#include "Log.h"
namespace Engine
{
	void GraphicsSystem::init(GSystem system)
	{
		m_system = system;
		switch (system)
		{
		case GL:
			GLenum test = glewInit();
			if (test != GLEW_OK)
			{
				fatal_error("Glew Init error");
			}
			m_sBatch.init();
			break;
		case GLES20:
			m_sBatch.init();
		case DX11:
			/*std::unique_ptr<SpriteBatch> spriteBatch;
			spriteBatch = std::make_unique<SpriteBatch>(deviceContext);*/
		default:
			break;
		}
	}
}
