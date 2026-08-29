#include"Shader.hpp"
unsigned int SimpleCraft::Shader::CreateShader(std::string_view path, unsigned int type)
{
	std::string shaderSource = LoadShader(path);
	unsigned int shader = glCreateShader(type);
	const char* shaderCSource = shaderSource.c_str();
	glShaderSource(shader, 1, &shaderCSource, NULL);
	glCompileShader(shader);
	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::string infoLog(length, '\0');
		glGetShaderInfoLog(shader, length, NULL, infoLog.data());
		PRINT_ERROR_FILE(infoLog, path);
		glDeleteShader(shader);
		return unsigned int{};
	}
	return shader;
}
std::string SimpleCraft::Shader::LoadShader(std::string_view path)
{
	std::fstream file(std::string(path), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return std::string{};
	}
	std::string line;
	std::stringstream buffer;
	while (std::getline(file, line))
	{
		buffer << line << "\n";
	}
	file.close();
	return buffer.str();
}
SimpleCraft::Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath)
{
	unsigned int vertexShader = CreateShader(vertexPath, GL_VERTEX_SHADER);
	unsigned int fragmentShader = CreateShader(fragmentPath, GL_FRAGMENT_SHADER);
	if (vertexShader == unsigned int{} || fragmentShader == unsigned int{})
	{
		_program = unsigned int{};
		return;
	}
	_program = glCreateProgram();
	glAttachShader(_program, vertexShader);
	glAttachShader(_program, fragmentShader);
	glLinkProgram(_program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	int result;
	glGetProgramiv(_program, GL_LINK_STATUS, &result);
	if (!result)
	{
		int length;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &length);
		std::string infoLog(length, '\0');
		glGetProgramInfoLog(_program, length, NULL, infoLog.data());
		PRINT_ERROR(infoLog);
		glDeleteProgram(_program);
		_program = unsigned int{};
		return;
	}
}
SimpleCraft::Shader::~Shader()
{
	if (_program)
	{
		glDeleteProgram(_program);
	}
}
SimpleCraft::Shader::Shader(SimpleCraft::Shader&& other) noexcept : _program(other._program)
{
	other._program = unsigned int{};
}
SimpleCraft::Shader& SimpleCraft::Shader::operator=(SimpleCraft::Shader&& other) noexcept
{
	if (this != &other)
	{
		if (_program)
		{
			glDeleteProgram(_program);
		}
		_program = other._program;
		other._program = unsigned int{};
	}
	return *this;
}
void SimpleCraft::Shader::Use() const
{
	if (_program)
	{
		glUseProgram(_program);
	}
}
void SimpleCraft::Shader::SetMat4(std::string_view name, glm::mat4 value)
{
	if (_program)
	{
		int location = glGetUniformLocation(_program, std::string(name).c_str());
		glProgramUniformMatrix4fv(_program, location, 1, GL_FALSE, glm::value_ptr(value));
	}
}
void SimpleCraft::Shader::SetVec2(std::string_view name, glm::vec2 value)
{
	if (_program)
	{
		int location = glGetUniformLocation(_program, std::string(name).c_str());
		glProgramUniform2fv(_program, location, 1, glm::value_ptr(value));
	}
}