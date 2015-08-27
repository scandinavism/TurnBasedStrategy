#version 130
in vec4 refrCoords2; 
in vec4 normCoords2; 
in vec4 viewCoords;
in  vec4 viewTangetSpace;
in  vec4 lightTangetSpace;

uniform sampler2D reflection;
uniform sampler2D refraction;
uniform sampler2D normalMap;
uniform sampler2D dudvMap;

uniform vec4 waterColor;
uniform float shift;

void main()
{
	vec4 normal = vec4 (0.0,0.0,-1.0,0.0);

        float tmp = max(dot (-lightTangetSpace,normal),0.0);
	tmp = clamp(0.2+tmp*tmp*tmp,0.0,1.0);


        const float kShine = 128.0;
        const float kDistortion = 0.115;
        const float kRefraction = 0.129;

	vec4 refrCoords = refrCoords2;
	vec4 normCoords = normCoords2;
	
        normCoords.x -= shift;
        refrCoords.x += shift;

        vec4 distOffset = texture2D(dudvMap, normCoords.xy) * kDistortion;
                vec4 dudvColor = texture2D(dudvMap, vec2(refrCoords + distOffset));
                dudvColor = normalize(dudvColor * 2.0 - 1.0) * kRefraction;

                vec4 normalVector = texture2D(normalMap, vec2(refrCoords + distOffset));
                normalVector = normalVector * 2.0 - 1.0;
                normalVector.a = 0.0;

                vec4 lightReflection = normalize( reflect(-lightTangetSpace, normalVector) );

                vec4 invertedFresnel = vec4( dot(normalVector, lightReflection ) );
                vec4 fresnelTerm = 1.0 - invertedFresnel;

                vec4 projCoord = viewCoords / viewCoords.q;

                projCoord = (projCoord + 1.0) * 0.5;
                projCoord += dudvColor*0.35;
                projCoord = clamp(projCoord, 0.001, 0.999);

                vec4 reflCoords = viewCoords / viewCoords.q;
               // reflCoords.x = - reflCoords.x;
                reflCoords.y = -reflCoords.y;
                reflCoords = (reflCoords + 1.0) * 0.5;
                reflCoords += dudvColor*0.41;
                reflCoords = clamp(reflCoords, 0.001, 0.999);
//
              vec4 reflectionColor  = texture2D(reflection, reflCoords.xy);
                vec4 refractionColor  = texture2D(refraction, projCoord.xy);
                vec4 depthValue = vec4(0.5,0.5,0.5,0.5);

                vec4 invDepth = 1.0 - depthValue;
                refractionColor *= 4*invertedFresnel * invDepth;
                refractionColor +=  waterColor * depthValue * invertedFresnel;

                reflectionColor *= fresnelTerm;

                vec4 localView = normalize(viewTangetSpace);
                float intensity = max(0.0, dot(lightReflection, localView) );
                vec4 specular = vec4(pow(intensity, kShine));

        vec4 summ =  (refractionColor + reflectionColor + specular)*tmp;
        summ.a = 1.0;
       gl_FragColor = summ;
     //   gl_FragColor = refractionColor;
;
	
	
}
