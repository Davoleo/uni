#define NUM_IN_SCATTER 20
#define NUM_OUT_SCATTER 10

float densityAtPoint(float3 densitySamplePoint, float3 planetCentre, float planetRadius, float atmosphereRadius, float densityFalloff)
{
    float heightAboveSurface = length(densitySamplePoint - planetCentre) - planetRadius;
    float height01 = heightAboveSurface / (atmosphereRadius - planetRadius);
    
    float localDensity = exp(-height01 * densityFalloff) * (1 - height01); // last term clamps function result to 0 at density 1
    return localDensity;
}

float opticalDepth(
    float3 rayOrigin,
    float3 rayDir,
    float rayLength,
    float3 planetCentre,
    float planetRadius,
    float atmosphereRadius,
    float densityFalloff)
{
    float3 densitySamplePoint = rayOrigin;
    float stepSize = rayLength / (float(NUM_OUT_SCATTER) - 1.);
    float opticalDepth = 0.;

    for (int i = 0; i < NUM_OUT_SCATTER; i ++) {
        float localDensity = densityAtPoint(densitySamplePoint, planetCentre, planetRadius, atmosphereRadius, densityFalloff);
        opticalDepth += localDensity * stepSize;
        densitySamplePoint += rayDir * stepSize;
    }
    return opticalDepth;
}