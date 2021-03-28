#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>

#include <iostream>
#include <string>

#define PI 3.14159265

// Box coordinate with 36 vertices.
// Every 3 coordinates will form 1 triangle.
// The last 2 columns represent texture coordinate for mapping.
float box[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void process_input(GLFWwindow *window);
unsigned int loadTexture(char const * path);

// settings
const unsigned int SCR_WIDTH = 1100;
const unsigned int SCR_HEIGHT = 1100;

// original positions to reset the game to beginning state
glm::vec3 reset_camera_pos   = glm::vec3(0.0f, 0.9f,  3.0f);
glm::vec3 reset_camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 reset_camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);
glm::vec3 reset_slender_pos = glm::vec3(0.0f, 0.002f, -25.0f);
glm::vec3 reset_torch_pos = glm::vec3(0.0f, 0.002f, -13.0f); 
glm::vec3 reset_light_pos = glm::vec3(0.0f, 0.9f, 3.0f);
glm::vec3 reset_dagger_pos = glm::vec3(-21.8f, 0.002f, -23.7f);
glm::vec3 reset_gun_pos = glm::vec3(11.0f, 0.0f, 21.4f); 
glm::vec3 reset_winCube_pos = glm::vec3(28.0f, 0.0f, -28.0f);

// camera positions
glm::vec3 camera_pos   = glm::vec3(0.0f, 0.9f,  3.0f);
glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);

// lighting
glm::vec3 light_pos(0.0f, 0.9f, 3.0f);

// positions of objects
glm::vec3 slender_pos = glm::vec3(0.0f, 0.002f, -25.0f); // position of slenderman
glm::vec3 torch_pos = glm::vec3(0.0f, 0.002f, -13.0f); // position of torch
glm::vec3 table_pos = glm::vec3(-2.0f, 0.0f, 10.0f); // position of table
glm::vec3 dagger_pos = glm::vec3(-21.8f, 0.002f, -23.7f); // position of dagger
glm::vec3 gun_pos = glm::vec3(11.0f, 0.0f, 21.4f); // position of gun
glm::vec3 winCube_pos = glm::vec3(28.0f, 0.0f, -28.0f); // position of cube to win game

// yaw is left and right, pitch is up and down
bool firstMouse = true;
float yaw = -90.0f; // yaw initialised to -90.0 degrees since a yaw of 0.0 results in direction vector pointing to the right, so we initially rotate a bit to the left
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

// timing
float delta_time = 0.0f;	// time between current frame and last frame
float last_frame = 0.0f;

// booleans and integers
bool BUTTON_PRESSED = false;
int BUTTON_DELAY = 0;
bool BUTTON_CLOSE_ENOUGH = false;

bool SHOW_COORDINATE = false;
int SHOW_DELAY = 0;

bool ALIVE = true;
bool VICTORY = false;
bool SPAWN_VICTORY_AREA = false;

bool TORCH_PICKEDUP = false;
bool DAGGER_PICKEDUP = false;
bool GUN_PICKEDUP = false;

bool AMBIENT_LIGHT = false;
int AMBIENT_DELAY = 0;
bool ORTHOGRAPHIC_MODE = false;
int ORTHOGRAPHIC_DELAY = 0;

int ITEM_COUNT = 0;
int ATTENUATION_NUM = 3;

// Countdown until the button trigger can be pressed again.
// This prevents accidental burst repeat clicking of the key.
void update_delay()
{
	if(BUTTON_DELAY > 0) BUTTON_DELAY -= 1;
	if(SHOW_DELAY > 0) SHOW_DELAY -= 1;
	if(AMBIENT_DELAY > 0) AMBIENT_DELAY -= 1;
	if(ORTHOGRAPHIC_DELAY > 0) ORTHOGRAPHIC_DELAY -= 1;
}

// TOGGLES
// turns on the light from torch
void toggle_button_distance(glm::vec3 button_pos)
{
	if(glm::length(camera_pos - button_pos) <= 1.6f)
		BUTTON_CLOSE_ENOUGH = true;
	else
		BUTTON_CLOSE_ENOUGH = false;
}

// if slenderman gets too close to the camera, player dies
void toggle_alive_distance(glm::vec3 camera_pos)
{
	if (glm::length(camera_pos - slender_pos) <= 1.6f)
	{
		ALIVE = false;
	}
}

// picks up torch within certain distance
void toggle_torch_distance(glm::vec3 torch_pos)
{
	if (glm::length(camera_pos - torch_pos) <= 2.0f)
	{
		TORCH_PICKEDUP = true;
	}
}

