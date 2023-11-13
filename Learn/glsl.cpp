#include <glad/glad.h>
#include<GLFW/glfw3.h>
using namespace std;

#version version_number
in type in_variable_name;
in type in_variable_name;

out type out_variable_name;

uniform type uniform_name;

void main()
{
	//process input(s) and do some weird graphics stuff 
	//...
	//output processed stuff to output variable 
	out_variable_name = weird_stuff_
}

int nrAttributes;
glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
cout << "Maximum nr of vertex attributes supported: " << nrAttributes << endl;

vec2 someVec;
vec4 differentVec = someVec.xyxx;
vec3 anotherVec = differentVec.zyw;
vec4 otherVec = someVec.xxxx + anotherVec.yxzy;

vec2 vect = vec2(0.5, 0.7);
vec4 result = vec4(vect, 0.0, 0.0);
vec4 otherResult = vec4(result.xyz, 1.0);

#version 330 core
layout(location = 0) in vec3 aPos; // position has attribute position 0 
out vec4 vertexColor; //    specify    a    color    output to the fragment shader 
void main()
{
	gl_Position = vec4(aPos, 1.0); // we give a vec3 to vec4’s constructor 
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // output variable to dark-red
}

#version 330 core
out vec4 FragColor;

uniform vec4 ourColor; //we set this var in the OpenGL code

void main()
{
	FragColor = outColor;
}

float timeValue = glfwGetTime();
float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
int vertexColorLocation = glGetUniformLocation(shaderProgram, "outColor");
glUseProgram(shaderProgram);
glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

while (!glfwWindowShouldClose(window))
{
	//input
	processInput(window);

	//render
	// 컬러버퍼 지우기 
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//be sure to activate the shader
	glUseProgram(shaderProgram);

	//update the uniform color 
	float timeValue = glfwGetTime();
	float greenValue = sin(timeValue) / 2.0f + 0.5f; 
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	// now render triangle
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//swap buffers and poll IO events 
	glfwSwapBuffers(window);
	glfwPollEvents();

}

#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 ourColor; 

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
}

#version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main()
{
	FragColor = vec4(ourColor, 1.0);
}

//position attribute 

#ifndef SHADER_H 
#define SHADER_H
#include <glad/glad.h> 
#include <string>
#include <fstream> 
#include <sstream> 
#include <iostream>
using namespace std;

class Shader
{
	public:
		// the program ID 
		unsigned int ID;
		//  onstructor reads and builds the shader
		Shader(const char* vertexPath, const char* fragmentPath);
		// use/activate the shader
		void use();
		// utility uniform functions
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
};
#endif