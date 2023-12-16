#include <glad/glad.h> //glfw보다 먼저 include되어야 한다. 
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader.h>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height); //framebuffer 크기 지정 콜백 함수 
void processInput(GLFWwindow* window); //

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: 초기화 및 설정 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window 생성
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "shader_exe1", NULL, NULL);
    if (window == NULL) //window 생성 실패 시 
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: OpenGL 함수 포인터 불러오기 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //불러오는데 실패했다면 
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // shader program 빌드 및 컴파일
    Shader ourshader("shader.vert","shader.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // EBO
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };

    unsigned int VBO, VAO; // 정점 버퍼 객체, 정점 배열 객체 선언 
    glGenVertexArrays(1, &VAO); //정점 배열 객체 생성
    glGenBuffers(1, &VBO); //정점 버퍼 객체 생성
    // 먼저 정점 배열 객체 바인드, 그리고 정점 버퍼 객체(들) 바인드, 마지막으로 정점 속성 환경설정
    glBindVertexArray(VAO); // 정점 배열 객체 바인드 

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // vertices 배열을 복사
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //버퍼데이터 

    //OpenGL에게 vertex attributes를 어떻게 해석해야 할 지 알려줌 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //vertex attribute를 활성화 

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        ourshader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3); // (primitive유형지정, vertex array index지정 전달, vertex의 수를 지정)
        // glBindVertexArray(0); 

        // glfw: swap buffers and poll I/O events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(ourshader.ID);

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