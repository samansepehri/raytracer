#include "utility.h"
#include <thread>
#include "viewport.cpp"
#include "xmlload.cpp"

using namespace std;

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
extern PixelIterator PI;
