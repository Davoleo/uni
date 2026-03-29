#include "Packages/com.parallel-cascades.procedural-shaders/HLSL/RaySphereIntersection.hlsl"
#include "GlowEffects.hlsl"

float2 calculateCorona(
    float3 rayOrigin,
    float3 viewDir,
    float distanceThroughCorona,
    float3 starCentre,
    float starRadius,
    float coronaRadius,
    float densityFalloff
    )
{
    float stepSize = distanceThroughCorona / float(NUM_IN_SCATTER - 1);
    
    float3 inScatterPoint = rayOrigin;
    float corona = 0.;
    float viewRayOpticalDepth = 0.;
    
    for(int i = 0; i < NUM_IN_SCATTER; i++ )
    {
        viewRayOpticalDepth = opticalDepth(inScatterPoint, -viewDir, stepSize * float(i), starCentre, starRadius, coronaRadius, densityFalloff);
        float transmittance = exp(-viewRayOpticalDepth);
        float localDensity = densityAtPoint(inScatterPoint, starCentre, starRadius, coronaRadius, densityFalloff);
        corona += localDensity * transmittance * stepSize;
        inScatterPoint += viewDir * stepSize;
    }

    float originalColorTransmittance = exp(-viewRayOpticalDepth);
    return float2(originalColorTransmittance, corona);
}

void corona_float(
    float4 originalColor,
    float4 coronaColor,
    float linear01Depth,
    float starRadius,
    float coronaRadius,
    float3 cameraPosition,
    float3 viewDirection,
    float farClipPlane,
    float3 starPosition,
    float densityFalloff,
    float glowFalloff,
    float glowIntensity,
    out float4 outColor)
{
    float sceneOpaqueDistance = linear01Depth * farClipPlane;
    
    float distanceToStar = raySphere(starPosition,starRadius, cameraPosition, viewDirection);
    float distanceToSurface = min(sceneOpaqueDistance,distanceToStar);
    
    float2 coronaIntersect = raySphere(starPosition,coronaRadius, cameraPosition, viewDirection);
    float distanceToCorona = coronaIntersect.x;
    
    float dstThroughCorona = min(coronaIntersect.y, distanceToSurface - distanceToCorona);

    if(dstThroughCorona > 0 && distanceToCorona <= sceneOpaqueDistance)
    {
        // This step is required to avoid a glaring visual bug at the edge of the corona sphere
        const float epsilon = 0.0001;
        float3 viewRayWithOffset = cameraPosition + viewDirection * (distanceToCorona + epsilon);

        // Need to clamp since samplingDistance can be negative if dstThrough == 0, i.e.
        // there is an object at the corona boundary and distanceToSurface == dstToCorona
        float samplingDistance = max(dstThroughCorona - epsilon * 2, 0.0f); 
        float2 corona = calculateCorona( viewRayWithOffset, viewDirection, samplingDistance, starPosition, starRadius, coronaRadius, densityFalloff);
        originalColor = originalColor * corona.x + saturate(pow(corona.y, glowFalloff)) * glowIntensity * coronaColor;
    }

    outColor = originalColor;
}