using UnityEngine;

namespace ParallelCascades.ProceduralCelestialBodyMaterials.Runtime
{
    [ExecuteInEditMode]
    public class GasGiantGlow : PostFXGlowEffect
    {        
        protected static readonly int GlowColor = Shader.PropertyToID("_Glow_Color");

        [SerializeField][ColorUsage(false,true)]
        protected Color _color = Color.white;
        
        protected override void UpdateMaterial()
        {
            if (_material == null)
            {
                return;
            }
            
            var meshAdjustedScale = _objectScale * _meshRadius;
            var meshAdjustedEffectScale = _effectScale * _meshRadius;
            
            _material.SetFloat(EffectRadius, meshAdjustedScale * (1+meshAdjustedEffectScale));
            _material.SetFloat(ObjectRadius, meshAdjustedScale);            
            _material.SetFloat(DensityFalloff, _densityFalloff);
            _material.SetColor(GlowColor, _color);
        }
    }
}