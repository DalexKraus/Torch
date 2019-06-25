#version 330 core

out vec4 FragColor;

void main()
{
   FragColor = vec4(sin(gl_FragCoord.x / 1920) * 1.0, sin(gl_FragCoord.y / 1920) * 1.0, 1.0f, 1.0f);
}