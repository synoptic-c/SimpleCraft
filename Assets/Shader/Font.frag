#version 450 core
out vec4 FragColor;
in vec2 v_texCoord;
uniform sampler2D u_texture;
void main()
{
	FragColor = vec4(1.0, 1.0, 1.0, texture(u_texture, vec2(v_texCoord.x, 1.0 - v_texCoord.y)).r);
}