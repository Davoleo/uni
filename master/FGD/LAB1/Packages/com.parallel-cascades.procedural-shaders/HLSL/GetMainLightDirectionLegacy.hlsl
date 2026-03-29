#ifndef MAIN_LIGHT_LEGACY_INCLUDED
#define MAIN_LIGHT_LEGACY_INCLUDED

void GetMainLightDirection_float(out float3 Direction)
{
#if defined(SHADERGRAPH_PREVIEW)
    Direction = float3(0.5, 0.5, 0);
#elif defined(BUILTIN_TARGET_API)
    Direction = _WorldSpaceLightPos0.xyz;
#else
    // URP fallback
    Direction = GetMainLight().direction;
#endif
}

#endif
