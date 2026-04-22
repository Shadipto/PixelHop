#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <map>
#include <set>
#include <utility>
#include <memory>
#include <functional>
#include <array>
#include <tuple>
#include <type_traits>
#include <limits>
#include <iomanip>
#include <cassert>

using namespace std;


#define PI 3.1416


#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
    #include <OpenGL/glu.h>
    #include <OpenGL/glext.h>
#elif defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glut.h>
    #include <GL/glu.h>
    #include <GL/glext.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
    #include <GL/glu.h>
    #include <GL/glext.h>
#endif