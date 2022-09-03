#include <glad/glad.h>
#include <GLFW/glfw3.h>

// OPENGL MATHEMATICS 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// CPP LIBRARIES

#include <iostream>
#include <ctime>
#include <cmath>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void check_shader_compile(unsigned int shader);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// Vertex Shader
const char *vertexShaderSource = 
	"#version 330 core\n"
	"layout (location=0) in vec3 aPos;\n"
//	"layout (location=1) in vec3 aColor;\n"
//	"out vec3 ourcolor;\n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 projection;\n"
	"void main()\n"
	"{\n"
		"gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
//		"ourcolor = aColor;\n"
	"}\0"
;

// Fragment Shader
const char *fragmentShaderSource = 
	"#version 330 core\n"
	"out vec4 FragColor;\n"
//	"in vec3 ourcolor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 1.0f ,1.0f ,1.0f);\n"					// Color is represented using RGBA red green blue opacity zero to one mark as float
	"}\n\0"
;



int main()
{

	// Initialization Code for GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 					// OpenGL Version (Installed Version Four.Six)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// Core-Profile mean w/out backward-compatible features we don't need

	std::cerr << "GLFW INITIALIZATION COMPLETE" << std::endl;


	// Create Window Object
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);		// Parameters (Width, Height, Name, Ignore, Ignore)
	if (window == NULL)																// Debug Code for if window was not successfully created
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	std::cerr << "GLFW WINDOW ESTABLISHED" << std::endl;

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
	glfwSetScrollCallback(window,scroll_callback);

	GLint windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	std::cerr << "GLAD INITIALIZATION COMPLETE" << std::endl;

	// Compile Shaders
	// Vertex Shader
	unsigned int vertexShader;														// Stores a non-zero value by which it can be referenced
	vertexShader = glCreateShader(GL_VERTEX_SHADER);								/* creates an empty shader object and returns a non-zero value 
																					   by which it can be referenced */

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);						// sets the source code in shader	
	glCompileShader(vertexShader);													// compiles shader duh
	check_shader_compile(vertexShader);
	std::cerr << "VERTEX SHADER CREATED COMPILED AND CHECKED" << std::endl;
	
	// Fragment Shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	check_shader_compile(fragmentShader);
	std::cerr << "FRAGMENT SHADER CREATED COMPILED AND CHECKED" << std::endl;

	/* Shader Program
	 *
	 * A shader program object is the final linked version of multiple shaders
	 * combined. To use the recently compiled shaders we have to link them to a
	 * shader program object and then activate this shader program when
	 * rendering objects.  The activated shader program's shaders will be used
	 * when we issue render calls.
	 *
	 * When linking the shaders into a program it links the outputs of each
	 * shader to the inputs of the next shader.  This is also where you'll get
	 * linking errors if your outputs and inputs do not match.*/

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check for linking errors
	int success;
	glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
	if(!success){
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << infoLog << std::endl;
	}
	else if(success){
		std::cerr << "SHADER PROGRAM SUCCESFULLY LINKED" << std::endl;}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Set the Viewport Up
	glViewport(0,0,800,600);														// the first two set the lower left coordinate of the window, width, height
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);				// Callback function for dynamically adjusted window
	
	// Define the Vertices
	
	float vertices_shape[] = {
		// x	y	 z
		-0.9f, -0.9f, 2.0f,
		0.9f, -0.9f, 2.0f,
		// y axis
		-0.9f, -0.9f, 2.0f,
		-0.9f, 0.9f, 2.0f,
		// z axis
		-0.9f, -0.9f, 0.0f,
		-0.9f, -0.9f, 2.0f,
	}; 

	float vertices_[] = {
		0.4f, 0.5f, 0.1f,
		0.8f, 0.2f, 0.5f,
		0.6f, 0.4f, 0.3f,
	};


	float chartmarginwidth = (float)windowWidth / 10.0f;
	float chartmarginheight = (float)windowHeight / 10.0f;

	/* float vertices[] = {
		// x	y	 z
		(float)windowWidth / 10.0f, (float)windowHeight - (float)windowHeight / 10.0f, 0.1f,
		(float)windowWidth - (float)windowWidth / 10.0f, (float)windowHeight - (float)windowHeight / 10.0f , 0.1f,
		// y axis
		chartmarginwidth , chartmarginheight, 0.1f,
		chartmarginwidth ,(float)windowHeight - chartmarginheight, 0.1f,
		// z axis
		chartmarginwidth, chartmarginheight, 0.0f,
		chartmarginwidth, chartmarginheight, 100.0f
	};*/


	// EBO makes it possible for you to use one vertex twice in one send to the gpu
	unsigned int indices[6] = {
		0, 1, 3,
		1, 2, 3
	};

	// set the vertex attributes object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	// Set up the Vertex Buffer Object (VBO)
	unsigned int VBO;																// defines the buffer
	glGenBuffers(1, &VBO);															// Generates the Buffer and stores it in VBO
																					// glGenBuffers(number of buffers you wish to gen, array of pointers to places that store those buffers)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);												// Binds the VBO to GL_ARRAY_BUFFER for it to be a vertex buffer

	/*	glBufferData copies the user data into the given buffer
	 *	the fourth parameter specifies how we want the graphics card to handle
	 *	the data:
	 *		GL_STREAM_DRAW: the data is set once and used by the GPU at most a
	 *		few times
	 *		GL_STATIC_DRAW: the data is set only once and used many times
	 *		GL_DYNAMIC_DRAW: Set many times and used many times
	 */

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_shape), vertices_shape, GL_STATIC_DRAW);

	// unsigned int VBO_2;
	// glGenBuffers(1, &VBO_2);

	// EBO
