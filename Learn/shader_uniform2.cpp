//���� �߻� �߿� ����.
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
    // glfw: �ʱ�ȭ �� ����
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw â ����
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "GLFW â ���� ����" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: ��� OpenGL �Լ� ������ �ε�
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "GLAD �ʱ�ȭ ����" << endl;
        return -1;
    }

    // ���̴� ���α׷� ���� �� ������
    Shader ourshader("shader.frag", "shader.vert");

    // ���ؽ� ������ �� ���� ���� �� ���ؽ� �Ӽ� ����
    float vertices[] = {
         0.5f, -0.5f, 0.0f,  // ������ �ϴ�
        -0.5f, -0.5f, 0.0f,  // ���� �ϴ�
         0.0f,  0.5f, 0.0f   // �� 
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // ���� Vertex Array Object�� ���ε��ϰ�, ���ؽ� ���۸� ���ε��ϰ� ������ ����, ���ؽ� �Ӽ��� ����
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);

    // ���� ����
    while (!glfwWindowShouldClose(window))
    {
        // �Է� ó��
        processInput(window);

        // ������
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // �� glUniform ȣ�� ���� shader�� Ȱ��ȭ
        ourshader.use();

        // shader uniform ������Ʈ
        double timeValue = glfwGetTime(); // ���� ���� �ð��� �� ������..
        float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5); // 0.0~1.0���� �������� ���� ��ȭ
        int vertexColorLocation = glGetUniformLocation(ourshader.ID, "ourColor"); //uniform�� ��ġ�� ��ȸ 
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // �ﰢ�� ������
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: ���� ��ü �� I/O �̺�Ʈ (Ű ����/����, ���콺 �̵� ��)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //�� �̻� �ʿ����� ���� ��� �ڿ��� ����
    // glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(ourshader.ID);

    // glfw: ��� ������ �Ҵ�� GLFW �ڿ��� �����ϰ� ����
    glfwTerminate();
    return 0;
}

// ��� �Է��� ó��: �� �����ӿ��� ����/������ Ű�� �����ϰ� �׿� ���� ����
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: â ũ�Ⱑ ����� ������ (OS �Ǵ� ����� ������) ȣ��Ǵ� �� �ݹ� �Լ�
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}