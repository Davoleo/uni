using UnityEngine;

namespace ParallelCascades.CommonUtilities.Runtime
{
    public static class MathfUtilities
    {
        public static float GetSharpnessInterpolant(float sharpness, float dt)
        {
            return Mathf.Clamp(1f - Mathf.Exp(-sharpness * dt),0,1);
        }
    }
}