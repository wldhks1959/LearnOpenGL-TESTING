//오류 발생 중에 있음.
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <shader.h>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw 창 생성
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "GLFW 창 생성 실패" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: 모든 OpenGL 함수 포인터 로드
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "GLAD 초기화 실패" << endl;
        return -1;
    }

    // 셰이더 프로그램 빌드 및 컴파일
    Shader ourshader("shader.frag", "shader.vert");

    // 버텍스 데이터 및 버퍼 구성 및 버텍스 속성 구성
    float vertices[] = {
         0.5f, -0.5f, 0.0f,  // 오른쪽 하단
        -0.5f, -0.5f, 0.0f,  // 왼쪽 하단
         0.0f,  0.5f, 0.0f   // 위 
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // 먼저 Vertex Array Object를 바인딩하고, 버텍스 버퍼를 바인딩하고 설정한 다음, 버텍스 속성을 구성
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);

    // 렌더 루프
    while (!glfwWindowShouldClose(window))
    {
        // 입력 처리
        processInput(window);

        // 렌더링
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 꼭 glUniform 호출 전에 shader를 활성화
        ourshader.use();

        // shader uniform 업데이트
        double timeValue = glfwGetTime(); // 현재 실행 시간을 초 단위로..
        float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5); // 0.0~1.0까지 범위에서 색상 변화
        int vertexColorLocation = glGetUniformLocation(ourshader.ID, "ourColor"); //uniform의 위치를 조회 
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // 삼각형 렌더링
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: 버퍼 교체 및 I/O 이벤트 (키 누름/떼기, 마우스 이동 등)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //더 이상 필요하지 않은 모든 자원을 해제
    // glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(ourshader.ID);

    // glfw: 모든 이전에 할당된 GLFW 자원을 정리하고 종료
    glfwTerminate();
    return 0;
}

// 모든 입력을 처리: 이 프레임에서 눌린/해제된 키를 쿼리하고 그에 따라 반응
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: 창 크기가 변경될 때마다 (OS 또는 사용자 조절로) 호출되는 이 콜백 함수
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}