#ifndef RAY_SPHERE_INTERSECTION_HLSL
#define RAY_SPHERE_INTERSECTION_HLSL

#define MAX_FLOAT 3.402823466e+38

// Original work (Ray-Sphere Intersection) Copyright (C) 2020 Sebastian Lague.
// License: Distributed under the MIT License. See LICENSE file.
// https://github.com/SebLague/Solar-System/blob/Development/Assets/Scripts/Script%20Utilities/MathUtility.cs
// Adapted to hlsl by Emil Tonev.
float2 raySphere(float3 sphereCentre, float sphereRadius, float3 rayOrigin, float3 normalizedRayDir)
{
    float3 offset = rayOrigin - sphereCentre;
    float a = 1; 
    float b = 2 * dot(offset, normalizedRayDir);
    float c = dot (offset, offset) - sphereRadius * sphereRadius;
    float d = b * b - 4 * a * c;

    // Number of intersections: 0 when d < 0; 1 when d = 0; 2 when d > 0
    if (d > 0) {
        float s = sqrt(d);
        float dstToSphereNear = max(0, (-b - s) / (2 * a));
        float dstToSphereFar = (-b + s) / (2 * a);

        // Ignore intersections that occur behind the ray
        if (dstToSphereFar >= 0) {
            return float2(dstToSphereNear, dstToSphereFar - dstToSphereNear);
        }
    }
    
    // Ray did not intersect sphere
    return float2(MAX_FLOAT, 0);
}

#endif