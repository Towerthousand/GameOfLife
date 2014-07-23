#include "SceneMain.hpp"
#include "MotionBlurContainer.hpp"
#include "Player.hpp"
#include "SimScreen.hpp"

SceneMain::SceneMain() : debugCounter(0.0f), fpsCount(0) {
	this->setName("SCENE");

	loadResources();
	srand(Environment::getClock());

	//GL stuff..:
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE); //enable backface culling
	glCullFace(GL_BACK);
	glPointSize(4.0f);

	MotionBlurContainer* renderer = new MotionBlurContainer();
    renderer->addTo(this);

	Player* player = new Player();
	player->addTo(renderer);

	SimScreen* ss = new SimScreen();
	ss->addTo(renderer);
}

SceneMain::~SceneMain() {
	Textures2D.clear();
	Meshes.clear();
	Programs.clear();
}

void SceneMain::loadResources() {
	//meshes
	std::vector<Vertex::Element> elems = {
		Vertex::Element(Vertex::Attribute::Position, Vertex::Element::Float, 3),
		Vertex::Element(Vertex::Attribute::Normal, Vertex::Element::Float, 3),
		Vertex::Element(Vertex::Attribute::TexCoord, Vertex::Element::Float, 2)
	};
	struct Vert { vec3f p; vec3f n; vec2f t;};
	std::vector<Vert> data = {
		{ vec3f(-1, -1, 0), vec3f(0, 0, 1), vec2f(0,0)},
		{ vec3f(1, -1, 0), vec3f(0, 0, 1), vec2f(1,0)},
		{ vec3f(-1, 1, 0), vec3f(0, 0, 1), vec2f(0,1)},
		{ vec3f(1, 1, 0), vec3f(0, 0, 1), vec2f(1,1)}
	};
	Mesh* quad = Mesh::loadEmpty(Vertex::Format(elems));
	quad->setVertexData(&data[0], 6);
	quad->setPrimitiveType(Mesh::TRIANGLE_STRIP);
	Meshes.add("quad", quad);
	Meshes.add("monkey", Mesh::loadFromFile("data/meshes/monkey.obj"));

	//textures
	char pixels[4] = {char(200), char(20), char(20), char(255)};
	Textures2D.add("nullRed", Texture2D::createFromRaw(pixels, 1, 1));
	char pixels2[4] = {char(20), char(200), char(20), char(255)};
	Textures2D.add("nullGreen", Texture2D::createFromRaw(pixels2, 1, 1));
	char pixels3[4] = {char(20), char(20), char(200), char(255)};
	Textures2D.add("nullBlue", Texture2D::createFromRaw(pixels3, 1, 1));
	char pixels4[4] = {char(70), char(30), char(80), char(255)};
	Textures2D.add("nullBlack", Texture2D::createFromRaw(pixels4, 1, 1));
	char pixels5[4] = {char(255), char(255), char(255), char(255)};
	Textures2D.add("nullWhite", Texture2D::createFromRaw(pixels5, 1, 1));

	//program
	Programs.add("motionBlur", ShaderProgram::loadFromFile("data/shaders/passthrough.vert", "data/shaders/motionBlur.frag"));
	Programs.add("textured", ShaderProgram::loadFromFile("data/shaders/texturedMVP.vert", "data/shaders/texturedVT.frag"));
	Programs.add("simulation", ShaderProgram::loadFromFile("data/shaders/texturedNOMVP.vert", "data/shaders/simulation.frag"));
}

void SceneMain::update(float deltaTime) {
	++fpsCount;
	debugCounter += deltaTime;
	if (debugCounter > 1) {
		VBE_LOG("FPS: " << fpsCount);
		debugCounter--;
		fpsCount = 0;
	}
}
