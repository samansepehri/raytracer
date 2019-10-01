#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

#include "scene.h"
#include "objects.h"
#include "viewport.cpp"
#include "xmlload.cpp"

using namespace std;

Node rootNode;
Camera camera;
RenderImage renderImage;
Sphere theSphere;

void BeginRender()
{

}

void StopRender()
{

}

int main()
{   
    ShowViewport();
    cout << "Hello World! \n";
    return 0;
}
