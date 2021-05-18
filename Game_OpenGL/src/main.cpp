/*****************************************************************************\
 * TP CPE, 4ETI, TP synthese d'images
 * --------------
 *
 * Programme principal des appels OpenGL
 \*****************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include<sstream>

#define GLEW_STATIC 1
#include <GL/glew.h>

#if defined(__APPLE__)
#include <OpenGL/gl3.h>
#define __gl_h_
#include <GLUT/glut.h>
#define MACOSX_COMPATIBILITY GLUT_3_2_CORE_PROFILE
#else
#include <GL/glut.h>
#define MACOSX_COMPATIBILITY 0
#endif

#include "glhelper.hpp"
#include "mat4.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "triangle_index.hpp"
#include "vertex_opengl.hpp"
#include "image.hpp"
#include "mesh.hpp"

/*****************************************************************************/
 // Variables globales
bool start = false;

 //*****************************************************************************/

//identifiant des shaders
    //DINO
GLuint shader_program_id;
    //CIBLE
GLuint shader_program_id2;
    //MISSILE
GLuint shader_program_id3;
    //TEXTE
GLuint gui_program_id;


//l'identifiant de LA CIBLE 
GLuint vao = 0;
GLuint vbo = 0;
GLuint vboi = 0;

//les parametres de translations DE LA CIBLE
float translation_x = 0.0f;
float translation_y = 0.0f;
float translation_z = -10.0f;

float angle_x = 0.0f;
float angle_y = 0.0f;

//l'identifiant du MISSILE
GLuint vao2 = 0;
GLuint vbo2 = 0;
GLuint vboi2 = 0;

//les parametres de translations DU MISSILE
float translation_missile_x = 0.0f;
float translation_missile_y = 0.0f;
float translation_missile_z = -3.0f;

float angle_x_missile = 0.0f;
float angle_y_missile = 0.0f;

bool lancer = false;

//Nombre de point de vie et touch a
int pv_max = 2;
int point = 2;
int counter_touch_a = 0;

//Matrice de rotation
mat4 rotation;
mat4 rotation_missile;

//Matrice de transformation
struct transformation
{
  mat4 rotation;
  vec3 rotation_center;
  vec3 translation;

  transformation():rotation(),rotation_center(),translation(){}
};

//Informations correspondants à un model
struct model
{
  GLuint vao = 0;
  GLuint texture_id=0;
  int nbr_triangle;
  transformation transformation_model;
  vec3 angle = vec3(0.0f,0.0f,0.0f); // angle suivant x, y et z
  // rotation autour de y non implémentée
};

//Liste des modèls
model model_dinosaure;
model model_sol;

//Transformation de la vue (camera)
transformation transformation_view;
float angle_view = 0.0f;

//Transformation de la vue (MISSILE)
vec3 rotation_center_missile;
//float angle_missile = 0.0f;

//Matrice de projection
mat4 projection;
mat4 projection_missile;

// Prototype focntion pour DINO
void load_texture(const char* filename,GLuint *texture_id,GLuint program_id);

void init_model_1();
void init_model_2();

void draw_model(model model_id);

// Text drawing Structure
struct text {
    GLuint vao = 0;              // Vertex array id
    GLuint texture_id = 0;       // Well, texture id...
    std::string value;           // Value of the text to display
    vec2 bottomLeft;
    vec2 topRight;
};
text text_to_draw;
// Prototype fonction pour TEXT
void init_text(text* t);
void draw_texts(text* text_t);

//Prototype void reset();
void pause();
void reset();
void game_over();

void pause() {
    start = false;
}
void reset() {
    //reset des variables globales 
    start = false;
    lancer = false;
    //reset le dinosaure
    model_dinosaure.transformation_model.translation.z = -20.0f;
    //Reset la cible
    translation_z = -10.0f;
    translation_y = 0.0f;
    translation_x = 0.0f;
    angle_x = 0.0f;
    angle_y = 0.0f;
    //Reset le missile
    translation_missile_z = -3.0f;
    translation_missile_y = 0.0f;
    translation_missile_x = 0.0f;
    angle_x_missile = 0.0f;
    angle_y_missile = 0.0f;
    //reset les points de vie
    point = pv_max;


}

void game_over() {
    //reset des variables globales 
    start = false;
    lancer = false;
    //Reset la cible
    translation_z = -10.0f;
    translation_y = 0.0f;
    translation_x = 0.0f;
    angle_x = 0.0f;
    angle_y = 0.0f;
    //Reset le missile
    translation_missile_z = -3.0f;
    translation_missile_y = 0.0f;
    translation_missile_x = 0.0f;
    angle_x_missile = 0.0f;
    angle_y_missile = 0.0f;
    //reset les points de vie
    point = pv_max;
}

