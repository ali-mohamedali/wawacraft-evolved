#version 330 core
in vec2 gtexcoord;

out vec4 fColor;

uniform sampler2D gtexture;

void main()
{
  fColor=texture(gtexture, gtexcoord);
}