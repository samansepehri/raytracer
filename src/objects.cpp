
#include "objects.h"

bool Sphere::IntersectRay( Ray const &ray, HitInfo &hInfo, int hitSide ) const
{
    
    float A = ray.dir.Dot(ray.dir);
    float B = 2*ray.dir.Dot(ray.p);
    float C = ray.p.Dot(ray.p) - 1;
    float delta2 = B*B - 4*A*C;
    
    if(delta2 < 0) return false;
    return true;
}
