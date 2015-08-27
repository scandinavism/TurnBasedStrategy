#version 130
 out vec4 refrCoords2; 
 out vec4 normCoords2; 
  out vec4 viewCoords;
  out vec4 viewTangetSpace;
 out vec4 lightTangetSpace;

uniform vec3 light, camera;
uniform float shift;

//uniform vec4 lightPos, cameraPos;


void main()
{
	// Because we have a flat plane for water we already know the vectors for tangent space
	vec4 tangent = vec4(1.0, 0.0, 0.0, 0.0);
	vec4 normal = vec4(0.0, 0.0, 1.0, 0.0);
	vec4 biTangent = vec4(0.0, 1.0, 0.0, 0.0);

vec4	lightPos = vec4(light,0.0);
vec4	cameraPos = vec4(camera,0.0);
	cameraPos.y-=cameraPos.z;
vec4         v = gl_Vertex;
	
	// Calculate the vector coming from the vertex to the camera
	vec4 viewDir = cameraPos - gl_Vertex;

	// Compute tangent space for the view direction
	viewTangetSpace = viewDir;
	viewTangetSpace.w = 1.0;

	// Calculate the vector that the light hits the vertex
//	vec4 lightDir = lightPos - gl_Vertex;
	vec4 lightDir =  vec4(light,0.0);

	// Compute tangent space for the light direction
	//lightTangetSpace.x = dot(lightDir, tangent);
	//lightTangetSpace.y = dot(lightDir, biTangent);
	//lightTangetSpace.z = dot(lightDir, normal);

	lightTangetSpace = - lightDir;	
	lightTangetSpace = normalize(lightTangetSpace);

	vec4 lightshift;
	lightshift.x = cos(radians(360.0)*shift*3.0); 
	lightshift.y = sin (radians(360.0)*shift*3.0);
	lightshift.z = - ( lightDir.x*lightshift.x+lightDir.y*lightshift.y)/lightDir.z;
	lightshift.w = 0.0;

	lightshift = normalize(lightshift);
	lightshift *= 0.1;

	lightTangetSpace +=lightshift;	
        lightTangetSpace = -normalize(lightTangetSpace);

	lightTangetSpace.w = 1.0;



	gl_TexCoord[0] = gl_MultiTexCoord0;

        refrCoords2 = gl_TexCoord[0]*1;
        normCoords2 = gl_TexCoord[0]*1;

	
	gl_FrontColor = vec4(1.0,1.0,1.0,0.9);
	gl_BackColor = vec4(1.0,1.0,1.0,0.9);
	// This calculates our current projection coordinates
	viewCoords = gl_ModelViewProjectionMatrix * gl_Vertex;
	//viewCoords = gl_ModelViewProjectionMatrix * v;
	gl_Position = viewCoords;
}
