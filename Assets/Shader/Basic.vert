#version 450 core
layout(location = 0) in vec2 v_position;
layout(location = 1) in vec2 v_texture;
out vec2 v_texCoord;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(v_position, 0.0, 1.0);
	v_texCoord = v_texture;
}