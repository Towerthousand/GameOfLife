#ifndef MOTIONBLURCONTAINER_HPP
#define MOTIONBLURCONTAINER_HPP
#include "commons.hpp"

class MotionBlurContainer : public ContainerObject {
	public:
		MotionBlurContainer();
		~MotionBlurContainer();

	private:
		void update(float deltaTime);
		void draw() const;

		RenderTarget* scene;
		mutable Model quad;
};

#endif // MOTIONBLURCONTAINER_HPP
