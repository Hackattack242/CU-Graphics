#version 400 core

//  Transformation matrices
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

//  Light propeties
uniform float fov;
uniform vec4 Global;
uniform vec4 Ambient;
uniform vec4 Diffuse;
uniform vec4 Specular;
uniform vec4 Position;
uniform vec4 LightColor;

//  Vertex attributes (input)
layout(location = 0) in vec4 Vertex;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec4 Color;
layout(location = 3) in vec2 Texture;

mat4 ModelViewMatrix;
mat3 NormalMatrix;


out vec2  ModelPos;

void main()
{	
   //construct Model-View Matrix
   ModelViewMatrix = ViewMatrix * ModelMatrix;

   ModelPos = (ModelMatrix * Vertex).xz *3;
   
   gl_Position =  ProjectionMatrix * ModelViewMatrix * Vertex;
}