// picks up dagger within certain distance
void toggle_dagger_distance(glm::vec3 dagger_pos)
{
	if (glm::length(camera_pos - dagger_pos) <= 1.6f)
	{
		DAGGER_PICKEDUP = true;
		ITEM_COUNT++;
	}
}

// picks up gun within certain distance
void toggle_gun_distance(glm::vec3 gun_pos)
{
	if (glm::length(camera_pos - gun_pos) <= 1.6f)
	{
		GUN_PICKEDUP = true;
		ITEM_COUNT++;
	}
}

// win game within certain distance
void toggle_cube_distance(glm::vec3 winCube_pos)
{
	if (glm::length(camera_pos - winCube_pos) <= 2.0f)
	{
		VICTORY = true;
	}
}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement for OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Escape from Slenderman", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	// tell GLFW to capture our mouse and lock it in the centre of the window
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader lighting_shader("./sample2.vs", "./sample2.fs");
	Shader lamp_shader("./lamp.vs", "./lamp.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	unsigned int VBO_box, VAO_box;

	glGenVertexArrays(1, &VAO_box);
	glGenBuffers(1, &VBO_box);

	glBindVertexArray(VAO_box);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_box);
	glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_STATIC_DRAW);

	//vertex coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//normal vectors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int VAO_light;
	glGenVertexArrays(1, &VAO_light);
	glBindVertexArray(VAO_light);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_box);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// load and create a texture 
	// -------------------------
	unsigned int tex_wood_diffuse, tex_grass_diffuse, tex_marble_diffuse;
	unsigned int tex_wood_specular, tex_grass_specular, tex_marble_specular;

	unsigned int tex_sky, tex_sky_specular, tex_wood, tex_greenleaves, tex_white, tex_black, tex_metal;
	unsigned int tex_red, tex_brickwall, tex_container, tex_win, tex_lose;

	tex_wood_diffuse = loadTexture(FileSystem::getPath("resources/textures/wood2.jpg").c_str());
	tex_wood_specular = loadTexture(FileSystem::getPath("resources/textures/wood2_specular.jpg").c_str());
	tex_grass_diffuse = loadTexture(FileSystem::getPath("resources/textures/grass.jpg").c_str());
	tex_grass_specular = loadTexture(FileSystem::getPath("resources/textures/grass_specular.jpg").c_str());
	tex_marble_diffuse = loadTexture(FileSystem::getPath("resources/textures/marble.jpg").c_str());
	tex_marble_specular = loadTexture(FileSystem::getPath("resources/textures/marble_specular.jpg").c_str());
	tex_sky = loadTexture(FileSystem::getPath("resources/textures/night_sky.jpg").c_str());
	tex_sky_specular = loadTexture(FileSystem::getPath("resources/textures/night_sky_specular.jpg").c_str());
	tex_wood = loadTexture(FileSystem::getPath("resources/textures/wood2.jpg").c_str());
	tex_greenleaves = loadTexture(FileSystem::getPath("resources/textures/greenleaves.jpg").c_str());
	tex_white = loadTexture(FileSystem::getPath("resources/textures/white.jpg").c_str());
	tex_black = loadTexture(FileSystem::getPath("resources/textures/black.jpg").c_str());
	tex_metal = loadTexture(FileSystem::getPath("resources/textures/metal.png").c_str());
	tex_red = loadTexture(FileSystem::getPath("resources/textures/red.jpg").c_str());
	tex_brickwall = loadTexture(FileSystem::getPath("resources/textures/brickwall.jpg").c_str());
	tex_container = loadTexture(FileSystem::getPath("resources/textures/container.jpg").c_str());
	tex_win = loadTexture(FileSystem::getPath("resources/textures/win.png").c_str());
	tex_lose = loadTexture(FileSystem::getPath("resources/textures/lose.png").c_str());
	
	//shader configuration -------------------------------------------------------------------------------------------
	lighting_shader.use();
	lighting_shader.setInt("material.diffuse", 0);
	lighting_shader.setInt("material.specular", 1);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		delta_time = currentFrame - last_frame;
		last_frame = currentFrame;

		//update delay countdown
		update_delay();

		// input
		// -----
		process_input(window);

		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

		// activate shader
		lighting_shader.use();
        lighting_shader.setVec3("light.position", camera_pos);
        lighting_shader.setVec3("light.direction", camera_front);
        lighting_shader.setVec3("viewPos", camera_pos);

		// change attenuation values
		// linear and quadratic values obtained from LearnOpenGL
		// when the user presses K or L, these values change. The default ATTENUATION_NUM is 3
		if (ATTENUATION_NUM == 0)
		{
			lighting_shader.setFloat("light.linear", 0.7f);
			lighting_shader.setFloat("light.quadratic", 1.8f);
		}
		else if (ATTENUATION_NUM == 1)
		{
			lighting_shader.setFloat("light.linear", 0.35f);
			lighting_shader.setFloat("light.quadratic", 0.44f);
		}
		else if (ATTENUATION_NUM == 2)
		{
			lighting_shader.setFloat("light.linear", 0.22f);
			lighting_shader.setFloat("light.quadratic", 0.20f);
		}
		else if (ATTENUATION_NUM == 3)
		{
			lighting_shader.setFloat("light.linear", 0.14f);
			lighting_shader.setFloat("light.quadratic", 0.07f);
		}
		else if (ATTENUATION_NUM == 4)
		{
			lighting_shader.setFloat("light.linear", 0.09f);
			lighting_shader.setFloat("light.quadratic", 0.032f);
		}
		else if (ATTENUATION_NUM == 5)
		{
			lighting_shader.setFloat("light.linear", 0.07f);
			lighting_shader.setFloat("light.quadratic", 0.017f);
		}
		else if (ATTENUATION_NUM == 6)
		{
			lighting_shader.setFloat("light.linear", 0.045f);
			lighting_shader.setFloat("light.quadratic", 0.0075f);
		}
		else // default values
		{
			lighting_shader.setFloat("light.constant", 1.0f);
			lighting_shader.setFloat("light.linear", 0.09f);
			lighting_shader.setFloat("light.quadratic", 0.032f);
		}

		// light properties
		// ambient lighting
		if (AMBIENT_LIGHT)
		{
		
			lighting_shader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
		}
		else
		{
			lighting_shader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
		}

		// if torch is picked up, the lighting will be a spotlight effect 
		if(TORCH_PICKEDUP == true) // button is turned on when torch picked up
		{
	        lighting_shader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        	lighting_shader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
			lighting_shader.setVec3("light.diffuse", 3.5f, 3.5f, 3.5f);
			lighting_shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		}
		else // no spotlight effect
		{
			lighting_shader.setFloat("light.cutOff", glm::cos(glm::radians(0.0f)));
        	lighting_shader.setFloat("light.outerCutOff", glm::cos(glm::radians(0.0f)));
			lighting_shader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
			lighting_shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		}

		// pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
		// -----------------------------------------------------------------------------------------------------------
		glm::mat4 projection;
		
		// perspective and orthographic mode
		if (ORTHOGRAPHIC_MODE) // ortho
		{
			projection = glm::ortho(1.0f,(float)SCR_WIDTH/100.0f, 1.0f,(float)SCR_HEIGHT/100.0f, 0.1f,1000.0f);
			lighting_shader.setMat4("projection", projection);
		}
		else // perspective
		{
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 300.0f);
			lighting_shader.setMat4("projection", projection);
		}

		// material properties
        	lighting_shader.setFloat("material.shininess", 65.0f);
		// for now just set the same for every object. But, you can make it dynamic for various objects.


		// camera/view transformation
		glm::mat4 view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
		lighting_shader.setMat4("view", view);

		//declare transformation matrix
		glm::mat4 model = glm::mat4();
		/*
		//example (remember, it is in column matrix position, so the order is reversed.)
		model = glm::translate(model, glm::vec3(1.0f, 2.0f, 3.0f)); 			// translate by (1.0, 2.0, 3.0)
		model = glm::scale(model, glm::vec3(2.0f, 5.0f, 3.0f)); 			// scale by (2.0, 5.0, 3.0) on X, Y, and Z respectively.
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));	// rotate 45 degree about Y-axis (0,1,0)
		*/

		//Draw objects
		//------------------------------------------------------------------------------------------
		
		// sky
		glBindVertexArray(VAO_box);//This does not have to binded every time after first call, but just for consistency.

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_sky);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_sky_specular);

		model = glm::mat4();
		model = glm::scale(model, glm::vec3(200.0f, 200.0f, 200.0f));

		lighting_shader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		// floor
		glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_grass_diffuse);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_grass_specular);

		model = glm::mat4();
		model = glm::scale(model, glm::vec3(60.0f, 0.001f, 60.0f)); // 60x60 map

		lighting_shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// boundaries
		glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_brickwall);

		glm::vec3 boundary_scales[] = {
			glm::vec3(60.0f, 5.0f, 0.1f), // north
			glm::vec3(0.1f, 5.0f, 60.0f), // east
			glm::vec3(60.0f, 5.0f, 0.1f), // south
			glm::vec3(0.1f, 5.0f, 60.0f) // west
		};
		glm::vec3 boundary_positions[] = {
			glm::vec3(0.0f, 2.5f, -30.0f), // north
			glm::vec3(30.0f, 2.5f, 0.0f), // east
			glm::vec3(0.0f, 2.5f, 30.0f), // south
			glm::vec3(-30.0f, 2.5f, 0.0f) // west
		};

		// for loop for the boundaries
		for(int tab = 0; tab < 4; tab++)
		{	
			model = glm::mat4();
			model = glm::translate(model, boundary_positions[tab]);
			model = glm::scale(model, boundary_scales[tab]);

			lighting_shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// trees
		glm::vec3 tree_scales[] = {
			glm::vec3(0.5f, 2.5f, 0.5f), // trunk
			glm::vec3(1.7f, 1.7f, 1.7f) // leaves
		};
		glm::vec3 tree_positions[] = {
			glm::vec3(-3.0f, 0.0f, 0.0f), // trunk
			glm::vec3(-3.0f, 2.5f, 0.0f), // leaves
		};

		// array to store positions for multiple trees
		glm::vec3 clone_tree_positions[] = {
			glm::vec3(4.0f, 0.0f, 13.0f),
			glm::vec3(9.0f, 0.0f, 6.0f),
			glm::vec3(13.0f, 0.0f, 4.0f),
			glm::vec3(15.0f, 0.0f, 22.0f),
			glm::vec3(19.0f, 0.0f, 2.0f),
			glm::vec3(21.0f, 0.0f, 21.0f),
			glm::vec3(27.0f, 0.0f, 27.0f),
			glm::vec3(-8.0f, 0.0f, -8.0f),
			glm::vec3(-11.0f, 0.0f, -13.0f),
			glm::vec3(-13.0f, 0.0f, -18.0f), // 10
			glm::vec3(-19.0f, 0.0f, -23.0f),
			glm::vec3(-24.0f, 0.0f, -11.0f),
			glm::vec3(9.0f, 0.0f, -11.0f),
			glm::vec3(11.0f, 0.0f, -18.0f),
			glm::vec3(17.0f, 0.0f, -25.0f),
			glm::vec3(-5.0f, 0.0f, -11.0f),
			glm::vec3(24.0f, 0.0f, -18.0f),
			glm::vec3(18.0f, 0.0f, -10.0f),
			glm::vec3(-8.0f, 0.0f, 10.0f),
			glm::vec3(-16.0f, 0.0f, 18.0f), // 20
			glm::vec3(-16.0f, 0.0f, 23.0f),
			glm::vec3(3.0f, 0.0f, -28.0f), 
			glm::vec3(12.0f, 0.0f, -4.0f),
			glm::vec3(21.0f, 0.0f, -1.0f),
			glm::vec3(14.0f, 0.0f, -7.0f),
			glm::vec3(-3.0f, 0.0f, -4.0f),
			glm::vec3(-5.0f, 0.0f, -11.0f),
			glm::vec3(2.0f, 0.0f, 16.0f),
			glm::vec3(4.0f, 0.0f, 15.0f),
			glm::vec3(14.0f, 0.0f, 21.0f), // 30
			glm::vec3(-14.0f, 0.0f, 4.0f),
			glm::vec3(11.0f, 0.0f, 12.0f),
			glm::vec3(-3.0f, 0.0f, 25.0f),
			glm::vec3(-4.0f, 0.0f, 9.0f),
			glm::vec3(24.0f, 0.0f, -13.0f),
			glm::vec3(21.0f, 0.0f, -18.0f),
			glm::vec3(11.0f, 0.0f, -14.0f),
			glm::vec3(-4.0f, 0.0f, -1.0f),
			glm::vec3(-19.0f, 0.0f, 22.0f),
			glm::vec3(-11.0f, 0.0f, 25.0f), // 40
			glm::vec3(-1.0f, 0.0f, -17.0f),
			glm::vec3(0.0f, 0.0f, -3.0f),
			glm::vec3(1.0f, 0.0f, -7.0f),
			glm::vec3(1.0f, 0.0f, 18.0f),
			glm::vec3(4.0f, 0.0f, 25.0f),
			glm::vec3(8.0f, 0.0f, 16.0f),
			glm::vec3(24.0f, 0.0f, -18.0f),
			glm::vec3(-5.0f, 0.0f, -26.0f),
			glm::vec3(13.0f, 0.0f, 24.0f),
			glm::vec3(19.0f, 0.0f, 18.0f), // 50
		};

		// this for loop creates 50 trees
		for (int ii = 0; ii < 50; ii++)
		{
			glBindVertexArray(VAO_box);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_wood);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_wood_specular);

			// for loop for the tree trunk
			for(int tab = 0; tab < 1; tab++)
			{	
				model = glm::mat4();
				model = glm::translate(model, tree_positions[0]);
				model = glm::translate(model, clone_tree_positions[ii]);
				model = glm::scale(model, tree_scales[0]);
				model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

				// rotates the tree trunk if 2 items are found
				if (ITEM_COUNT == 2)
				{
					model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));

				}

				lighting_shader.setMat4("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			// leaves
			glBindVertexArray(VAO_box);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_greenleaves);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_grass_specular);

			// for loop for the tree leaves
			for(int tab = 1; tab < 2; tab++)
			{	
				model = glm::mat4();
				model = glm::translate(model, tree_positions[tab]);
				model = glm::translate(model, clone_tree_positions[ii]);
				model = glm::scale(model, tree_scales[tab]);
				model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
				model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, -1.0f, 0.0f));

				lighting_shader.setMat4("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}

		// slenderman
		glm::vec3 slender_scales[] = {
			glm::vec3(0.23f, 0.45f, 0.23f), // head
			glm::vec3(0.3f, 1.2f, 0.3f), // body
			glm::vec3(0.1f, 2.5f, 0.1f), // left arm
			glm::vec3(0.1f, 2.5f, 0.1f), // right arm
			glm::vec3(0.1f, 2.5f, 0.1f), // left leg
			glm::vec3(0.1f, 2.5f, 0.1f) // right leg
		};

		glm::vec3 slender_positions[] = {
			glm::vec3(0.0f, 3.0f, 0.0f), // head
			glm::vec3(0.0f, 2.2f, 0.0f), // body 
			glm::vec3(-0.2f, 1.55f, 0.0f), // left arm
			glm::vec3(0.2f, 1.55f, 0.0f), // right arm
			glm::vec3(-0.08f, 1.0f, 0.0f), // left leg
			glm::vec3(0.08f, 1.0f, 0.0f) // right leg
		};
	
		toggle_alive_distance(camera_pos);
		float slenderSpeed = 1.6f * delta_time; // speed at which slenderman moves towards the camera
		slender_pos += slenderSpeed * glm::normalize(camera_pos - slender_pos); // changes the position of slenderman
		slender_pos[1] = 0.0f; // makes slenderman stay on ground

		glBindVertexArray(VAO_box);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_white);
	
		// head of slenderman
		for(int tab = 0; tab < 1; tab++)
		{	
			model = glm::mat4();

			// if player is alive and has not won, slenderman will continuously chase camera
			if ((ALIVE) && (!VICTORY))
			{
				model = glm::translate(model, slender_pos); // translates slenderman
				model = rotate(model, glm::radians(yaw + 90.0f), glm::vec3(0.0f, -1.0f, 0.0f)); // similar to making slenderman face camera
			}

			model = glm::translate(model, slender_positions[tab]);
			model = glm::scale(model, slender_scales[tab]);
		
			lighting_shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(VAO_box);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_black);

		// body for slenderman
		for(int tab = 0; tab < 6; tab++)
		{	
			model = glm::mat4();

			// if player is alive and has not won, slenderman will continuously chase camera
			if ((ALIVE) && (!VICTORY))
			{
				model = glm::translate(model, slender_pos); // translates slenderman
				model = rotate(model, glm::radians(yaw + 90.0f), glm::vec3(0.0f, -1.0f, 0.0f)); // similar to making slenderman face camera
			}

			model = glm::translate(model, slender_positions[tab]);
			model = glm::scale(model, slender_scales[tab]);
			
			lighting_shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}		

		// torch
		glm::vec3 torch_scales[] = {
			glm::vec3(0.15f, 0.15f, 0.15f), // head of torch
			glm::vec3(0.35f, 0.12f, 0.1f) // body of torch
		};

		glm::vec3 torch_positions[] = {
			glm::vec3(-0.2f, 0.12f, 0.0f), // head of torch
			glm::vec3(0.0f, 0.12f, 0.0f) // body of torch
		};

		glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_metal);
	
		toggle_torch_distance(torch_pos);

		for(int tab = 0; tab < 2; tab++)
		{	
			model = glm::mat4();

			if (TORCH_PICKEDUP)
			{
				// if torch picked up, moves model of torch under the floor to make it disappear
				torch_pos = glm::vec3(0.0f, -5.0f, 0.0f);
			}

			model = glm::translate(model, torch_pos);
			model = glm::translate(model, torch_positions[tab]);
			model = glm::scale(model, torch_scales[tab]);

			lighting_shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);	
		}	
	
		// gravestones
		glm::vec3 grave_scales[] = {
			glm::vec3(0.15f, 1.2f, 0.8f),	// top slab
			glm::vec3(1.1f, 0.15f, 0.9) // bottom slab
		};
		glm::vec3 grave_positions[] = {
			glm::vec3(-0.4f, 0.1f, 0.0f), // top slab
			glm::vec3(0.0f, 0.0, 0.0f) // bottom slab
		};
		// array to store positions for multiple gravestones
		glm::vec3 clone_grave_positions[] = {
			glm::vec3(-27.0f, 0.0f, 8.0f),
			glm::vec3(-27.0f, 0.0f, 9.5f),
			glm::vec3(-27.0f, 0.0f, 11.0f),
			glm::vec3(-27.0f, 0.0f, 12.5f)
		};

		// this for loop creates 4 gravestones
		for (int ii = 0; ii < 4; ii++)
		{
			glBindVertexArray(VAO_box);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_marble_diffuse);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_marble_specular);

			// for loop for the gravestones
			for(int tab = 0; tab < 2; tab++)
			{	
				model = glm::mat4();
				model = glm::translate(model, grave_positions[tab]);
				model = glm::translate(model, clone_grave_positions[ii]);
				model = glm::scale(model, grave_scales[tab]);
				model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

				lighting_shader.setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}

		// table 
		glm::vec3 table_scales[] = {
			glm::vec3(1.0f, 0.1f, 1.0f), // top
			glm::vec3(0.1f, 0.5f, 0.1f), // near left
			glm::vec3(0.1f, 0.5f, 0.1f), // near right
			glm::vec3(0.1f, 0.5f, 0.1f), // far left
			glm::vec3(0.1f, 0.5f, 0.1f)	// far right
		};
		glm::vec3 table_positions[] = {
			glm::vec3(0.0f, 0.6f, 0.0f), //top
			glm::vec3(-0.45f, 0.5f, 0.45f), //near left
			glm::vec3(0.45f, 0.5f, 0.45f), //near right
			glm::vec3(-0.45f, 0.5f, -0.45f), //far left
			glm::vec3(0.45f, 0.5f, -0.45f) //far right
		};

		glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_wood_diffuse);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_wood_specular);

		for(int tab = 0; tab < 5; tab++)
		{	
			model = glm::mat4();
			model = glm::translate(model, table_pos);
			model = glm::translate(model, table_positions[tab]);
			model = glm::scale(model, table_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));

			lighting_shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// dagger
		glm::vec3 dagger_scales[] = {
			glm::vec3(0.5f, 0.04f, 0.04f), // blade
			glm::vec3(0.25f, 0.04f, 0.05f), // horizontal hilt
			glm::vec3(0.06f, 0.03f, 0.2f) // vertical hilt
		};
		glm::vec3 dagger_positions[] = {
			glm::vec3(-0.03f, 0.002f, 0.0f), // blade
			glm::vec3(-0.4f, 0.002f, 0.0f), // horizontal hilt
			glm::vec3(-0.32f, 0.002f, 0.0f) // vertical hilt
		};

		glBindVertexArray(VAO_box);
		toggle_dagger_distance(dagger_pos);

		// for loop for the dagger
		for(int tab = 0; tab < 3; tab++)
		{	
			model = glm::mat4();

			if (tab == 0)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_metal);
			}
			else
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_red);
			}

			if (DAGGER_PICKEDUP)
			{
				dagger_pos = glm::vec3(1.0f, -5.0f, 0.0f); // translates dagger under floor when picked up
			}
	
			model = glm::translate(model, dagger_pos);
			model = glm::translate(model, dagger_positions[tab]);
			model = glm::scale(model, dagger_scales[tab]);

			lighting_shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);	
		}

		// gun
		glm::vec3 gun_scales[] = {
			glm::vec3(0.45f, 0.2f, 0.1f), // gun
			glm::vec3(0.1f, 0.2f, 0.2f), // handle
		};
		glm::vec3 gun_positions[] = {
			glm::vec3(0.0f, 0.002f, 0.0f), // gun
			glm::vec3(0.17f, 0.002f, 0.15f), // handle
		};

		glBindVertexArray(VAO_box);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_metal);

		toggle_gun_distance(gun_pos);

		// for loop for the gun
		for(int tab = 0; tab < 2; tab++)
		{	
			model = glm::mat4();

			if (GUN_PICKEDUP)
			{
				gun_pos = glm::vec3(2.0f, -5.0f, 0.0f); // translates gun under floor when picked up
			}
	
			model = glm::translate(model, gun_pos);
			model = glm::translate(model, gun_positions[tab]);
			model = glm::scale(model, gun_scales[tab]);

			lighting_shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);	
		}

		// escape
		glm::vec3 escape_scales[] = {
			glm::vec3(2.5f, 5.0f, 0.1f), // door thing
			glm::vec3(0.1f, 5.0f, 3.0f) // left side
		};
		glm::vec3 escape_positions[] = {
			glm::vec3(0.21f, 2.5f, -3.4f), // door thing
			glm::vec3(-1.1f, 2.5f, -4.85f) // left side
		};
		glm::vec3 clone_escape_position[] = {
			glm::vec3(28.5f, 0.002f, -23.5)
		};

		glBindVertexArray(VAO_box);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_container);

		// for loop for the escape
		for(int tab = 0; tab < 2; tab++)
		{	
			if (SPAWN_VICTORY_AREA == true)
			{
				model = glm::mat4();
				model = glm::translate(model, escape_positions[tab]);
				model = glm::translate(model, clone_escape_position[0]);
				model = glm::scale(model, escape_scales[tab]);

				lighting_shader.setMat4("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);	
			}
		} 

		// win cube
		glm::vec3 winCube_scales[] = {
			glm::vec3(1.0f, 1.0f, 1.0f)
		};
		glm::vec3 winCube_positions[] = {
			glm::vec3(28.4f, 1.0f, -28.0f) 
		};

		glBindVertexArray(VAO_box);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_grass_diffuse);

		toggle_cube_distance(winCube_pos);

		// for loop for the win cube
		for(int tab = 0; tab < 1; tab++)
		{	
			if (ITEM_COUNT == 2)
			{	
				model = glm::mat4();
				model = glm::translate(model, winCube_positions[tab]);
				model = glm::scale(model, winCube_scales[tab]);
				lighting_shader.setMat4("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);	
			}
		} 

		// win screen
		glm::vec3 winScreen_scales[] = {
			glm::vec3(3.0f, 2.0f, 0.1f)
		};
		glm::vec3 winScreen_positions[] = {
			glm::vec3(0.0f, 2.0f, 32.0f) 
		};

		glBindVertexArray(VAO_box);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_win);

		// for loop for the win screen
		for(int tab = 0; tab < 1; tab++)
		{	
			model = glm::mat4();
			model = glm::translate(model, winScreen_positions[tab]);
			model = glm::scale(model, winScreen_scales[tab]);
			lighting_shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);	
		} 
		
		// lose screen
		glm::vec3 loseScreen_scales[] = {
			glm::vec3(0.3f, 0.2, 0.1f)
		};

		glBindVertexArray(VAO_box);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_lose);

		// for loop for the lose screen
		for(int tab = 0; tab < 1; tab++)
		{	
			if (!ALIVE)
			{
				model = glm::mat4();
				model = glm::translate(model, camera_pos + camera_front); // translates the lose object in front of camera
				model = rotate(model, glm::radians(yaw + 90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
				model = glm::scale(model, loseScreen_scales[tab]);
				ATTENUATION_NUM = 1; // set attenuation low so the screen is visible
				lighting_shader.setMat4("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);	
			}
		} 

		// spawns the victory area if player picks up the dagger and gun
		if (ITEM_COUNT == 2)
		{
			SPAWN_VICTORY_AREA = true;
		}

		// if player wins, moves the camera to win screen
		if (VICTORY)
		{
			camera_pos[0] = 0.0f;
			camera_pos[1] = 2.0f;
			camera_pos[2] = 35.0f;
		}

		// Draw the light source
		if (TORCH_PICKEDUP)
		{
			lamp_shader.use();
			lamp_shader.setMat4("projection", projection);
			lamp_shader.setMat4("view", view);
			model = glm::mat4();
			model = glm::translate(model, camera_pos + camera_front);
			model = glm::scale(model, glm::vec3(0.03f)); // a smaller cube
			lamp_shader.setMat4("model", model);

			// this makes it so that the light automatically turns on
			BUTTON_PRESSED = true; 
			lamp_shader.setFloat("intensity", 1.0);

			glBindVertexArray(VAO_light);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		else // this is what the light source looks like on the ground without being picked up
		{
			lamp_shader.use();
			lamp_shader.setMat4("projection", projection);
			lamp_shader.setMat4("view", view);
			model = glm::mat4();
			model = glm::translate(model, torch_pos);
			model = glm::translate(model, glm::vec3(-0.2f, 0.12f, 0.0f)); 
			model = glm::scale(model, glm::vec3(0.17)); // a smaller cube
			lamp_shader.setMat4("model", model);

			// this makes it so that the light automatically turns on
			BUTTON_PRESSED = true; 

			lamp_shader.setFloat("intensity", 1.0);

			glBindVertexArray(VAO_light);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO_box);
	glDeleteBuffers(1, &VBO_box);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (!ALIVE) // when player is dead, set the Y pos of the camera to be 0.1 to imitate "on the floor"
	{
		camera_pos[1] = 0.1f;
	}
	
	if ((ALIVE) && (!VICTORY))
	{
		// variables
		float cameraSpeed;
		camera_pos[1] = 1.4f; // sets it so that player cannot fly when looking up/down

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			cameraSpeed = 2.5 * delta_time; 
		}
		else
		{
			cameraSpeed = 2.5 * delta_time * 2;	// double speed with "Shift" pressed
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera_pos += cameraSpeed * camera_front;
		}	
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera_pos -= cameraSpeed * camera_front;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;
		}

		// limit player from exceeding these boundaries on the map
		// if the x pos of my camera reaches -29, it sets it to be 29 so the player can't exceed that boundary
		if (camera_pos.x < -29)
		{
			camera_pos.x = -29;
		}

		if (camera_pos.x > 29)
		{
			camera_pos.x = 29;
		}

		if (camera_pos.z < -29)
		{
			camera_pos.z = -29;
		}

		if (camera_pos.z > 29)
		{
			camera_pos.z = 29;
		}

		// toggle ambient lighting
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && AMBIENT_DELAY == 0)
		{
			AMBIENT_DELAY = 20;
			if (AMBIENT_LIGHT)
			{
				AMBIENT_LIGHT = false;
			}
			else
			{
				AMBIENT_LIGHT = true;
			}
		}

		// toggle brightness up
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		{
			// if attenuation value is greater than 0, can decrease brightness
			if ((TORCH_PICKEDUP) && (ATTENUATION_NUM > 0))
			{
				ATTENUATION_NUM--;
			}
		}

		// toggle brightness down
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			// if attenuation value is less than 6, can increase brightness
			if ((TORCH_PICKEDUP) && (ATTENUATION_NUM < 6))
			{
				ATTENUATION_NUM++;
			}
		} 

		// toggle orthographic mode (not working)
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && SHOW_DELAY == 0)
		{
			if (ORTHOGRAPHIC_MODE)
			{
				ORTHOGRAPHIC_MODE = false;
			}
			else
			{
				ORTHOGRAPHIC_MODE = true;
			}
			SHOW_DELAY = 20;
		} 
	}

	// restart button
	// resets the objects to original positions
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && BUTTON_DELAY == 0)
	{
		BUTTON_DELAY = 20;
		
		camera_pos = reset_camera_pos;
		camera_up = reset_camera_up;
		camera_front = reset_camera_front;
		light_pos = reset_light_pos;
		torch_pos = reset_torch_pos;
		slender_pos = reset_slender_pos;
		dagger_pos = reset_dagger_pos;
		gun_pos = reset_gun_pos;
		winCube_pos = reset_winCube_pos;

		BUTTON_PRESSED = false;
		ALIVE = true;
		TORCH_PICKEDUP = false;
		DAGGER_PICKEDUP = false;
		GUN_PICKEDUP = false;
		AMBIENT_LIGHT = false;
		VICTORY = false;
		SPAWN_VICTORY_AREA = false;
		ITEM_COUNT = 0;
		ATTENUATION_NUM = 3;
		ORTHOGRAPHIC_MODE = false;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is used
// ---------------------------------------------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (ALIVE)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}
	
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; 
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.020f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw   += xoffset;
		pitch += yoffset;

		if(pitch > 89.0f)
			pitch = 89.0f;
		if(pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		camera_front = glm::normalize(direction);
	}
}  

unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}