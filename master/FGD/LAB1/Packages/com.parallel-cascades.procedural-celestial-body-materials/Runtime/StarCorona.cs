using UnityEngine;

namespace ParallelCascades.ProceduralCelestialBodyMaterials.Runtime
{
    [ExecuteInEditMode]
    public class StarCorona : PostFXGlowEffect
    {        
        protected static readonly int CoronaColor = Shader.PropertyToID("_Corona_Color");
        
        [SerializeField][ColorUsage(false,true)]
        protected Color _color = Color.yellow;
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
            _material.SetColor(CoronaColor, _color);
        }
    }
}