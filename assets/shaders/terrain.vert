#version 130
uniform mat4 mWorldViewProj;
uniform mat4 mInvWorld;
uniform vec3 light;
uniform int mode;
uniform float level;

out vec4 lightVector;
out vec4 normal;
out float Z;


void main(void)
{
        vec4 v = vec4(gl_Vertex);

        Z = v.z;
        //if (mode==2) v.z -= 4.0*level;
	gl_Position = mWorldViewProj * gl_Vertex;
	

	normal = vec4(gl_Normal,0.0);
	normal = normalize(normal);

	lightVector = vec4 (light,0.0);
	lightVector = mInvWorld*lightVector;
	lightVector = normalize(lightVector);

	gl_FrontColor = gl_Color;
                  gl_TexCoord[0] = gl_MultiTexCoord0;
}
