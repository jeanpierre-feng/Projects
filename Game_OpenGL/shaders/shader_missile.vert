#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normale;
layout (location = 2) in vec3 color;

uniform vec4 translation_missile;
uniform mat4 rotation_missile;
uniform vec4 rotation_center_missile;
uniform mat4 projection_missile;

out vec3 coordonnee_3d;
out vec3 coordonnee_3d_locale;
out vec3 vnormale;
out vec3 vcolor;

//Un Vertex Shader minimaliste
void main (void)
{
  //Les coordonnees 3D du sommet
  coordonnee_3d = position;

  //Coordonnees du sommet
  vec4 p = rotation_missile*(vec4(position, 1.0)-rotation_center_missile)+ rotation_center_missile + translation_missile;
  coordonnee_3d_locale = p.xyz;

  //Projection du sommet
  p = projection_missile*p;

  //Gestion des normales
  vec4 n = rotation_missile*vec4(normale, 0.0);
  vnormale = n.xyz;

  // Gestion des couleurs 
  vcolor = color; 

  //position dans l'espace ecran
  gl_Position = p;
}
