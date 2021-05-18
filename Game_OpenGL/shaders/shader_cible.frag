#version 330 core

// Variable de sortie (sera utilisé comme couleur)
out vec4 color;

in vec3 coordonnee_3d;

//Un Fragment Shader minimaliste
void main (void)
{
  float x = abs(coordonnee_3d.x);
  float y = abs(coordonnee_3d.y);
  float z = abs(coordonnee_3d.z);

	vec3 p = vec3(x,y,z);
	vec3 centre1 = vec3(0.3,0.3,0);
	vec3 centre2 = vec3(0.3,0,0.3);

	if (length(p - centre1) < 0.1 ){
		x= 1;
		y= 1;
		z= 1;
	}
	else if (0.1 <length(p - centre1) && length(p - centre1)< 0.2){
		x= 0;
		y= 0.4;
		z= 0.7;
	}

	else if (0.1 <length(p - centre2) && length(p - centre2)< 0.2){
		x= 0;
		y= 0.4;
		z= 0.7;
	}
	else if (length(p - centre2) < 0.1 ){
		x= 1;
		y= 1;
		z= 1;
	}
	
	else{
		 x = abs(coordonnee_3d.x);
		 y = abs(coordonnee_3d.y);
		 z = abs(coordonnee_3d.z);
	}

	
  color = vec4(x,y,z,1.0);
}
