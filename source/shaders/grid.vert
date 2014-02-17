#version 130

uniform int levelSize;
uniform float objectID;
uniform vec2 nearFar;
out vec3 theNormal;
out float linearDepth;
out vec2 uv;

void oculusDeform();

void main()
{
	uv = (gl_Vertex).xy / levelSize + vec2(0.5, 0.5);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex ;

	theNormal = normalize(gl_NormalMatrix * gl_Normal);
	linearDepth = (-(gl_ModelViewMatrix * gl_Vertex).z-nearFar.x)/(nearFar.y-nearFar.x);
	gl_TexCoord[1] = vec4(objectID);

	oculusDeform();

	return;
}