#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <thread>
#include "scene.h"
#include "objects.h"
#include "utility.cpp"

using namespace std;

Node rootNode;
Camera camera;
RenderImage renderImage;
Sphere theSphere;

void RenderPixel()
{
    
}
void BeginRender()
{
    auto noThread = thread::hardware_concurrency();
    vector<thread> threads;
    for(size_t i = 0; i < noThread; ++i)
    {
        threads.emplace_back(RenderPixel);
    }
    
    for(auto &t:threads)
        t.join();
    
    
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
