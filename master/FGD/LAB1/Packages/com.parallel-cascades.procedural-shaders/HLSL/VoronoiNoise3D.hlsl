#include "Hash.hlsl"
// Original work (GLSL Voronoi 3D) Copyright (C) 2013 Inigo Quilez
// License: Distributed under the MIT License. See LICENSE file.
// https://www.shadertoy.com/view/ldl3Dl
// Translated to HLSL and adapted for Unity by Emil Tonev

#ifndef VORONOI_NOISE_3D_INCLUDED
#define VORONOI_NOISE_3D_INCLUDED

// returns float3(closest point distance, second closest point distance, cell id)
void voronoiNoise3d_float(float3 pos, float3 offset, float cellDensity, out float3 noise)
{
    pos = pos * cellDensity + offset;
    float3 p = floor(pos);
    float3 f = frac(pos);

    float id = 0; 
    float2 res = float2(100.0,0);

    [unroll]
    for( int k=-1; k<=1; k++ )
    {
        [unroll]
        for( int j=-1; j<=1; j++ )
        {
            [unroll]
            for( int i=-1; i<=1; i++ )
            {
                float3 b = float3(float(i),float(j),float(k));
                float3 r = float3(b) - f + Hash33(p+b);
                float d = dot(r,r);

                if( d < res.x )
                {
                    id = dot( p+b, float3(1.0,57.0,113.0 ) );
                    res = float2( d, res.x );			
                }
                else if( d < res.y )
                {
                    res.y = d;
                }
            }
        }
    }
    
    noise = float3(sqrt(res.x),sqrt(res.y),abs(id));
}

#endif