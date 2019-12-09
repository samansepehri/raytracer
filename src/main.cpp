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

class PixelIterator{
private:
    atomic<int> ix;
public:
    void Init(){ ix = 0;}
    bool GetPixel(int &x, int &y){
        int i=ix++;
        if(i>=camera.imgWidth*camera.imgHeight) return false;
        x = i%camera.imgWidth;
        y = i/camera.imgWidth;
        return true;
    }
};
//multi-thread
PixelIterator pIt;

void RenderPixel(PixelIterator &pi, int threadInd)
{
    
    float l = 1; // distance from camera to image plane
    float aspectRatio = camera.imgWidth / camera.imgHeight;
    float h = l * tan((Utility::toRadian(camera.fov/2.))) * 2; // height of the image plane
    float w = aspectRatio * h; // width of the image plane
    
    Vec3f topLeftPixel(-w/2., h/2., -l);
    topLeftPixel += camera.pos;
    
    camera.dir.Normalize();
    camera.up.Normalize();
    
    
    Matrix3f worldToCamera( camera.up.Cross(-camera.dir).GetNormalized() , camera.up ,camera.dir);
    
    int x,y;
    Color24* img = renderImage.GetPixels();

    while(pi.GetPixel(x,y)){
        
        int index = y*camera.imgWidth+x;

        Color c(1, 0,0);
        vector<Color> colorPallet = {Color(1,0,0), Color(0,1,0), Color(0,0,1), Color(0, 1, 1),
                                   Color(1,0,1), Color(1,1,0), Color(.5,0,0.5), Color(1, .5, 0)};
        img[index] = static_cast<Color24> (colorPallet[threadInd]);

        Vec3f pixelTarget( (x+.5)* w / camera.imgWidth, -(y+.5)* h / camera.imgHeight , 0);
        pixelTarget += topLeftPixel;
        Ray cameraRay(camera.pos, pixelTarget - camera.pos);
        cameraRay.dir.Normalize();


        //renderImage.IncrementNumRenderPixel(1);
    }
}
void BeginRender()
{
    auto noThread = thread::hardware_concurrency();
    cout << "Number of threads: " << noThread << endl;
    vector<thread> threads;
    for(size_t i = 0; i < noThread; ++i)
    {
        threads.emplace_back(RenderPixel, ref(pIt), i);
    }
    
    for(auto &t:threads)
        t.join();
    
    
    int size = renderImage.GetWidth()*renderImage.GetHeight();
    // generate a ray for each pixel
    // hit testing
    // shading
    // write to pixel (img using renderImage.GetPixels() )
    //Color24* img = renderImage.GetPixels();
    
    Color c(1, 0,0);
    //img[30000] = static_cast<Color24>(c);
    //img[30001] = static_cast<Color24>(c);
    //img[30002] = static_cast<Color24>(c);
    //img[30003] = static_cast<Color24>(c);
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