static void init()
{ // Sommets pour la CIBLE
    float sommets[] = { 0.0f,0.0f,0.3f,
      1.0f,0.0f,0.3f,
      0.0f,1.0f,0.3f,
      0.0f,0.0f,1.3f,
      
      1.0f,1.0f,1.0f,
      1.5f,1.0f,1.0f,
      1.0f,1.5f,1.0f,
      1.0f,1.0f,1.5f,
      
    };

    unsigned int index[] = { 0,1,2,
      0,1,3,
      4,5,6,
      4,5,7};

    //coordonnees geometriques des sommets missile
    vec3 p0 = vec3(-0.05f, -0.4f, 2.0f);
    vec3 p1 = vec3(0.05f, -0.4f, 2.0f);
    vec3 p2 = vec3(-0.05f, -0.5f, 2.0f);
    vec3 p3 = vec3(0.05f, -0.5f, 2.0f);
    vec3 p4 = vec3(0.05f, -0.4f, 2.15f);
    vec3 p5 = vec3(0.05f, -0.5f, 2.15f);
    vec3 p6 = vec3(-0.05f,-0.5f, 2.15f);
    vec3 p7 = vec3(-0.05f, -0.4f, 2.15f);

    //normales pour chaque sommet MISSILE
    vec3 n0 = vec3(-0.5f, -0.5f, 0.5f);
    vec3 n1 = vec3(-0.25f, -0.25f, 0.8535f);
    vec3 n2 = vec3(-0.25f, -0.25f, 0.8535f);
    vec3 n3 = vec3(-0.5, -0.5, 0.707);
    vec3 n4 = vec3(-0.5, -0.5, 0.707);
    vec3 n5 = vec3(-0.25f, -0.25f, 0.8535f);
    vec3 n6 = vec3(-0.5f, -0.5f, 0.5f);
    vec3 n7 = vec3(-0.25f, -0.25f, 0.8535f);

    //couleur pour chaque sommet MISSILE
    vec3 c0 = vec3(0.0f, 0.0f, 0.0f);
    vec3 c1 = vec3(1.0f, 0.0f, 0.0f);
    vec3 c2 = vec3(0.0f, 1.0f, 0.0f);
    vec3 c3 = vec3(1.0f, 1.0f, 0.0f);
    vec3 c4 = vec3(0.0f, 1.0f, 1.0f);
    vec3 c5 = vec3(0.5f, 1.0f, 0.3f);
    vec3 c6 = vec3(0.25f, 1.0f, 0.5f);
    vec3 c7 = vec3(1.0f, 0.6f, 0.35f);

    //tableau entrelacant coordonnees-normales MISSILE
    vec3 geometrie[] = { p0,n0,c0 , p1,n1,c1 , p2,n2,c2 , p3,n3,c3, p4,n4,c4  , p5,n5,c5 , p6,n6,c6  ,p7,n7,c7 };


    //indice des triangles
    triangle_index tri0 = triangle_index(0, 1, 2);
    triangle_index tri1 = triangle_index(1, 3, 2);
    triangle_index tri2 = triangle_index(1, 4, 5);
    triangle_index tri3 = triangle_index(1, 3, 5);
    triangle_index tri4 = triangle_index(0, 7, 6);
    triangle_index tri5 = triangle_index(0, 2, 6);
    triangle_index tri6 = triangle_index(7, 4, 6);
    triangle_index tri7 = triangle_index(4, 5, 6);
    triangle_index tri8 = triangle_index(2, 6, 5);
    triangle_index tri9 = triangle_index(2, 3, 5);
    triangle_index tri10 = triangle_index(0, 7, 4);
    triangle_index tri11 = triangle_index(0, 1, 4);


    triangle_index index_missile[] = { tri0,tri1,tri2,tri3,tri4,tri5,tri6,tri7,tri8,tri9,tri10,tri11 };

    //*******************TEXT**************************************************************************//
//**************************************************************************************************//
    gui_program_id = glhelper::create_program_from_file(
        "shaders/shader_text.vert",
        "shaders/shader_text.frag"); CHECK_GL_ERROR();

    text_to_draw.value = "READY";
    text_to_draw.bottomLeft = vec2(-0.2, 0.5);
    text_to_draw.topRight = vec2(0.2, 1);
    glUseProgram(gui_program_id);
    init_text(&text_to_draw);



    //*******************CILBE**************************************************************************//
    //**************************************************************************************************//

    //attribution d'une liste d'état (1 indique la création d'une seule liste)
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //attribution d'un buffer de donnees (1 indique la création d'un seul buffer)
    glGenBuffers(1, &vbo); CHECK_GL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER, vbo); CHECK_GL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER, sizeof(sommets), sommets, GL_STATIC_DRAW); CHECK_GL_ERROR();

    // Active l'utilisation des données de positions (le 0 correspond à la location dans le vertex shader)
    glEnableVertexAttribArray(0); CHECK_GL_ERROR();
    // Indique comment le buffer courant (dernier vbo "bindé") est utilisé pour les positions des sommets
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERROR();

    //attribution d'un autre buffer de donnees
    glGenBuffers(1, &vboi); CHECK_GL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi); CHECK_GL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW); CHECK_GL_ERROR();

    // Chargement du shader_cible
    shader_program_id2 = glhelper::create_program_from_file(
        "shaders/shader_cible.vert",
        "shaders/shader_cible.frag"); CHECK_GL_ERROR();
    glUseProgram(shader_program_id2);

    //*******************MISSILE**************************************************************************//
     //**************************************************************************************************//

    //attribution d'une liste d'état (1 indique la création d'une seule liste)
    glGenVertexArrays(1, &vao2);
    glBindVertexArray(vao2);

    //attribution d'un buffer de donnees (1 indique la création d'un seul buffer)
    glGenBuffers(1, &vbo2); CHECK_GL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER, vbo2); CHECK_GL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER, sizeof(geometrie), geometrie, GL_STATIC_DRAW); CHECK_GL_ERROR();

    // Active l'utilisation des données de positions (le 0 correspond à la location dans le vertex shader)
    glEnableVertexAttribArray(0); CHECK_GL_ERROR();
    // Indique comment le buffer courant (dernier vbo "bindé") est utilisé pour les positions des sommets
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(vec3), 0); CHECK_GL_ERROR();

    // Active l'utilisation des données de normales (le 1 correspond à la location dans le vertex shader)
    glEnableVertexAttribArray(1); CHECK_GL_ERROR();
    // Indique comment le buffer courant (dernier vbo "bindé") est utilisé pour les normales des sommets
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(vec3), (void*)sizeof(vec3)); CHECK_GL_ERROR();

    // Active l'utilisation des données de normales (le 2 correspond à la location dans le vertex shader)
    glEnableVertexAttribArray(2); CHECK_GL_ERROR();
    // Indique comment le buffer courant (dernier vbo "bindé") est utilisé pour les couleurs des sommets
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(vec3), (void*)(2 * sizeof(vec3))); CHECK_GL_ERROR();

    //attribution d'un autre buffer de donnees
    glGenBuffers(1, &vboi2); CHECK_GL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi2); CHECK_GL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_missile), index_missile, GL_STATIC_DRAW); CHECK_GL_ERROR();

    // Chargement du shader_missible
    shader_program_id3 = glhelper::create_program_from_file(
        "shaders/shader_missile.vert",
        "shaders/shader_missile.frag"); CHECK_GL_ERROR();
    glUseProgram(shader_program_id3);


    //*******************DINOSAURE**************************************************************************//
     //**************************************************************************************************//

  // Chargement du shader
  shader_program_id = glhelper::create_program_from_file(
      "shaders/shader.vert",
      "shaders/shader.frag"); CHECK_GL_ERROR();
  glUseProgram(shader_program_id);



  //matrice de projection
  projection = matrice_projection(60.0f*M_PI/180.0f,1.0f,0.01f,100.0f);
  GLint loc_projection = glGetUniformLocation(shader_program_id, "projection"); CHECK_GL_ERROR();
  if (loc_projection == -1) std::cerr << "Pas de variable uniforme : projection" << std::endl;
  glUniformMatrix4fv(loc_projection,1,false,pointeur(projection)); CHECK_GL_ERROR();

  //centre de rotation de la 'camera' (les objets sont centres en z=-2)
  transformation_view.rotation_center = vec3(0.0f,0.0f,-2.0f);

  //centre de rotation du missile 
  rotation_center_missile = vec3(0.0f, -0.45f, 2.075f);

  //activation de la gestion de la profondeur
  glEnable(GL_DEPTH_TEST); CHECK_GL_ERROR();



  // Charge modele 1 sur la carte graphique
  init_model_1();
  // Charge modele 2 sur la carte graphique
  init_model_2();


}

