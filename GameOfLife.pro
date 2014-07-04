include(VBE/VBE.pro)
INCLUDEPATH += $$PWD/
#DEFINES += __DLOG
SOURCES += main.cpp \
	commons.cpp \
	SceneMain/SceneMain.cpp \
	SceneMain/DeferredContainer.cpp \
	SceneMain/DeferredLight.cpp \
	SceneMain/BlurContainer.cpp \
        SceneMain/Player.cpp \

HEADERS += \
	commons.hpp \
	SceneMain/SceneMain.hpp \
	SceneMain/DeferredContainer.hpp \
	SceneMain/DeferredLight.hpp \
	SceneMain/BlurContainer.hpp \
        SceneMain/Player.hpp \

OTHER_FILES += \
	data/shaders/light.frag \
	data/shaders/blurPassVertical.frag \
	data/shaders/blurPassHoritzontal.frag \
	data/shaders/blurMaskPass.frag \
	data/shaders/quad.frag \
	data/shaders/depth.frag \
	data/shaders/depth.vert \
	data/shaders/standardDeferred.vert \
	data/shaders/standardDeferred.frag \
	data/shaders/ambientPass.frag \
        data/shaders/debug.frag