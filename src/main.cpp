#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

#include "scene.h"
#include "objects.h"
#include "utility.cpp"

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
    LoadScene("../../myscene.xml");
    ShowViewport();
    cout << "Hello World! \n";
    return 0;
}