//Fonction d'affichage
static void display_callback()
{
  //effacement des couleurs du fond d'ecran
  glClearColor(0.5f, 0.6f, 0.9f, 1.0f); CHECK_GL_ERROR();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CHECK_GL_ERROR();



  /// <summary>
  ///                           CIBLE
  /// </summary>
  glUseProgram(shader_program_id2);
  glBindVertexArray(vao);

  //envoie des parametres sur la carte graphique
  GLint loc_rotation = glGetUniformLocation(shader_program_id2, "rotation");
  if (loc_rotation == -1) std::cerr << "Pas de variable uniforme : rotation" << std::endl;
  glUniformMatrix4fv(loc_rotation, 1, false, pointeur(rotation));

  GLint loc_translation = glGetUniformLocation(shader_program_id2, "translation");
  if (loc_translation == -1) std::cerr << "Pas de variable uniforme : translation" << std::endl;
  glUniform4f(loc_translation, translation_x, translation_y, translation_z, 0.0f);

  //matrice de projection CIBLE
  GLint loc_projection = glGetUniformLocation(shader_program_id2, "projection"); CHECK_GL_ERROR();
  if (loc_projection == -1) std::cerr << "Pas de variable uniforme : projection" << std::endl;
  glUniformMatrix4fv(loc_projection, 1, false, pointeur(projection)); CHECK_GL_ERROR();

  glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);

  /// <summary>
///                           MISSILE
/// </summary>
  glUseProgram(shader_program_id3);
  glBindVertexArray(vao2);

  //envoie des parametres sur la carte graphique
  GLint loc_rotation_missile = glGetUniformLocation(shader_program_id3, "rotation_missile"); CHECK_GL_ERROR();
  if (loc_rotation_missile == -1) std::cerr << "Pas de variable uniforme : rotation_missile" << std::endl;
  glUniformMatrix4fv(loc_rotation_missile, 1, false, pointeur(rotation_missile)); CHECK_GL_ERROR();

  //envoie du centre de rotation MISSILE
  vec3 cv2 = rotation_center_missile;
  GLint loc_rotation_center_missile = glGetUniformLocation(shader_program_id3, "rotation_center_missile"); CHECK_GL_ERROR();
  if (loc_rotation_center_missile == -1) std::cerr << "Pas de variable uniforme : rotation_center_missile" << std::endl;
  glUniform4f(loc_rotation_center_missile, cv2.x, cv2.y, cv2.z, 0.0f); CHECK_GL_ERROR();

  GLint loc_translation_missile = glGetUniformLocation(shader_program_id3, "translation_missile"); CHECK_GL_ERROR();
  if (loc_translation_missile == -1) std::cerr << "Pas de variable uniforme : translation_missile" << std::endl;
  glUniform4f(loc_translation_missile, translation_missile_x, translation_missile_y, translation_missile_z, 0.0f); CHECK_GL_ERROR();

  //matrice de projection MSSILE
  projection_missile = matrice_projection(60.0f * M_PI / 180.0f, 1.0f, 0.01f, 100.0f);
  GLint loc_projection_missile = glGetUniformLocation(shader_program_id3, "projection_missile"); CHECK_GL_ERROR();
  if (loc_projection_missile == -1) std::cerr << "Pas de variable uniforme : projection_missile" << std::endl;
  glUniformMatrix4fv(loc_projection_missile, 1, false, pointeur(projection_missile)); CHECK_GL_ERROR();

  glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0); CHECK_GL_ERROR();
  /// <summary>
