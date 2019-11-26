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
    int size = renderImage.GetWidth()*renderImage.GetHeight();
    // generate a ray for each pixel
    // hit testing
    // shading
    // write to pixel (img using renderImage.GetPixels() )
    Color24* img = renderImage.GetPixels();
    
    // result in the build folder
    renderImage.SaveImage("../render.png");
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
