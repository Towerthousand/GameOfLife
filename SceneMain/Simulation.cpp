#include "Simulation.hpp"

Simulation::Simulation(std::string inputFile) {
	tex = Texture2D::createFromFile(inputFile,Texture::RGBA,Texture::UNSIGNED_BYTE,Texture::RGBA8);
    WIDTH = tex->getWidth();
    HEIGHT = tex->getHeight();
	Texture2D* tex2 = Texture2D::createEmpty(WIDTH,HEIGHT,Texture::RGBA8);
	tex->setFilter(GL_NEAREST, GL_NEAREST);
    tex2->setFilter(GL_NEAREST, GL_NEAREST);
    RenderTarget* simTarget = new RenderTarget(WIDTH, HEIGHT);
    simTarget->addCustomTexture(RenderTarget::COLOR0, tex2);
    Model model;
    model.mesh = Meshes.get("quad");
    model.program = Programs.get("simulation");
    model.program->uniform("width")->set(WIDTH);
    model.program->uniform("height")->set(HEIGHT);
	data = new unsigned char[WIDTH*HEIGHT*NUM_FRAMES*4];

    //simulate
    int current = 0;
    RenderTarget* curr = RenderTarget::getCurrent();
    RenderTarget::bind(simTarget);
    GL_ASSERT(glBlendFunc(GL_ONE,GL_ONE));
    GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT));
    for(int i = 0; i < NUM_FRAMES; ++i) {
		current == 0? tex->bind() : tex2->bind();
		GL_ASSERT(glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[WIDTH*HEIGHT*4*(NUM_FRAMES-1-i)]));
        model.program->uniform("input")->set(current==0?tex:tex2);
        current = (current+1)%2;
        simTarget->setCustomTexture(RenderTarget::COLOR0, current==0?tex:tex2);
        GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT));
        model.draw();
    }
    RenderTarget::bind(curr);

	//set at start
	setFrame(0);

    //clean up
    delete simTarget;
    delete tex2;
}

Simulation::~Simulation() {
    delete tex;
	delete[] data;
}

void Simulation::setFrame(int frame) {
	VBE_ASSERT(frame >= 0 && frame < NUM_FRAMES,"Non-existent frame " << frame);
	tex->loadFromRaw((const void*) &data[WIDTH*HEIGHT*4*frame], WIDTH, HEIGHT, Texture::RGBA, Texture::UNSIGNED_BYTE, Texture::RGBA8);
	tex->setFilter(GL_NEAREST, GL_NEAREST);
	currentFrame = frame;
}

Texture2D*Simulation::getSimTex() {return tex;}
