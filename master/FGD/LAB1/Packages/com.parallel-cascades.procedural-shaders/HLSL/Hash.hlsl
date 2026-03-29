#ifndef HASH_INCLUDED
#define HASH_INCLUDED

float mod(float x, float y)
{
    return x - y * floor(x/y);
}

//https://byteblacksmith.com/improvements-to-the-canonical-one-liner-glsl-rand-for-opengl-es-2-0/
float Hash21 (float2 st)
{
    float a = 12.9898;
    float b = 78.233;
    float c = 43758.5453;
    float dt= dot(st.xy ,float2(a,b));
    float sn= mod(dt,3.14);
    return frac(sin(sn) * c);
}

float3 Hash33( float3 x )
{
    x = float3( dot(x,float3(127.1,311.7, 74.7)),
              dot(x,float3(269.5,183.3,246.1)),
              dot(x,float3(113.5,271.9,124.6)));

    return frac(sin(x)*43758.5453123);
}

#endif