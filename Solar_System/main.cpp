// GLFW - glad - stb_image
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GL includes
#include "shader.h"
#include "camera.h"
#include "model.h"

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
GLFWwindow* window;
// camera
 //Camera camera(glm::vec3(0.0f, 1.0f, 23.0f));
Camera camera(glm::vec3(0.0f, 0.0f, 100.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;
bool keys[1024];

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void glfwinitialize()
{
	glfwInit();
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Solar system", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);


}
int main()
{
	glfwinitialize();
    Shader shader("vertex.vs", "fragment.fs");

 	Model sun_model("objects/Sun/sun2.obj");
	Model mercury_model("objects/mercury/mercury.obj");
	Model mars_model("objects/mars/Mars_normal-strong.obj");
	Model earth_model("objects/earth/earth.obj");
	Model venus_model("objects/Venus/venus.obj");
	Model saturn_model("objects/Saturn/saturn3.obj");
	Model neptun_model("objects/Neptune/neptune.obj");
	Model uranus_model("objects/Uranus/uranus.obj");
	Model jupiter_model("objects/jupiter/jupiter1.obj");
	Model moon_model("objects/moon/moon1.obj");


    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = 2*(currentFrame - lastFrame);
        lastFrame = currentFrame;

        processInput(window);

 		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

		// draw planet   
		glm::mat4 model1(1), model2(1), model3(1), model4(1), model5(1), model6(1), model7(1), model8(1), model9(1), model10(1);
		
		model1 = glm::translate(model1, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model1 = glm::rotate(model1, glm::radians((GLfloat)glfwGetTime() * 8.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model1 = glm::scale(model1, glm::vec3(0.1f, 0.1f, 0.1f));	// It's a bit too big for our scene, so scale it down
		shader.setMat4("model", model1);
		sun_model.Draw(shader);
		
		model2 = glm::translate(model2, glm::vec3(18.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model2 = glm::rotate(model2, glm::radians((GLfloat)glfwGetTime() * 20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model2 = glm::scale(model2, glm::vec3(0.01f, 0.01f, 0.01f));	// It's a bit too big for our scene, so scale it down
		shader.setMat4("model", model2);
		mercury_model.Draw(shader);

		model3 = glm::translate(model3, glm::vec3(-20.0f, -1.75f, -6.0f)); // Translate it down a bit so it's at the center of the scene
		model3 = glm::rotate(model3, glm::radians((GLfloat)glfwGetTime() * 18.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model3 = glm::scale(model3, glm::vec3(0.01f, 0.01f, 0.01f));	// It's a bit too big for our scene, so scale it down
		shader.setMat4("model", model3);
		venus_model.Draw(shader);
		
		model4 = glm::translate(model4, glm::vec3(-27.0f, -1.0f, 10.0f)); // Translate it down a bit so it's at the center of the scene
		model4 = glm::rotate(model4, glm::radians((GLfloat)glfwGetTime() * 20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model4 = glm::scale(model4, glm::vec3(0.003f, 0.003f, 0.003f));	// It's a bit too big for our scene, so scale it down
		shader.setMat4("model", model4);
		earth_model.Draw(shader);
		/*
		model10 = glm::translate(model10, glm::vec3(-27.0f, 0.8f, 11.0f)); // Translate it down a bit so it's at the center of the scene
		model10 = glm::scale(model10, glm::vec3(0.005, 0.005f, 0.005f));	// It's a bit too big for our scene, so scale it down
		shader.setMat4("model", model10);
		moon_model.Draw(shader);
		*/
		model5 = glm::translate(model5, glm::vec3(30.0f, -1.75f, -9.0f)); // Translate it down a bit so it's at the center of the scene
		model5 = glm::rotate(model5, glm::radians((GLfloat)glfwGetTime() * 25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model5 = glm::scale(model5, glm::vec3(0.1f, 0.1f, 0.1f));	// It's a bit too big for our scene, so scale it down
		shader.setMat4("model", model5);
		mars_model.Draw(shader);

		model6 = glm::translate(model6, glm::vec3(-43.5f, -1.75f, 25.0f)); // Translate it down a bit so it's at the center of the scene
		model6 = glm::rotate(model6, glm::radians((GLfloat)glfwGetTime() * 25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model6 = glm::scale(model6, glm::vec3(0.03f, 0.03f, 0.03f));	// It's a bit too big for our scene, so scale it down
		shader.setMat4("model", model6);
		saturn_model.Draw(shader);

		model7 = glm::translate(model7, glm::vec3(-47.0f, -1.75f, -40.0f)); // Translate it down a bit so it's at the center of the scene
		model7 = glm::rotate(model7, glm::radians((GLfloat)glfwGetTime() * 20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model7 = glm::scale(model7, glm::vec3(0.03f, 0.03f, 0.03f));	// It's a bit too big for our scene, so scale it down
		shader.setMat4("model", model7);
		neptun_model.Draw(shader);

		model8 = glm::translate(model8, glm::vec3(45.0f, -1.75f, -40.0f)); // Translate it down a bit so it's at the center of the scene
		model8 = glm::rotate(model8, glm::radians((GLfloat)glfwGetTime() * 15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model8 = glm::scale(model8, glm::vec3(0.03f, 0.03f, 0.03f));	// It's a bit too big for our scene, so scale it down
		shader.setMat4("model", model8);
		uranus_model.Draw(shader);

		model9 = glm::translate(model9, glm::vec3(36.0f, -1.75f, 37.0f)); // Translate it down a bit so it's at the center of the scene
		model9 = glm::rotate(model9, glm::radians((GLfloat)glfwGetTime() * 17.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model9 = glm::scale(model9, glm::vec3(0.05f, 0.05f, 0.05f));	// It's a bit too big for our scene, so scale it down
		shader.setMat4("model", model9);
		jupiter_model.Draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
