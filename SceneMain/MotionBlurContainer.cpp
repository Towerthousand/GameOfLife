#include "MotionBlurContainer.hpp"

MotionBlurContainer::MotionBlurContainer() : scene(NULL) {
	setName("deferred");
	scene = new RenderTarget();
	scene->addTexture(RenderTarget::DEPTH, Texture::DEPTH_COMPONENT32); //Z-BUFFER
	scene->addTexture(RenderTarget::COLOR0, Texture::RGBA8); //COLOR
	scene->ensureValid();
	scene->getTextureForAttachment(RenderTarget::COLOR0)->setFilter(GL_NEAREST, GL_NEAREST);
	quad.mesh = Meshes.get("quad");
	quad.program = Programs.get("motionBlur");
}

MotionBlurContainer::~MotionBlurContainer() {
	delete scene;
}

void MotionBlurContainer::update(float deltaTime) {
	ContainerObject::update(deltaTime);
}

void MotionBlurContainer::draw() const {
	//"The Screen". It may not be actually the screen since a upper container might be postprocessing
	RenderTarget* screen = RenderTarget::getCurrent();
	//SCENE
	GL_ASSERT(glEnable(GL_DEPTH_TEST));
	GL_ASSERT(glDisable(GL_BLEND)); //no transparency whatsoever

	RenderTarget::bind(scene);
	GL_ASSERT(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));
	ContainerObject::draw();

	RenderTarget::bind(screen);
	//GL_ASSERT(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));

	//COSAS
	GL_ASSERT(glEnable(GL_BLEND));
	GL_ASSERT(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));
	GL_ASSERT(glDepthMask(GL_TRUE));
	GL_ASSERT(glDepthFunc(GL_ALWAYS));

	//AMBIENT LIGHT
	quad.program->uniform("tex")->set(scene->getTextureForAttachment(RenderTarget::COLOR0));
	quad.program->uniform("alpha")->set(0.1f);
	quad.program->uniform("invResolution")->set(vec2f(1.0f/screen->getWidth(), 1.0f/screen->getHeight()));
	quad.draw();

	GL_ASSERT(glDepthFunc(GL_LEQUAL));
	GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); //forward rendering blending
}
