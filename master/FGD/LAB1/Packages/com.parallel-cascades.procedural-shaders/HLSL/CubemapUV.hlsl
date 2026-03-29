#ifndef CUBEMAP_UV_INCLUDED
#define CUBEMAP_UV_INCLUDED

#include "Hash.hlsl"

void cubemapUVOffset_float(float3 objectPos, float2 uv, float offset, out float2 uvWithOffset)
{
    objectPos = normalize(objectPos);
    
    // Determine the major axis
    float absX = abs(objectPos.x);
    float absY = abs(objectPos.y);
    float absZ = abs(objectPos.z);
    
    if (absX >= absY && absX >= absZ) {
        // Major axis is X
        uvWithOffset = sign(objectPos.x) * float2(0,1) * offset + uv;
    } else if (absY >= absX && absY >= absZ) {
        // Major axis is Y
        uvWithOffset = sign(objectPos.y) * float2(1,1)* offset + uv;
    } else {
        // Major axis is Z
        uvWithOffset = sign(objectPos.z) * float2(1,0)* offset + uv;
    }
}



#endif