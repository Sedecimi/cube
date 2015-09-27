#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>
#include <iostream>
#include "shaders.h"

using namespace std;
using namespace glm;

int main(){
/*	static const GLfloat buffer_data[] = {
		-0.5f, -0.678f, 0.0f,
   		0.5f, -0.678f, 0.0f,
   		0.0f,  0.678f, 0.0f,
	};*/
	static const GLfloat buffer_data[] = {
    	-0.5f,-0.5f,-0.5f, // Треугольник 1 : начало
    	-0.5f,-0.5f, 0.5f,
    	-0.5f, 0.5f, 0.5f, // Треугольник 1 : конец
    	0.5f, 0.5f,-0.5f, // Треугольник 2 : начало
    	-0.5f,-0.5f,-0.5f,
    	-0.5f, 0.5f,-0.5f, // Треугольник 2 : конец
    	0.5f,-0.5f, 0.5f,
    	-0.5f,-0.5f,-0.5f,
    	0.5f,-0.5f,-0.5f,
    	0.5f, 0.5f,-0.5f,
    	0.5f,-0.5f,-0.5f,
    	-0.5f,-0.5f,-0.5f,
    	-0.5f,-0.5f,-0.5f,
    	-0.5f, 0.5f, 0.5f,
    	-0.5f, 0.5f,-0.5f,
    	0.5f,-0.5f, 0.5f,
    	-0.5f,-0.5f, 0.5f,
    	-0.5f,-0.5f,-0.5f,
    	-0.5f, 0.5f, 0.5f,
    	-0.5f,-0.5f, 0.5f,
    	0.5f,-0.5f, 0.5f,
    	0.5f, 0.5f, 0.5f,
    	0.5f,-0.5f,-0.5f,
    	0.5f, 0.5f,-0.5f,
    	0.5f,-0.5f,-0.5f,
    	0.5f, 0.5f, 0.5f,
    	0.5f,-0.5f, 0.5f,
    	0.5f, 0.5f, 0.5f,
    	0.5f, 0.5f,-0.5f,
    	-0.5f, 0.5f,-0.5f,
    	0.5f, 0.5f, 0.5f,
    	-0.5f, 0.5f,-0.5f,
    	-0.5f, 0.5f, 0.5f,
   		0.5f, 0.5f, 0.5f,
    	-0.5f, 0.5f, 0.5f,
    	0.5f,-0.5f, 0.5f
	};
/* COLOR */
	static const GLfloat g_color_buffer_data[] = {
    	0.583f,  0.771f,  0.014f,
    	0.609f,  0.115f,  0.436f,
    	0.327f,  0.483f,  0.844f,
    	0.822f,  0.569f,  0.201f,
    	0.435f,  0.602f,  0.223f,
    	0.310f,  0.747f,  0.185f,
    	0.597f,  0.770f,  0.761f,
    	0.559f,  0.436f,  0.730f,
    	0.359f,  0.583f,  0.152f,
    	0.483f,  0.596f,  0.789f,
    	0.559f,  0.861f,  0.639f,
    	0.195f,  0.548f,  0.859f,
    	0.014f,  0.184f,  0.576f,
    	0.771f,  0.328f,  0.970f,
    	0.406f,  0.615f,  0.116f,
    	0.676f,  0.977f,  0.133f,
    	0.971f,  0.572f,  0.833f,
    	0.140f,  0.616f,  0.489f,
    	0.997f,  0.513f,  0.064f,
    	0.945f,  0.719f,  0.592f,
    	0.543f,  0.021f,  0.978f,
    	0.279f,  0.317f,  0.505f,
    	0.167f,  0.620f,  0.077f,
    	0.347f,  0.857f,  0.137f,
    	0.055f,  0.953f,  0.042f,
    	0.714f,  0.505f,  0.345f,
    	0.783f,  0.290f,  0.734f,
    	0.722f,  0.645f,  0.174f,
    	0.302f,  0.455f,  0.848f,
    	0.225f,  0.587f,  0.040f,
    	0.517f,  0.713f,  0.338f,
    	0.053f,  0.959f,  0.120f,
    	0.393f,  0.621f,  0.362f,
    	0.673f,  0.211f,  0.457f,
    	0.820f,  0.883f,  0.371f,
    	0.982f,  0.099f,  0.879f
	};
	if(!glfwInit()){
		cout << "Error\n";
		return 1;
	}
//	glfwWindowHint(GLFW_FSAA_SAMPLES, 4); // 4x Сглаживание
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "POLTORA POLIGONA",NULL, NULL );//glfwGetPrimaryMonitor(), nullptr); // Fullscreen
	if (!window) {
    	cout << "ERROR: could not open window with GLFW3\n";
    	glfwTerminate();
    	return 1;
  	}
	glfwMakeContextCurrent (window);
	
cout << "Do color buffer" << endl;
/****COLOR BUFFER****/
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
 	cout << "Done" << endl;	

	GLuint	vao;  //Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data),buffer_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
		3,                  // Размер
		GL_FLOAT,           // Тип
		GL_FALSE,           // Указывает, что значения не нормализованы
		0,                  // Шаг
		(void*)0            // Смещение массива в буфере
	);
	glEnableVertexAttribArray(1); //Буфер цвета
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
    	1,                                // Атрибут. Здесь необязательно указывать 1, но главное, чтобы это значение совпадало с layout в шейдере..
    	3,                                // Размер
    	GL_FLOAT,                         // Тип
    	GL_FALSE,                         // Нормализован?
   		0,                                // Шаг
    	(void*)0                          // Смещение
	);	
	glEnable (GL_DEPTH_TEST); // enable depth-testing
  	glDepthFunc (GL_LESS); // depth-testing interprets a sma
  	glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
	GLuint ProgramID  = LoadShaders("./vertexShader.sp", "./fragmentShader.sp");
	//Передаем матрицу в шейдер
/* Work with matirx */
	mat4 Projection = perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	mat4 View = lookAt(  //Camera Matrix
    		vec3(4,3,0), // Камера находится в мировых координатах (4,3,3)
    		vec3(0,0,0), // И направлена в начало координат
    		vec3(0,1,0)  // "Голова" находится сверху
	);
	//Еденичная матрица модели
	mat4 Model = mat4(1.0f);
	mat4 MVP = Projection * View * Model;
/* End matrix */
	GLint MatrixID = glGetUniformLocation(ProgramID, "MVP");
	if(MatrixID < 0){
		cout << "MatrixID -1" << endl;		return 1;
	}
	if(MatrixID != -1){
		cout << "MVP Found!" << endl;
	}
	float * mvp_ptr = value_ptr(MVP);
	glUniformMatrix4fv(MatrixID, 1, GL_TRUE, mvp_ptr);
	cout << "Начинаем рисовать" << endl;
	while (!(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)){
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(ProgramID);
  		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36); 
		glfwSwapBuffers (window);
		glfwPollEvents ();
	}
 	glfwTerminate();	                                 
	return 0;
}