///                           CAMERA
/// </summary>
  //définie le programme à utiliser
  glUseProgram(shader_program_id);

  // Affecte les parametres uniformes de la vue (identique pour tous les modeles de la scene)
  {

    //envoie de la rotation CAMERA
    GLint loc_rotation_view = glGetUniformLocation(shader_program_id, "rotation_view"); CHECK_GL_ERROR();
    if (loc_rotation_view == -1) std::cerr << "Pas de variable uniforme : rotation_view" << std::endl;
    glUniformMatrix4fv(loc_rotation_view,1,false,pointeur(transformation_view.rotation)); CHECK_GL_ERROR();

    //envoie du centre de rotation CAMERA
    vec3 cv = transformation_view.rotation_center;
    GLint loc_rotation_center_view = glGetUniformLocation(shader_program_id, "rotation_center_view"); CHECK_GL_ERROR();
    if (loc_rotation_center_view == -1) std::cerr << "Pas de variable uniforme : rotation_center_view" << std::endl;
    glUniform4f(loc_rotation_center_view , cv.x,cv.y,cv.z , 0.0f); CHECK_GL_ERROR();

    //envoie de la translation CAMERA
    vec3 tv = transformation_view.translation;
    GLint loc_translation_view = glGetUniformLocation(shader_program_id, "translation_view"); CHECK_GL_ERROR();
    if (loc_translation_view == -1) std::cerr << "Pas de variable uniforme : translation_view" << std::endl;
    glUniform4f(loc_translation_view , tv.x,tv.y,tv.z , 0.0f); CHECK_GL_ERROR();

 
  }

  // Affiche le modele dinosaure
  draw_model(model_dinosaure);
  // Affiche le modele sol
  draw_model(model_sol);

  glUseProgram(gui_program_id);
  glDisable(GL_DEPTH_TEST);
  draw_texts(&text_to_draw);
  glEnable(GL_DEPTH_TEST);

  //Changement de buffer d'affichage pour eviter un effet de scintillement
  glutSwapBuffers();


}







void init_text(text* t) {
    vec3 p0 = vec3(0.0f, 0.0f, 0.0f);
    vec3 p1 = vec3(0.0f, 1.0f, 0.0f);
    vec3 p2 = vec3(1.0f, 1.0f, 0.0f);
    vec3 p3 = vec3(1.0f, 0.0f, 0.0f);

    vec3 geometrie[4] = { p0, p1, p2, p3 };
    triangle_index index[2] = { triangle_index(0, 1, 2), triangle_index(0, 2, 3) };

    glGenVertexArrays(1, &(t->vao));                                              CHECK_GL_ERROR();
    glBindVertexArray(t->vao);                                                  CHECK_GL_ERROR();

    GLuint vbo;
    glGenBuffers(1, &vbo);                                                       CHECK_GL_ERROR();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                          CHECK_GL_ERROR();
    glBufferData(GL_ARRAY_BUFFER, sizeof(geometrie), geometrie, GL_STATIC_DRAW);   CHECK_GL_ERROR();

    glEnableVertexAttribArray(0); CHECK_GL_ERROR();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERROR();

    GLuint vboi;
    glGenBuffers(1, &vboi);                                                      CHECK_GL_ERROR();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi);                                 CHECK_GL_ERROR();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);   CHECK_GL_ERROR();

    load_texture("data/fontB.tga", &t->texture_id,gui_program_id);
}


void draw_texts(text* text_t) {
    vec2 size = (text_t->topRight - text_t->bottomLeft) / float(text_t->value.size());
    //  std::cout << size << " " << text_t->bottomLeft << std::endl;

    //Send uniforma parameters

    GLint loc_size = glGetUniformLocation(gui_program_id, "size"); CHECK_GL_ERROR();
    if (loc_size == -1) std::cerr << "Pas de variable uniforme : size" << std::endl;
    glUniform2f(loc_size, size.x, size.y);    CHECK_GL_ERROR();

    glBindVertexArray(text_t->vao); CHECK_GL_ERROR();

    for (int i = 0; i < text_t->value.size(); ++i)
    {
        GLint loc_start = glGetUniformLocation(gui_program_id, "start"); CHECK_GL_ERROR();
        if (loc_start == -1) std::cerr << "Pas de variable uniforme : start" << std::endl;
        glUniform2f(loc_start, text_t->bottomLeft.x + i * size.x, text_t->bottomLeft.y);    CHECK_GL_ERROR();

        GLint loc_char = glGetUniformLocation(gui_program_id, "c"); CHECK_GL_ERROR();
        if (loc_char == -1) std::cerr << "Pas de variable uniforme : c" << std::endl;
        glUniform1i(loc_char, (int)text_t->value[i]);    CHECK_GL_ERROR();
        glBindTexture(GL_TEXTURE_2D, text_t->texture_id);                       CHECK_GL_ERROR();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);                    CHECK_GL_ERROR();
    }
}



/*****************************************************************************\
 * keyboard_callback                                                         *
 \*****************************************************************************/
