#version 450 core
out vec4 FragColor;
in vec2 v_texCoord;
uniform sampler2D u_texture;
uniform vec2 u_uvOffset;
uniform vec2 u_uvIndex;
uniform vec2 u_uvScale;
void main()
{
	vec2 uvTransform = u_uvOffset + u_uvIndex * u_uvScale + v_texCoord * u_uvScale;
	FragColor = texture(u_texture, uvTransform);
}