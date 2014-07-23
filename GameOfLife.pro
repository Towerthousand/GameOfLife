include(VBE/VBE.pro)
INCLUDEPATH += $$PWD/
#DEFINES += __DLOG
SOURCES += main.cpp \
	commons.cpp \
	SceneMain/SceneMain.cpp \
        SceneMain/Player.cpp \
    SceneMain/Simulation.cpp \
    SceneMain/SimScreen.cpp \
    SceneMain/MotionBlurContainer.cpp

HEADERS += \
	commons.hpp \
	SceneMain/SceneMain.hpp \
        SceneMain/Player.hpp \
    SceneMain/Simulation.hpp \
    SceneMain/SimScreen.hpp \
    SceneMain/MotionBlurContainer.hpp

OTHER_FILES += \
    data/shaders/simulation.frag \
    data/shaders/passthrough.vert \
    data/shaders/texturedNOMVP.vert \
    data/shaders/texturedMVP.vert \
    data/shaders/texturedVT.frag \
    data/shaders/motionBlur.frag
