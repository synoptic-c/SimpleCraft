#include"ContextGL.hpp"
SimpleCraft::ContextGL::ContextGL(std::string_view path)
{
	if (!glfwInit())
	{
		PRINT_ERROR("Failed to initialize GLFW");
		return;
	}
	std::fstream file(std::string(path), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return;
	}
	nlohmann::json json = nlohmann::json::parse(file);
	file.close();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, json["major"].get<int>());
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, json["minor"].get<int>());
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
SimpleCraft::ContextGL::~ContextGL()
{
	glfwTerminate();
}
void SimpleCraft::ContextGL::LoadGLLoader()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		PRINT_ERROR("Failed to initialize glad");
		return;
	}
}