static void keyboard_callback(unsigned char key, int, int)
{
  float d_angle=0.1f;
  float d2_angle = -0.1f;

  float dz=0.5f;
  float dx_missile = 0.01f;

  //quitte le programme si on appuie sur les touches 'q', 'Q', ou 'echap'
  //enregistre l'image si on appuie sur la touche 'p'
  switch (key)
  {
    case 'p':
      glhelper::print_screen();
      break;
    case 'q':
    case 'Q':
    case 27:
      exit(0);
      break;

    case 'o':
      model_dinosaure.angle.x += d_angle;
      break;
    case 'l':
      model_dinosaure.angle.x -= d_angle;
      angle_y += d_angle;
      break;
    case 'n':
        model_dinosaure.angle.x -= d_angle;
        angle_y = d2_angle;
        break;

    case 'k':
      model_dinosaure.angle.y += d_angle;
      angle_x -= d_angle;
      break;
    case 'm':
      model_dinosaure.angle.y -= d_angle;
      break;

    // CIBLE
    case 'i':
        angle_x += d_angle;
        break;
    case 'j':
        angle_y += d_angle;
        break;
    case 'y':
        translation_z += dz;
        break;
    case 'h':
        translation_z -= dz;
        break;

    // CAMERA
    case 's':
      angle_view += d_angle;
      break;
    case 'f':
      angle_view -= d_angle;
      break;
    case 'e':
      transformation_view.translation.z += dz;
      break;
    case 'd':
      transformation_view.translation.z -= dz;
      break;



    // Controle sur le missile
    case 'w'://Translation à gauche
        translation_missile_x -= dx_missile;
        break;
    case 'c'://Translation à droite
        translation_missile_x += dx_missile;
        break;
    case 'x'://Lancer le missile
        lancer = true;
        break;

    // Touche START/RESTART   PAUSE  et   RESET
    case 'v': // START et RESTART
        start = true;
        text_to_draw.value = " ";

        break;
    case 't': //PAUSE
        pause();
        text_to_draw.value = "PAUSE";
        text_to_draw.bottomLeft = vec2(-0.2, 0.5);
        text_to_draw.topRight = vec2(0.2, 1);

        break;
    case 'r': //RESET
        reset();
        text_to_draw.value = "RESET";
        text_to_draw.bottomLeft = vec2(-0.2, 0.5);
        text_to_draw.topRight = vec2(0.2, 1);
        break;

    // Afficher les différents touches possible
    case 'a':
        pause();
        counter_touch_a++;
        if (counter_touch_a == 1) {
            text_to_draw.value = " V : START/RESTART  ";

        }
        if (counter_touch_a == 2) {
            text_to_draw.value = " X : SHOOT  ";

        }
        if (counter_touch_a == 3) {
            text_to_draw.value = " W : MOVE LEFT ";

        }
        if (counter_touch_a == 4) {
            text_to_draw.value = " C : MOVE RIGHT";

        }
        if (counter_touch_a == 5) {
            text_to_draw.value = " R : RESET ";

        }
        if (counter_touch_a == 6) {
            text_to_draw.value = " T :PAUSE ";

        }
        if (counter_touch_a == 7) {
            counter_touch_a = 0;
        }

        text_to_draw.bottomLeft = vec2(-0.75, 0);//(bottom;left)
        text_to_draw.topRight = vec2(0.75 , 5);//(rigth;top)
        break;

  }
  mat4 rotation_x = matrice_rotation(angle_x, 1.0f, 0.0f, 0.0f);
  mat4 rotation_y = matrice_rotation(angle_y, 0.0f, 1.0f, 0.0f);
  rotation = rotation_x * rotation_y;

  mat4 rotation_missile_x = matrice_rotation(angle_x_missile, 1.0f, 0.0f, 0.0f);
  mat4 rotation_missile_y = matrice_rotation(angle_y_missile, 0.0f, 1.0f, 0.0f);
  rotation_missile = rotation_missile_x * rotation_missile_y;

  model_dinosaure.transformation_model.rotation = matrice_rotation(model_dinosaure.angle.y, 0.0f,1.0f,0.0f) * matrice_rotation(model_dinosaure.angle.x, 1.0f,0.0f,0.0f);
  transformation_view.rotation = matrice_rotation(angle_view , 0.0f,1.0f,0.0f);
  // Des exemples de camera vous sont données dans le programme 10

}

/*****************************************************************************\
 * special_callback                                                          *
 \*****************************************************************************/
static void special_callback(int key, int,int)
{
  float dL=0.03f;
  float dz = 0.5f;
  switch (key)
  {
    case GLUT_KEY_UP:
      model_dinosaure.transformation_model.translation.y += dL; //rotation avec la touche du haut
      transformation_view.translation.z -= dz;
      break;
    case GLUT_KEY_DOWN:
      model_dinosaure.transformation_model.translation.y -= dL; //rotation avec la touche du bas
      transformation_view.translation.z += dz;
      break;
    case GLUT_KEY_LEFT:
      model_dinosaure.transformation_model.translation.x -= dL; //rotation avec la touche de gauche
      break;
    case GLUT_KEY_RIGHT:
      model_dinosaure.transformation_model.translation.x += dL; //rotation avec la touche de droite
      break;
  }
}


/*****************************************************************************\
 * timer_callback                                                            *
 \*****************************************************************************/