/*	
	unsigned int EBO;
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
*/
	// Write the Attributes
	
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	// Color Thing
	// glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3* sizeof(float)));  // Specifying the location one mentioned in the shader
	// glEnableVertexAttribArray(1);

	// Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Initiate Render Loop
	
	unsigned int counter = 0;
	time_t start_time, end_time;
	time(&start_time);

	double lastTime = glfwGetTime();
	
	glfwSetCursorPos(window, (float)windowWidth/2,(float)windowHeight/2);

	while(!glfwWindowShouldClose(window))											// While the window isn't closed
	{
		counter++;
		processInput(window);

		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		// 3d Transformations
		glm::vec3 position = glm::vec3(0,0,5);
		float horizontalAngle = 3.14f;
		float verticalAngle = 0.0f;
		float initialFoV = 45.0f;
		float speed = 3.0f;
		float mouseSpeed = 0.05f;

		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		lastTime = glfwGetTime();

		// read mouse position
		double xpos, ypos;
		// GLint windowWidth, windowHeight;
		glfwGetCursorPos(window, &xpos, &ypos);
		//glfwGetWindowSize(window, &windowWidth, &windowHeight);
	//	glfwSetCursorPos(window, (float)windowWidth/2,(float)windowHeight/2);
		horizontalAngle += mouseSpeed * deltaTime * float((float)windowWidth/2 - xpos);
		verticalAngle += mouseSpeed * deltaTime * float((float)windowHeight/2 - ypos);
		glm::vec3 direction = glm::vec3(cos(verticalAngle) * sin(horizontalAngle),sin(verticalAngle),cos(verticalAngle) * cos(horizontalAngle));
		glm::vec3 right_vector = glm::vec3(sin(horizontalAngle - 3.14f/2.0f),0,cos(horizontalAngle - 3.14f/2.0f));
		glm::vec3 up = glm::cross(right_vector,direction);

		// Test Code

		// Keyboard Stuff

		// Move forward
		if (glfwGetKey( window, GLFW_KEY_UP  ) == GLFW_PRESS){
		     position += direction * deltaTime * speed;
		     }
		// Move backward
		if (glfwGetKey( window , GLFW_KEY_DOWN  ) == GLFW_PRESS){
		     position -= direction * deltaTime * speed;
		     }
		// Strafe right
		if (glfwGetKey( window, GLFW_KEY_RIGHT  ) == GLFW_PRESS){
		     position += right_vector * deltaTime * speed;
		     }
		// Strafe left
		if (glfwGetKey( window, GLFW_KEY_LEFT  ) == GLFW_PRESS){
		     position -= right_vector * deltaTime * speed;
		     }
		float xoffset, yoffset;
		scroll_callback(window, xoffset, yoffset);
		std::cerr << yoffset << "/t" << xoffset << std::endl;
		float FoV = initialFoV - 5 * yoffset;
		
		// Compute the Matrices
		glm::mat4 ViewMatrix = glm::lookAt(position, position+direction, up);
		// glm::mat4 ViewMatrix = glm::mat4(1.0f);
		glm::mat4 ModelMatrix = glm::mat4(1.0f);
		// glm::mat4 ProjectionMatrix = glm::ortho(0.0f,(float)windowWidth,(float)windowHeight,0.0f, 0.1f,100.0f); // ORTHO DOESN'T WORK
		glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(FoV), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

		int modelID = glGetUniformLocation(shaderProgram,"model");
		int viewID = glGetUniformLocation(shaderProgram,"view");
		int projectionID = glGetUniformLocation(shaderProgram,"projection");

		glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
		glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
		glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

		glBindVertexArray(VAO);
	//	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
		// glDrawArrays(GL_LINES,0,6);
		glDrawArrays(GL_LINES,0,6);
		glFlush();
		
	/*	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_shape), vertices_shape, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glDrawArrays(GL_TRIANGLES,0,3); */
		glfwSwapBuffers(window);													// swap the window into the front buffer
		glfwPollEvents();															// and keep an eye on inputsand events
	}

	time(&end_time);
	
	std::cerr << end_time - start_time << "Seconds " << (float) counter / (end_time - start_time) << "FPS" << std::endl;

	std::cerr << counter << " FRAMES RENDERED.  RENDER LOOP COMPLETED.  TERMINATING APPLICATION...";


	// If render loop is over, Terminate
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	// glDeleteBuffers(1,&EBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;
	
}

void processInput(GLFWwindow *window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window,true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0,0,width,height);
}

void check_shader_compile(unsigned int shader){
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset){};
