#include"GraphicsSettings.hpp"
SimpleCraft::GraphicsSettings::GraphicsSettings()
{
	stbi_set_flip_vertically_on_load(true);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glfwWindowHint(GLFW_SAMPLES, 8);
}