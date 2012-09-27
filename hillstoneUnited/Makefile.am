noinst_PROGRAMS = hillstoneUnited
SUBDIRS = movement
hillstoneUnited_SOURCES = main.cpp \
			rcss3dsocket.h rcss3dsocket.cpp \
			robot.h robot.cpp \
			world.h world.cpp \
			action.h action.cpp \
			movementmanager.h movementmanager.cpp \
			BrainManager.h BrainManager.cpp \
			BrainBase.h BrainBase.cpp\
			TestBrain.h TestBrain.cpp\
			ResponceBase.h ResponceBase.cpp\
			FallDownResponce.h FallDownResponce.cpp\
			util.h
#			$(mSources)

#hillstoneUnited_CPPFLAGS = -Wall

LDADD = ${RCSS3D_LDFLAGS} -lrcssnet3D \
	${BOOST_REGEX_LIB} \
	movement/libmovement.a
