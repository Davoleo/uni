using ParallelCascades.BindGradientToTexture.Runtime.PropertyAttributes;
using UnityEngine;

namespace ParallelCascades.ProceduralCelestialBodyMaterials.Runtime
{
    public class ProceduralAsteroidRing : MonoBehaviour
    {
        private bool _asteroidRing;
        
        [SerializeField] private Material _material;
        [SerializeField] private Texture2D _colorGradientTexture;
        
        [Header("Shader Properties")] 
        [BindGradientToTexture("_colorGradientTexture")][SerializeField]
        private Gradient _colorGradient = new(){colorKeys =  new GradientColorKey[2]
        {
            new() {color = Color.white, time = 0},
            new() {color = Color.black, time = 1}
        }};
        
        [SerializeField] private float _innerRadius = 0.1f;
        [SerializeField] private float _outerRadius = 0.3f;
        [SerializeField] private float _fadeStrength = 2.23f;
        [SerializeField] private float _flowSpeed = 0.01f;
        
        private static readonly int ColorGradientTexture = Shader.PropertyToID("_Color_Gradient_Texture");
        private static readonly int InnerRadius = Shader.PropertyToID("_Inner_Radius");
        private static readonly int OuterRadius = Shader.PropertyToID("_Outer_Radius");
        private static readonly int FadeStrength = Shader.PropertyToID("_Fade_Strength");
        private static readonly int FlowSpeed = Shader.PropertyToID("_Flow_Speed");
        
        private void OnValidate()
        {
            UpdateMaterial();
        }

        private void UpdateMaterial()
        {
            if(_material == null || _colorGradientTexture == null)
            {
                return;
            }
            
            _material.SetTexture(ColorGradientTexture, _colorGradientTexture);
            _material.SetFloat(InnerRadius, _innerRadius);
            _material.SetFloat(OuterRadius, _outerRadius);
            _material.SetFloat(FadeStrength, _fadeStrength);
            _material.SetFloat(FlowSpeed, _flowSpeed);
        }
    }
}