static void timer_callback(int)
{
  //demande de rappel de cette fonction dans 25ms
  glutTimerFunc(25, timer_callback, 0);
  
  //Lancement du jeu si start = true c'est à dire lorsque appuie sur la touche V
  if (start == true) {
      static int counter_step_hit = 0;

      //Affichage du nombre de point de vie du dinosaure, actualisé lorsqu'on réussi à toucher la cible 
      if (counter_step_hit == 0) {
          std::ostringstream oss;
          oss << "PV CIBLE: " << point;
          text_to_draw.value = oss.str();
          text_to_draw.bottomLeft = vec2(-1, 0.5);//(bottom;left)
          text_to_draw.topRight = vec2(-0.5, 1.5);//(rigth;top)
      }
      
      //Fait avancer le dino jusqu'à la défaite
      model_dinosaure.transformation_model.translation.z += 0.01f;
      if (model_dinosaure.transformation_model.translation.z > 1.5) {
          game_over();
          text_to_draw.value = "GAME OVER";
          text_to_draw.bottomLeft = vec2(-0.75, 0);//(bottom;left)
          text_to_draw.topRight = vec2(0.75 , 5);//(rigth;top)
      }
      
      // Mettre en mouvement la cible continuellement
      angle_x += 0.1;

      if (translation_x < 7.5f) {
          angle_y -= 0.1f;
          translation_x += 0.05f;
      }
      else if (translation_x > 7.5f) {
          angle_y -= 0.1f;
          translation_x = -7.5f;
      }

      //Permet de lancer le missile et de le réinitialiser lorsqu'il atteint une certaines longueur
      if (lancer == true && translation_missile_z > -20.0f) {
          angle_x_missile -= 0.2f;      //Rotation
          translation_missile_z -= 0.1; //Translation en z
          //Trajectoire parabolique
          translation_missile_y = -0.0245f * (translation_missile_z + 6.5f) * (translation_missile_z + 6.5f) + 0.3f;

      }
      //Réinitialise la position du missile si il a atteint une certiane distance en z  
      else if (translation_missile_z < -20.0f) {
          translation_missile_z = -3.0f;
          translation_missile_y = 0.0f;
          lancer = false;
      }
      // Affichage des caractères "HIT" pendant un certain temps
      if (counter_step_hit > 0) {
          counter_step_hit--;
          if (counter_step_hit == 0) {
              text_to_draw.value = " ";
          }
      }

      //Détecter si le missile à toucher la cible 
      if (lancer == true) { 
          vec3 pos_missile(translation_missile_x, translation_missile_y, translation_missile_z);
          vec3 pos_cible(translation_x, translation_y,translation_z);
          vec3 v = pos_missile-pos_cible; //Distance entre la cible et le missile 
          float hit_distance = 2.5;

          //Si la distance entre la cible et le missile est inférieur à une certaine valeur alors on considère qu'on la toucher
          if (norm(v) < hit_distance ) {
              point--;
              text_to_draw.value = "HIT";
              text_to_draw.bottomLeft = vec2(-0.2, 0.5);
              text_to_draw.topRight = vec2(0.2, 1);
              counter_step_hit = 15;
              //Réinitialise le missile lorsqu'on à toucher la cible 
              lancer = false;
              translation_missile_x = 0.0f;
              translation_missile_y = 0.0f;
              translation_missile_z = -3.0;
          }
      }
      //Victoire
      if (point == 0) {
          reset();
          text_to_draw.value = "VICTORY";
          text_to_draw.bottomLeft = vec2(-0.75, 0);//(bottom;left)
          text_to_draw.topRight = vec2(0.75, 5);//(rigth;top)
      }

      //Reinitialise le counter_touch_a
      if (counter_touch_a == 7) {
            counter_touch_a = 0;
      }
  }


 
  mat4 rotation_x = matrice_rotation(angle_x, 1.0f, 0.0f, 0.0f);
  mat4 rotation_y = matrice_rotation(angle_y, 0.0f, 1.0f, 0.0f);
  rotation = rotation_x * rotation_y;

  mat4 rotation_missile_x = matrice_rotation(angle_x_missile, 1.0f, 0.0f, 0.0f);
  mat4 rotation_missile_y = matrice_rotation(angle_y_missile, 0.0f, 1.0f, 0.0f);
  rotation_missile = rotation_missile_x * rotation_missile_y;


  //reactualisation de l'affichage
  glutPostRedisplay();
}

int main(int argc, char** argv)
{
  //**********************************************//
  //Lancement des fonctions principales de GLUT
  //**********************************************//

  //initialisation
  glutInit(&argc, argv);

  //Mode d'affichage (couleur, gestion de profondeur, ...)
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | MACOSX_COMPATIBILITY);

  //Taille de la fenetre a l'ouverture
  glutInitWindowSize(600, 600);

  //Titre de la fenetre
  glutCreateWindow("OpenGL");

  //Fonction de la boucle d'affichage
  glutDisplayFunc(display_callback);

  //Fonction de gestion du clavier
  glutKeyboardFunc(keyboard_callback);

  //Fonction des touches speciales du clavier (fleches directionnelles)
  glutSpecialFunc(special_callback);

  //Fonction d'appel d'affichage en chaine
  glutTimerFunc(25, timer_callback, 0);

  //Option de compatibilité
  glewExperimental = true;

  //Initialisation des fonctions OpenGL
  glewInit();

  //Affiche la version openGL utilisée
  std::cout << "OpenGL: " << (GLchar *)(glGetString(GL_VERSION)) << std::endl;

  //Notre fonction d'initialisation des donnees et chargement des shaders
  init();
 


  //Lancement de la boucle (infinie) d'affichage de la fenetre
  glutMainLoop();

  //Plus rien n'est execute apres cela
  return 0;
}

