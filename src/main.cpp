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
//multi-thread
PixelIterator pIt;

bool TraceRay(const Ray& ray, HitInfo& hitInfo);
bool TraceNode(const Node& node, const Ray& ray, HitInfo& hitInfo);

bool TraceRay(const Ray& ray, HitInfo& hitInfo)
{
    return TraceNode(rootNode, ray, hitInfo);
}
bool TraceNode(const Node& node, const Ray& ray, HitInfo& hitInfo)
{
    bool isHit = false;

    Ray nodeRay = node.ToNodeCoords(ray);
    //const Object* obj =  node.GetNodeObj();

    if(const Object* obj = node.GetNodeObj())
    {
        if(obj->IntersectRay(nodeRay, hitInfo))
        {
            hitInfo.node = &node;
            isHit = true;
        }
    }

    for (int i = 0; i < node.GetNumChild(); ++i) {
        const Node* childNode = node.GetChild(i);
        if( TraceNode(*childNode, nodeRay, hitInfo))
        {
            isHit = true;
        }
    }

    return isHit;
}
void RenderPixel(int pixelIndex, float zBuffer, Color color)
{
    Color24* img = renderImage.GetPixels();
    img[pixelIndex] = static_cast<Color24>(color);
}
void RenderScene(PixelIterator &pi, int threadInd)
{
    float l = 1; // distance from camera to image plane
    float aspectRatio = (float)camera.imgWidth / camera.imgHeight;
    float h = l * tan((Utility::toRadian(camera.fov/2.))) * 2; // height of the image plane
    float w = aspectRatio * h; // width of the image plane
    
    Vec3f topLeftPixel(-w/2., h/2., -l);
    topLeftPixel += camera.pos;
    
    camera.dir.Normalize();
    camera.up.Normalize();
    
    
    Matrix3f worldToCamera( camera.up.Cross(-camera.dir).GetNormalized() , camera.up ,-camera.dir);
    
    int x,y;

    while(pi.GetPixel(x,y)){
        
        /* Multi-thread visualization
        Color c(1, 0,0);
        vector<Color> colorPallet = {Color(1,0,0), Color(0,1,0), Color(0,0,1), Color(0, 1, 1),
                                   Color(1,0,1), Color(1,1,0), Color(.5,0,0.5), Color(1, .5, 0)};
        img[index] = static_cast<Color24> (colorPallet[threadInd]);
        */
        
        Vec3f pixelTarget( (x+.5)* w / camera.imgWidth, -(y+.5)* h / camera.imgHeight , 0);
        pixelTarget += topLeftPixel;
        Ray cameraRay(camera.pos, pixelTarget - camera.pos);
        cameraRay.dir = worldToCamera * cameraRay.dir;
        cameraRay.dir.Normalize();

        HitInfo hitInfo;
        
        if(rootNode.GetNumChild()>0){
            
            int index = y*camera.imgWidth+x;
            if(TraceRay(cameraRay,hitInfo)){
                //set color
                //setPixelColor(index,hitinfo.z,hitinfo.node->GetMaterial()->Shade(ray_pixel, hitinfo, lights));
                RenderPixel(index, BIGFLOAT, Color24::White().ToColor());
                //img[index] = Color24::White();
                
            }
            else{
                //setPixelColor(index,BIGFLOAT,black);
                RenderPixel(index, BIGFLOAT, Color24::Black().ToColor());
                //img[index] = Color24::Black();
            }
            renderImage.IncrementNumRenderPixel(1);
        }
    }
}
void BeginRender()
{
    auto numThread = thread::hardware_concurrency();
    cout << "Number of threads: " << numThread << endl;
    vector<thread> threads;
    for(size_t i = 0; i < numThread; ++i)
    {
        threads.emplace_back(RenderScene, ref(pIt), i);
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
