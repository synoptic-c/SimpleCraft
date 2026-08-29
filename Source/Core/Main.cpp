#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"Graphics/ContextGL.hpp"
#include"Graphics/Window.hpp"
#include"Graphics/GraphicsSettings.hpp"
#include"Graphics/MeshManager.hpp"
#include"Graphics/ShaderManager.hpp"
#include"Graphics/FontManager.hpp"
#include"Graphics/Camera.hpp"
#include"Physics/BoundManager.hpp"
#include"Entity/Player.hpp"
#include"World/World.hpp"
#include"World/Tile.hpp"
#include"Entity/Drop.hpp"
#include"Container/Inventory.hpp"
#include"Container/Item.hpp"
#include"Edit/Cursor.hpp"
#include"Util/Timer.hpp"
#include"Util/Input.hpp"
int main()
{
	SimpleCraft::ContextGL contextGL("Assets/Config/Context.json");
	SimpleCraft::Window window("Assets/Config/Window.json");
	contextGL.LoadGLLoader();
	SimpleCraft::GraphicsSettings graphicsSettings;
	SimpleCraft::MeshManager meshManager("Assets/Config/MeshManager.json");
	SimpleCraft::ShaderManager shaderManager("Assets/Config/ShaderManager.json");
	SimpleCraft::FontManager fontManager("Assets/Config/FontManager.json");
	SimpleCraft::BoundManager boundManager("Assets/Config/BoundManager.json");
	SimpleCraft::Camera camera("Assets/Config/Camera.json");
	SimpleCraft::Tile tile("Assets/Config/Tile.json", "Assets/Data/Tile.json");
	SimpleCraft::World world("Assets/Config/World.json", "Assets/Config/Structure.json", "Assets/Data/Ore.json");
	SimpleCraft::Cursor cursor;
	SimpleCraft::Drop drop("Assets/Config/Drop.json");
	SimpleCraft::Player player("Assets/Config/Player.json");
	SimpleCraft::Inventory inventory("Assets/Config/Inventory.json");
	SimpleCraft::Item item("Assets/Config/Item.json");
	SimpleCraft::Timer timer;
	SimpleCraft::Input input;
	//1.8 - 1.12.2
	//int samples;
	//glGetIntegerv(GL_MAX_SAMPLES, &samples);
	//glEnable(GL_MULTISAMPLE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!window.WindowShouldClose())
	{
		timer.Update();
		window.PollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		camera.Update(window.GetFramebufferSizeX(), window.GetFramebufferSizeY());
		input.Update(window, camera);
		item.Update(camera, input);
		cursor.Update(drop, world, tile, item, camera, input);
		player.Update(boundManager, world, tile, input, timer.GetDeltaTime());
		camera.SetView(player.GetPosition());
		world.GenerateChunk(tile.GetTileDefinitions(), camera.GetView());
		world.UnloadChunk(camera.GetView());
		drop.Update(boundManager, world, tile, player, item, timer.GetDeltaTime());
		tile.Render(meshManager, shaderManager, camera, world);
		drop.Render(meshManager, shaderManager, tile, camera);
		player.Render(meshManager, shaderManager, camera, timer.GetDeltaTime());
		inventory.Render(input.GetIsInventory(), meshManager, shaderManager, camera);
		item.Render(input.GetIsInventory(), meshManager, shaderManager, fontManager, tile, input, camera);
		window.SwapBuffers();
	}
}