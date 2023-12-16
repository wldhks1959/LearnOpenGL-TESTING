#include <glad/glad.h> //glfw���� ���� include�Ǿ�� �Ѵ�. 
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height); //framebuffer ũ�� ���� �ݹ� �Լ� 
void processInput(GLFWwindow* window); //

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

//Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main()
{
    // glfw: �ʱ�ȭ �� ���� 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window ����
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL ver 3.3 Triangle", NULL, NULL);
    if (window == NULL) //window ���� ���� �� 
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); 
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: OpenGL �Լ� ������ �ҷ����� 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //�ҷ����µ� �����ߴٸ� 
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // shader program ���� �� ������
    // vertexShader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //shader��ü ����, �ҽ� �ڵ� ���ڿ� �� ����, ���� �ҽ� �ڵ� 
    glCompileShader(vertexShader);
    // ������ ���� Ȯ�� �Լ� 
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); //������ ���� Ȯ�� 
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // fragment shader
    //�ȼ� ���� ��� ����ϴµ� ���, �����ϰ� ���� ���� ��Ȳ���� ����� ���� ���
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // link shaders
    unsigned int shaderProgram = glCreateProgram(); //���α׷��� ���� ��, ���� ������ ���α׷� ��üID ���� ��ȯ 
    //glLinkProgram�� ����Ͽ� vertex/fragment shader ���α׷� ��ü�� ���� 
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); //��ũ 
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }
    glDeleteShader(vertexShader); //shader ��ü���� ���α׷��� ������ �� �ʿ�����Ƿ� ����
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // EBO
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };

    unsigned int VBO, VAO; // ���� ���� ��ü, ���� �迭 ��ü ���� 
    glGenVertexArrays(1, &VAO); //���� �迭 ��ü ����
    glGenBuffers(1, &VBO); //���� ���� ��ü ����
    // ���� ���� �迭 ��ü ���ε�, �׸��� ���� ���� ��ü(��) ���ε�, ���������� ���� �Ӽ� ȯ�漳��
    glBindVertexArray(VAO); // ���� �迭 ��ü ���ε� 

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // vertices �迭�� ����
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //���۵����� 

    //OpenGL���� vertex attributes�� ��� �ؼ��ؾ� �� �� �˷��� 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //vertex attribute�� Ȱ��ȭ 

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram); 
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 3); // (primitive��������, vertex array index���� ����, vertex�� ���� ����)
        // glBindVertexArray(0); 

        // glfw: swap buffers and poll I/O events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}