void draw_model(model m)
{

  //envoie des parametres uniformes
  {
    GLint loc_rotation_model = glGetUniformLocation(shader_program_id, "rotation_model"); CHECK_GL_ERROR();
    if (loc_rotation_model == -1) std::cerr << "Pas de variable uniforme : rotation_model" << std::endl;
    glUniformMatrix4fv(loc_rotation_model,1,false,pointeur(m.transformation_model.rotation));    CHECK_GL_ERROR();

    vec3 c = m.transformation_model.rotation_center;
    GLint loc_rotation_center_model = glGetUniformLocation(shader_program_id, "rotation_center_model"); CHECK_GL_ERROR();
    if (loc_rotation_center_model == -1) std::cerr << "Pas de variable uniforme : rotation_center_model" << std::endl;
    glUniform4f(loc_rotation_center_model , c.x,c.y,c.z , 0.0f);                                 CHECK_GL_ERROR();

    vec3 t = m.transformation_model.translation;
    GLint loc_translation_model = glGetUniformLocation(shader_program_id, "translation_model"); CHECK_GL_ERROR();
    if (loc_translation_model == -1) std::cerr << "Pas de variable uniforme : translation_model" << std::endl;
    glUniform4f(loc_translation_model , t.x,t.y,t.z , 0.0f);                                     CHECK_GL_ERROR();
  }

  glBindVertexArray(m.vao);CHECK_GL_ERROR();

  //affichage
  {
    glBindTexture(GL_TEXTURE_2D, m.texture_id);                             CHECK_GL_ERROR();
    glDrawElements(GL_TRIANGLES, 3*m.nbr_triangle, GL_UNSIGNED_INT, 0);     CHECK_GL_ERROR();
  }
}

void init_model_1()
{
  // Chargement d'un maillage a partir d'un fichier
  mesh m = load_obj_file("data/stegosaurus.obj");

  // Affecte une transformation sur les sommets du maillage
  float s = 0.2f;
  mat4 transform = mat4(   s, 0.0f, 0.0f, 0.0f,
      0.0f,    s, 0.0f,-0.9f,
      0.0f, 0.0f,   s ,-2.0f,
      0.0f, 0.0f, 0.0f, 1.0f);
  apply_deformation(&m,transform);

  // Centre la rotation du modele 1 autour de son centre de gravite approximatif
  model_dinosaure.transformation_model.rotation_center = vec3(0.0f,-0.5f,-2.0f);
  model_dinosaure.transformation_model.translation.z = -20.0f;


  // Calcul automatique des normales du maillage
  update_normals(&m);
  // Les sommets sont affectes a une couleur blanche
  fill_color(&m,vec3(1.0f,1.0f,1.0f));

  //attribution d'une liste d'état (1 indique la création d'une seule liste)
  glGenVertexArrays(1, &model_dinosaure.vao);
  glBindVertexArray(model_dinosaure.vao);

  GLuint vbo;
  //attribution d'un buffer de donnees (1 indique la création d'un buffer)
  glGenBuffers(1,&vbo); CHECK_GL_ERROR();
  //affectation du buffer courant
  glBindBuffer(GL_ARRAY_BUFFER,vbo); CHECK_GL_ERROR();
  //copie des donnees des sommets sur la carte graphique
  glBufferData(GL_ARRAY_BUFFER,m.vertex.size()*sizeof(vertex_opengl),&m.vertex[0],GL_STATIC_DRAW); CHECK_GL_ERROR();

  // Active l'utilisation des données de positions (le 0 correspond à la location dans le vertex shader)
  glEnableVertexAttribArray(0); CHECK_GL_ERROR();
  // Indique comment le buffer courant (dernier vbo "bindé") est utilisé pour les positions des sommets
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_opengl), 0); CHECK_GL_ERROR();

  // Active l'utilisation des données de normales (le 1 correspond à la location dans le vertex shader)
  glEnableVertexAttribArray(1); CHECK_GL_ERROR();
  // Indique comment le buffer courant (dernier vbo "bindé") est utilisé pour les normales des sommets
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(vertex_opengl), (void*)sizeof(vec3)); CHECK_GL_ERROR();

  // Active l'utilisation des données de couleurs (le 2 correspond à la location dans le vertex shader)
  glEnableVertexAttribArray(2); CHECK_GL_ERROR();
  // Indique comment le buffer courant (dernier vbo "bindé") est utilisé pour les couleurs des sommets
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_opengl), (void*)(2*sizeof(vec3))); CHECK_GL_ERROR();

  // Active l'utilisation des données de textures (le 3 correspond à la location dans le vertex shader)
  glEnableVertexAttribArray(3); CHECK_GL_ERROR();
  // Indique comment le buffer courant (dernier vbo "bindé") est utilisé pour les textures des sommets
  glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_opengl), (void*)(3*sizeof(vec3))); CHECK_GL_ERROR();

  GLuint vboi;
  //attribution d'un autre buffer de donnees
  glGenBuffers(1,&vboi); CHECK_GL_ERROR();
  //affectation du buffer courant (buffer d'indice)
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi); CHECK_GL_ERROR();
  //copie des indices sur la carte graphique
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,m.connectivity.size()*sizeof(triangle_index),&m.connectivity[0],GL_STATIC_DRAW); CHECK_GL_ERROR();

  // Nombre de triangles de l'objet 1
  model_dinosaure.nbr_triangle = m.connectivity.size();

  // Chargement de la texture
  load_texture("data/stegosaurus.tga",&model_dinosaure.texture_id, shader_program_id);
}

