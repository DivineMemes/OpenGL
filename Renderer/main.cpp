#include "context.h"
#include "render.h"
#include "glm/ext.hpp"
#include <cmath>
int main()
{
	context game;
	game.init(800, 600, "A jojo reference");

	vertex triVerts[] =
	{	//p o s i t i o n	 //n o r m s  //u v 's
		{{-.5f, -.5f,	0, 1}, {0,0,1,1}, {0,0} },
		{{ .5f, -.5f,	0, 1}, {0,0,1,1}, {1,0} },
		{{	0,	 .5f,	0, 1}, {0,0,1,1}, {0.5f,1}}
	};
	unsigned triIndicies[] = { 2, 1, 0 };

	geometry triangle = makeGeometry(triVerts, 3, triIndicies, 3);
	const char * basicVert =
		"#version 410\n"
		"layout (location = 0) in vec4 position;\n"
		"void main() {gl_Position = position;}";

	const char * mvpVert =
		"#version 430\n"
		"layout (location = 0) in vec4 position;\n"
		"layout (location = 1) in vec4 normal;\n"
		"layout (location = 2) in vec2 uv;\n"
		
		"out vec2 vUV;\n"
		"out vec3 vNormal;\n"

		"layout (location = 0) uniform mat4 proj;\n"
		"layout (location = 1) uniform mat4 view;\n"
		"layout (location = 2) uniform mat4 model;\n"

		"void main() {gl_Position = proj * view * model * position; vUV = uv; vNormal = normalize(model * normal).xyz;}";


	const char * basicFrag =
		"#version 330\n"
		"out vec4 vertColor;\n"
		"void main() {vertColor = vec4 (1.0, 0.0, 0.0, 1.0);}";


	const char * texFrag =
		"#version 430\n"
		"in vec2 vUV;\n"
		"in vec3 vNormal;\n"
		"out vec4 vertColor;\n"
		"layout (location = 3) uniform sampler2D albedo;\n"
		"layout (location = 4) uniform vec3 lightDir;\n"
		"void main() {float diffuse = max(0, dot(vNormal, -lightDir)); vertColor = texture(albedo, vUV); vertColor = vec4(vertColor.x * diffuse, vertColor.y * diffuse, vertColor.z * diffuse, 1);}";

	shader basicShad = makeShader(basicVert, basicFrag);
	shader mvpShad = makeShader(mvpVert, basicFrag);
    shader texShad = makeShader(mvpVert, texFrag);
	/*int r;
	int g;
	int b;*/

	unsigned char whitePixel[] = {255,255,255};

	texture whiteTexture = makeTexture(1, 1, 3, whitePixel);
	texture testTexture = loadTexture("download.png");
	texture newTex = makeTexture(1, 1, 3, whitePixel);

	glm::mat4 cam_proj = glm::perspective(glm::radians(45.f), 800.0f / 600.0f,  0.1f, 1000.0f);
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 triangle_model = glm::identity<glm::mat4>();

	glm::vec3 lightDir = glm::vec3(-1, 0, 0);

	while (!game.shouldClose())
	{
		game.tick();
		game.clear();
		triangle_model = glm::rotate(triangle_model, glm::radians(1.f), glm::vec3(1,100,1));
		setUniform(texShad, 0, cam_proj);
		setUniform(texShad, 1, cam_view);
		setUniform(texShad, 2, triangle_model);

		setUniform(texShad, 3, testTexture, 0);
		setUniform(texShad, 4, lightDir);
		/*r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;

		whitePixel[0] = r;
		whitePixel[1] = g;
		whitePixel[2] = b;*/
		//newTex = makeTexture(1, 1, 3, whitePixel);

		/*draw(mvpShad, triangle);*/
		draw(texShad, triangle);
	}
	game.term();
	return 0;
}