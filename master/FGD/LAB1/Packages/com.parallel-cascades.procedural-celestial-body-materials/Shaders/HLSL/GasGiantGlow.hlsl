#include "Packages/com.parallel-cascades.procedural-shaders/HLSL/RaySphereIntersection.hlsl"
#include "GlowEffects.hlsl"

float2 calculateGlow(
    float3 lightDirection,
    float3 rayOrigin,
    float3 viewDir,
    float distanceThroughGlow,
    float3 objectCentre,
    float objectRadius,
    float glowRadius,
    float densityFalloff
    )
{
    float stepSize = distanceThroughGlow / float(NUM_IN_SCATTER - 1);
    
    float3 inScatterPoint = rayOrigin;
    float glow = 0.;
    float viewRayOpticalDepth = 0.;
    
    for(int i = 0; i < NUM_IN_SCATTER; i++ )
    {
        viewRayOpticalDepth = opticalDepth(inScatterPoint, -viewDir, stepSize * float(i), objectCentre, objectRadius, glowRadius, densityFalloff);
        float transmittance = exp(-viewRayOpticalDepth);
        float localDensity = densityAtPoint(inScatterPoint, objectCentre, objectRadius, glowRadius, densityFalloff);
        float3 sphereNormal = normalize(inScatterPoint - objectCentre);
        float lightTransmittance = saturate(-dot(sphereNormal, lightDirection));
        glow += localDensity * transmittance * stepSize * lightTransmittance;
        inScatterPoint += viewDir * stepSize;
    }


    float originalColorTransmittance = exp(-viewRayOpticalDepth);
    return float2(originalColorTransmittance, glow);
}

void glow_float(
    float3 lightDirection,
    float4 originalColor,
    float4 coronaColor,
    float linear01Depth,
    float objectRadius,
    float effectRadius,
    float3 cameraPosition,
    float3 viewDirection,
    float farClipPlane,
    float3 objectPosition,
    float densityFalloff,
    float glowFalloff,
    float glowIntensity,
    out float4 outColor)
{
    float sceneOpaqueDistance = linear01Depth * farClipPlane;
    
    float distanceToStar = raySphere(objectPosition,objectRadius, cameraPosition, viewDirection);
    float distanceToSurface = min(sceneOpaqueDistance,distanceToStar);
    
    float2 coronaIntersect = raySphere(objectPosition,effectRadius, cameraPosition, viewDirection);
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
        float2 glowEffect = calculateGlow( lightDirection, viewRayWithOffset, viewDirection, samplingDistance, objectPosition, objectRadius, effectRadius, densityFalloff);
        originalColor = originalColor * glowEffect.x + saturate(pow(glowEffect.y, glowFalloff)) * glowIntensity * coronaColor;
    }

    outColor = originalColor;
}