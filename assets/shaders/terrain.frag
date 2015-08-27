#version 130
uniform sampler2D atlas;
uniform float level;
uniform int mode;

in vec4 lightVector;
in vec4 normal;
in float Z;

vec2 atlascoords(vec2 coords,int textureid)
{
      vec2 temp;
      temp.x = (coords.x / 8.0) + 0.125*(textureid % 8);
      temp.y = (coords.y/ 8.0) + 0.125*(textureid / 8);
      
       return temp;
}
;

void main (void)
{

if (mode==1 && Z<=0) discard;

if (mode==2 && Z>=level*0.5) discard;
if (mode==3 && Z>=level*0.5) discard;

float factor = 0.75;


float tmp = max(dot(-lightVector,normal),0);

tmp = clamp(0.2+tmp*tmp*tmp,0.0,1.0);

int textid1 = int( floor(gl_Color.r/0.00390625));
int textid2 = int (floor(gl_Color.g/0.00390625));
int textid3 = int (floor(gl_Color.b/0.00390625));



vec4 col = vec4 (0.0,0.0,0.0,0.0);

vec4 base1t = vec4 (0.0,0.0,0.0,0.0);
vec4 base2t = vec4 (0.0,0.0,0.0,0.0);
vec4 base3t = vec4 (0.0,0.0,0.0,0.0);
vec4 transitiont = vec4 (0.0,0.0,0.0,0.0);

float angle = 0.0;

int type_ = int(floor(gl_Color.a/0.125));
switch (type_)
{
case 0: 
//basic terrain

 	col = texture2D(atlas, atlascoords(vec2(gl_TexCoord[0].xy),textid1));
        //col = vec4(0.0,1.0,1.0,1.0);
break;

case 1:
//transition 1

    base1t = texture2D(atlas, atlascoords(vec2(gl_TexCoord[0].x,gl_TexCoord[0].y+sqrt(3.0)/4.0*factor),textid1));
    base2t = texture2D(atlas, atlascoords(vec2(gl_TexCoord[0].x,gl_TexCoord[0].y-sqrt(3.0)/4.0*factor),textid2));
  transitiont = texture2D(atlas,atlascoords(vec2((gl_TexCoord[0].x - 0.5)/factor+0.5,(gl_TexCoord[0].y - 0.5)/factor+0.5),62));

    col = base1t*(1.0-transitiont.x)+base2t*(transitiont.x);

break;

case 2:
//transition 2
     angle = 60.0;
     base1t = texture2D(atlas, atlascoords(vec2((gl_TexCoord[0].x-0.5)*cos(radians(angle))+(gl_TexCoord[0].y-0.5)*sin(radians(angle))+0.5+0.375*factor,sqrt(3.0)/8.0*factor+0.5+(gl_TexCoord[0].y-0.5)*cos(radians(angle))-(gl_TexCoord[0].x-0.5)*sin(radians(angle))),textid1   ));
     base2t = texture2D(atlas, atlascoords(vec2((gl_TexCoord[0].x-0.5)*cos(radians(angle))+(gl_TexCoord[0].y-0.5)*sin(radians(angle))+0.5-0.375*factor,-sqrt(3.0)/8.0*factor+0.5+(gl_TexCoord[0].y-0.5)*cos(radians(angle))-(gl_TexCoord[0].x-0.5)*sin(radians(angle))) ,textid2  ));
      transitiont = texture2D(atlas,atlascoords(vec2((gl_TexCoord[0].x - 0.5)/factor+0.5,(gl_TexCoord[0].y - 0.5)/factor+0.5),62));

     col = base1t*(1.0-transitiont.x)+base2t*(transitiont.x);

     //col = transitiont;
;

break;

case 3:
//transition 3
     angle = 120.0;
     base1t = texture2D(atlas, atlascoords(vec2(
                                (gl_TexCoord[0].x-0.5)*cos(radians(angle))+(gl_TexCoord[0].y-0.5)*sin(radians(angle))+0.5+0.375*factor,
                        -sqrt(3.0)/8.0*factor+0.5+(gl_TexCoord[0].y-0.5)*cos(radians(angle))-(gl_TexCoord[0].x-0.5)*sin(radians(angle))
             ) ,textid1 ));

     base2t = texture2D(atlas, atlascoords(vec2(
                                               (gl_TexCoord[0].x-0.5)*cos(radians(angle))+(gl_TexCoord[0].y-0.5)*sin(radians(angle))+0.5-0.375*factor,
                        +sqrt(3.0)/8.0*factor+0.5+(gl_TexCoord[0].y-0.5)*cos(radians(angle))-(gl_TexCoord[0].x-0.5)*sin(radians(angle))
             ) ,textid2  ));

     transitiont = texture2D(atlas,atlascoords(vec2((gl_TexCoord[0].x - 0.5)/factor+0.5,(gl_TexCoord[0].y - 0.5)/factor+0.5),62));

     col = base1t*(1.0-transitiont.x)+base2t*(transitiont.x);


break;

case 4:
//corner 1
   base1t = texture2D(atlas, atlascoords(vec2(gl_TexCoord[0].x+0.25*factor,gl_TexCoord[0].y+sqrt(3.0)/4.0*factor),textid1) );
   base2t = texture2D(atlas,atlascoords( vec2(gl_TexCoord[0].x-0.5*factor,gl_TexCoord[0].y),textid2) );
    base3t = texture2D(atlas,atlascoords( vec2(gl_TexCoord[0].x+0.25*factor,gl_TexCoord[0].y-sqrt(3.0)/4.0*factor),textid3) ) ;

      transitiont = texture2D(atlas,atlascoords(vec2((gl_TexCoord[0].x - 0.5)/factor+0.5,(gl_TexCoord[0].y - 0.5)/factor+0.5),63));
 
  col = base1t *transitiont.r+base2t*transitiont.g+base3t*transitiont.b;


break;

case 5:
//corner2
    angle = 60.0;
    base1t = texture2D(atlas, atlascoords(vec2((gl_TexCoord[0].x-0.5)*cos(radians(angle))+(gl_TexCoord[0].y-0.5)*sin(radians(angle))+0.5+0.5*factor,0.5+(gl_TexCoord[0].y-0.5)*cos(radians(angle))-(gl_TexCoord[0].x-0.5)*sin(radians(angle)) ),textid1));
    base2t = texture2D(atlas, atlascoords(vec2((gl_TexCoord[0].x-0.5)*cos(radians(angle))+(gl_TexCoord[0].y-0.5)*sin(radians(angle))+0.5-0.25*factor,0.5+(gl_TexCoord[0].y-0.5)*cos(radians(angle))-(gl_TexCoord[0].x-0.5)*sin(radians(angle))+sqrt(3.0)/4.0*factor),textid2));
    base3t = texture2D(atlas, atlascoords(vec2((gl_TexCoord[0].x-0.5)*cos(radians(angle))+(gl_TexCoord[0].y-0.5)*sin(radians(angle))+0.5-0.25*factor,0.5+(gl_TexCoord[0].y-0.5)*cos(radians(angle))-(gl_TexCoord[0].x-0.5)*sin(radians(angle))-sqrt(3.0)/4.0*factor),textid3));

   transitiont = texture2D(atlas,atlascoords(vec2((gl_TexCoord[0].x - 0.5)/factor+0.5,(gl_TexCoord[0].y - 0.5)/factor+0.5),63));
   col = base1t *transitiont.r+base2t*transitiont.g+base3t*transitiont.b;


break;

default:
  col = vec4(1.0,1.0,0.0,0.0);
}  

 col.a = 1.0;
 gl_FragColor = col*tmp;

}
