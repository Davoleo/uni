void AsteroidRing_float(
float2 uv,
float innerRadius,
float outerRadius,
float fadeStrength,
float tau,
float inverseTau,
float time,
float flowSpeed,
UnityTexture2D gradient,
UnitySamplerState gradientSampler,
UnityTexture2D mainTex,
UnitySamplerState mainTexSampler,
out float4 ring)
{
    float2 uv1 = (uv - 0.5) * 2.0;
    float2 uv2 = uv1 * 2.0;

    // Two radii for two samples for different detail levels
    float r1 = length(uv1);
    float r2 = length(uv2);

    float ringRadius = outerRadius - innerRadius;

    r1 = saturate((r1 - innerRadius) / ringRadius);
    r2 = (r2 - innerRadius) / ringRadius;
    
    // Circular angle rotating with time
    float azimuthalAngle = atan2(uv2.y, uv2.x) * inverseTau;
    azimuthalAngle += time * flowSpeed;

    // First texture sample for radial circles
    float2 sampleUV1 = float2(azimuthalAngle, r2);
    float2 height = mainTex.Sample(mainTexSampler, sampleUV1).gb;

    // Blend samples to introduce non-linear variations in the height
    height.r *= height.g * 0.333 + 0.666;
    height.g = 0.0;
    
    // Second texture sample for finer blending with details
    float2 sampleUV2 = float2(0.0, r1);
    height += mainTex.Sample(mainTexSampler, sampleUV2).rg;
    
    height.r *= 0.5;
    
    // Sample from gradient texture using accumulated height data
    float4 tex = gradient.Sample(gradientSampler, height);
    
    // Apply alpha and radial fade
    tex *= saturate(1.0 - abs(r1 - 0.55) * fadeStrength);
    
    ring = tex * step(innerRadius, length(uv1)) * step(length(uv1), outerRadius); 
}