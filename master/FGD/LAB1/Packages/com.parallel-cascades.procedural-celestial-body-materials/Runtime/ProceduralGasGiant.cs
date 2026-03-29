using ParallelCascades.BindGradientToTexture.Runtime.PropertyAttributes;
using UnityEngine;

namespace ParallelCascades.ProceduralCelestialBodyMaterials.Runtime
{
    public class ProceduralGasGiant : MonoBehaviour
    {
        [SerializeField] private Material _material;
        [SerializeField] private Texture2D _colorGradientTexture;
        
        [Header("Shader Properties")]
        [SerializeField][BindGradientToTexture("_colorGradientTexture")] 
        private Gradient _colorGradient = new(){colorKeys =  new GradientColorKey[2]
        {
            new() {color = Color.white, time = 0},
            new() {color = Color.black, time = 1}
        }};
        
        [SerializeField][ColorUsage(false,true)] private Color _fresnelColor = Color.white;
        
        [SerializeField][Range(0.001f,1)] private float _scale = 1f;
        [SerializeField][Range(1,20)] private float _fresnelPower = 10f;
        [SerializeField][Range(0.0f,0.1f)] private float _flowSpeed = 0.001f;
        [SerializeField][Range(0.0f,0.2f)] private float _zScaling = 0.01f;
        [SerializeField][Range(0.0f,0.2f)] private float _xScaling = 0.01f;
        [SerializeField][Range(0.0f,5f)] private float _yGradientScale = 0.1f;
        [SerializeField][Range(0.0f,0.1f)] private float _yGradientStrength = 0.1f;

        [SerializeField] private Vector3 _offset;

        private static readonly int ColorGradientTexture = Shader.PropertyToID("_Color_Gradient_Texture");
        private static readonly int FresnelColor = Shader.PropertyToID("_Fresnel_Color");
        private static readonly int Scale = Shader.PropertyToID("_Scale");
        private static readonly int FresnelPower = Shader.PropertyToID("_Fresnel_Power");
        private static readonly int FlowSpeed = Shader.PropertyToID("_Flow_Speed");
        private static readonly int ZScaling = Shader.PropertyToID("_Z_Scaling");
        private static readonly int XScaling = Shader.PropertyToID("_X_Scaling");
        private static readonly int YGradientScale = Shader.PropertyToID("_Y_Gradient_Scale");
        private static readonly int YGradientStrength = Shader.PropertyToID("_Y_Gradient_Strength");
        private static readonly int Offset = Shader.PropertyToID("_Offset");

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
            _material.SetColor(FresnelColor, _fresnelColor);
            _material.SetFloat(Scale, _scale);
            _material.SetFloat(FresnelPower, _fresnelPower);
            _material.SetFloat(FlowSpeed, _flowSpeed);
            _material.SetFloat(ZScaling, _zScaling);
            _material.SetFloat(XScaling, _xScaling);
            _material.SetFloat(YGradientScale, _yGradientScale);
            _material.SetFloat(YGradientStrength, _yGradientStrength);
            _material.SetVector(Offset, _offset);
        }
        
    }
}