void init_model_2()
{
  //Creation manuelle du model 2

  //coordonnees geometriques des sommets
  vec3 p0=vec3(-25.0f,-0.9f,-25.0f);
  vec3 p1=vec3( 25.0f,-0.9f,-25.0f);
  vec3 p2=vec3( 25.0f,-0.9f, 25.0f);
  vec3 p3=vec3(-25.0f,-0.9f, 25.0f);

  //normales pour chaque sommet
  vec3 n0=vec3(0.0f,1.0f,0.0f);
  vec3 n1=n0;
  vec3 n2=n0;
  vec3 n3=n0;

  //couleur pour chaque sommet
  vec3 c0=vec3(1.0f,1.0f,1.0f);
  vec3 c1=c0;
  vec3 c2=c0;
  vec3 c3=c0;

  //texture du sommet
  vec2 t0=vec2(0.0f,0.0f);
  vec2 t1=vec2(1.0f,0.0f);
  vec2 t2=vec2(1.0f,1.0f);
  vec2 t3=vec2(0.0f,1.0f);

  vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
  vertex_opengl v1=vertex_opengl(p1,n1,c1,t1);
  vertex_opengl v2=vertex_opengl(p2,n2,c2,t2);
  vertex_opengl v3=vertex_opengl(p3,n3,c3,t3);

  //tableau entrelacant coordonnees-normales
  vertex_opengl geometrie[]={v0,v1,v2,v3};

  //indice des triangles
  triangle_index tri0=triangle_index(0,1,2);
  triangle_index tri1=triangle_index(0,2,3);
  triangle_index index[]={tri0,tri1};
  model_sol.nbr_triangle = 2;

  //attribution d'une liste d'état (1 indique la création d'une seule liste)
  glGenVertexArrays(1, &model_sol.vao);
  glBindVertexArray(model_sol.vao);

  GLuint vbo;
  //attribution d'un buffer de donnees (1 indique la création d'un buffer)
  glGenBuffers(1,&vbo);                                             CHECK_GL_ERROR();
  //affectation du buffer courant
  glBindBuffer(GL_ARRAY_BUFFER,vbo);                                CHECK_GL_ERROR();
  //copie des donnees des sommets sur la carte graphique
  glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW);  CHECK_GL_ERROR();

  // Active l'utilisation des données de positions (le 0 correspond à la location dans le vertex shader)
  glEnableVertexAttribArray(0); CHECK_GL_ERROR();
  // Indique comment le buffer courant (dernier vbo "bindé") est utilisé pour les positions des sommets
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_opengl), 0); CHECK_GL_ERROR();

  // Active l'utilisation des données de normales (le 1 correspond à la location dans le vertex shader)
  glEnableVertexAttribArray(1); CHECK_GL_ERROR();
  // Indique comment le buffer courant (dernier vbo "bindé") est utilisé pour les normales des sommets
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(vertex_opengl), (void*)sizeof(vec3)); CHECK_GL_ERROR();

  // Active l'utilisation des données de couleurs (le 2 correspond à la location dans le vertex shader)
  glEnableVertexAttribArray(2); CHECK_GL_ERROR();
  // Indique comment le buffer courant (dernier vbo "bindé") est utilisé pour les couleurs des sommets
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_opengl), (void*)(2*sizeof(vec3))); CHECK_GL_ERROR();

  // Active l'utilisation des données de textures (le 3 correspond à la location dans le vertex shader)
  glEnableVertexAttribArray(3); CHECK_GL_ERROR();
  // Indique comment le buffer courant (dernier vbo "bindé") est utilisé pour les textures des sommets
  glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_opengl), (void*)(3*sizeof(vec3))); CHECK_GL_ERROR();

  GLuint vboi;
  //attribution d'un autre buffer de donnees
  glGenBuffers(1,&vboi);                                            CHECK_GL_ERROR();
  //affectation du buffer courant (buffer d'indice)
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi);                       CHECK_GL_ERROR();
  //copie des indices sur la carte graphique
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW);  CHECK_GL_ERROR();


  // Chargement de la texture
  load_texture("data/grass.tga",&model_sol.texture_id,shader_program_id);

}



void load_texture(const char* filename,GLuint *texture_id,GLuint program_id)
{
  // Chargement d'une texture (seul les textures tga sont supportes)
  Image  *image = image_load_tga(filename);
  if (image) //verification que l'image est bien chargee
  {

    //Creation d'un identifiant pour la texture
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); CHECK_GL_ERROR();
    glGenTextures(1, texture_id); CHECK_GL_ERROR();

    //Selection de la texture courante a partir de son identifiant
    glBindTexture(GL_TEXTURE_2D, *texture_id); CHECK_GL_ERROR();

    //Parametres de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); CHECK_GL_ERROR();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); CHECK_GL_ERROR();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); CHECK_GL_ERROR();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); CHECK_GL_ERROR();

    //Envoie de l'image en memoire video
    if(image->type==IMAGE_TYPE_RGB){ //image RGB
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data); CHECK_GL_ERROR();}
    else if(image->type==IMAGE_TYPE_RGBA){ //image RGBA
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data); CHECK_GL_ERROR();}
    else{
      std::cout<<"Image type not handled"<<std::endl;}

    delete image;
  }
  else
  {
    std::cerr<<"Erreur chargement de l'image, etes-vous dans le bon repertoire?"<<std::endl;
    abort();
  }

  GLint loc_texture = glGetUniformLocation(program_id, "texture"); CHECK_GL_ERROR();
  if (loc_texture == -1) std::cerr << "Pas de variable uniforme : texture" << std::endl;
  glUniform1i (loc_texture,0); CHECK_GL_ERROR();
}

