#pragma once
namespace Engine
{
	enum GSystem
	{
		GLES20, GL, DX11
	};
	class GraphicsSystem
	{
	public:
		void init(GSystem system);
		void draw();
	private:
		
	};
}

