noinst_PROGRAMS = hillstoneUnited

AUTOMAKE_OPTIONS = subdir-objects

# hillstoneUnited_CPPFLAGS = -Wall
LDADD = ${RCSS3D_LDFLAGS} -lrcssnet3D \
	${BOOST_REGEX_LIB}

hillstoneUnited_MAIN = main.cpp \
											 rcss3dsocket.hpp rcss3dsocket.cpp \
											 robot.hpp robot.cpp \
											 world.hpp world.cpp \
											 elementbase.hpp \
											 util.hpp

brain = brain/brainbase.hpp brain/brainbase.cpp \
		brain/runtoball.hpp brain/runtoball.cpp

movement = movement/movementbase.hpp movement/movementbase.cpp \
					 movement/ticktackbase.hpp movement/ticktackbase.cpp \
					 movement/gabase.hpp movement/gabase.cpp \
					 movement/pose.hpp movement/pose.cpp \
					 movement/sequence.hpp movement/sequence.cpp \
					 movement/sequencemovement.hpp movement/sequencemovement.cpp \
					 movement/standup.hpp movement/standup.cpp \
					 movement/odenswalk.hpp movement/odenswalk.cpp

MakeWalk = MakeWalk/makewalk.hpp MakeWalk/makewalk.cpp MakeWalk/update.cpp \
					 MakeWalk/makewalk-set.cpp MakeWalk/inversekinematics.cpp \
					 MakeWalk/legvelocity.cpp MakeWalk/init.cpp \
					 MakeWalk/quickinit.cpp MakeWalk/walkcontrol.cpp \
					 MakeWalk/jointupdate.cpp MakeWalk/setheeltoe.cpp \
					 MakeWalk/legtrajectory.cpp MakeWalk/setyawangle.cpp \
					 MakeWalk/setanklepos.cpp MakeWalk/invertedpendulum.cpp \
					 MakeWalk/coordinateconverter.cpp MakeWalk/timeupdate.cpp \
					 MakeWalk/angletrajectory.cpp MakeWalk/outputcommand.cpp

hillstoneUnited_SOURCES = $(hillstoneUnited_MAIN) $(brain) $(movement) $(MakeWalk)
