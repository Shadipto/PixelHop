CXX = g++
CXXFLAGS = -std=c++17 -O2 -DGL_SILENCE_DEPRECATION
SRCS = main.cpp core/Game.cpp core/Renderer.cpp entities/Player.cpp entities/Platform.cpp input/Input.cpp
TARGET = platformer

UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
LIBS = -framework OpenGL -framework GLUT
else
LIBS = -lGL -lGLU -lglut
endif

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET) *.o
