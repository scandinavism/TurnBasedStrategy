/* Perlin nose terrain generator
* by D. Nikiforovksy
*/

/*  as DGameMap method */
struct vec2f
{
  float x;
  float y;
}


void PerlinTerrain()
{

vec2f** Gradients;


int MAX_OCTAVES = 4; 
int period = 32; // these are tightly linked. be careful!

float persistency = 0.5;
float amplitude = 0.5;

for (int OCTAVE =1; OCTAVE<MAX_OCTAVES;i++)
{
//allocate gradients

int I_NUM_GRADIENTS = I_SIZE/period +1;
int J_NUM_GRADIENTS = J_SIZE/period +1;


Gradients = new vec2f*[I_NUM_GRADIENTS];
    for( int i = 0 ; i < I_NUM_GRADIENTS ; i++ )
        Gradients[i] = new vec2f [J_NUM_GRADIENTS];


//set gradients
for (int i =0; i<I_NUM_GRADIENTS)
	for (int j=0; j<J_NUM_GRADIENTS)
		{
			Gradients[i][j].x = 2*(mapRandom->Get()-0.5);
			Gradients[i][j].y = 2*(mapRandom->Get()-0.5);
		}


//calculate the noise
for (int i=0;i<I_SIZE;i++)
	for (int j=0;j<J_SIZE;j++)
{

	float noisevalue = 0.0;

	float noise1 = Gradients[i /period][j/period].x*(-i%period) + Gradients[i/period][j/period].y*(-j%period) ;	
	float noise2 = Gradients[i /period +1][j/period].x*(period-i%period) + Gradients[i/period +1][j/period].y*(-j%period) ;	
	float noise3 = Gradients[i /period+1][j/period+1].x*(period-i%period) + Gradients[i/period+1][j/period+1].y*(period-j%period) ;	
	float noise4 = Gradients[i /period][j/period+1].x*(-i%period) + Gradients[i/period][j/period+1].y*(period-j%period) ;		

	noisevalue = noise1 + noise2 + noise3 + noise4; // replace with interpolation!!
	noisevalue = noisevalue/period * amplitude;	
	TileMap[i][j].Height += (int)round(noisevalue*128);

}

}



// prepare for next iteration
amplitude *= persistency;
eriod /= 2;
}



