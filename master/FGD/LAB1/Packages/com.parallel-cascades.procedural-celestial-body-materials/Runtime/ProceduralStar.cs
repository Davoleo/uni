using ParallelCascades.BindGradientToTexture.Runtime.PropertyAttributes;
using UnityEngine;

namespace ParallelCascades.ProceduralCelestialBodyMaterials.Runtime
{
    public class ProceduralStar : MonoBehaviour
    {
        [SerializeField] private Material _material;
        [SerializeField] private Texture2D _colorGradientTexture;
        
        [Header("Shader Properties")]
        [BindGradientToTexture("_colorGradientTexture", true)][SerializeField]
        private Gradient _colorGradient = new(){colorKeys =  new GradientColorKey[2]
        {
            new() {color = Color.yellow, time = 0},
            new() {color = Color.red, time = 1}
        }};
        [SerializeField][ColorUsage(false,true)] private Color _colorR = Color.yellow;
        [SerializeField][ColorUsage(false,true)] private Color _colorQ = Color.red;
        [SerializeField][ColorUsage(false,true)] private Color _fresnelColor = Color.red;
        
        [SerializeField][Range(0.1f,10)] private float _scale = 1f;
        [SerializeField][Range(0.1f,10)] private float _warpAmount = 1f;
        [SerializeField][Range(1,20)] private float _fresnelPower = 1f;
        [SerializeField][Range(0.001f,1)] private float _flowSpeed = 0.1f;
        
        private static readonly int ColorGradientTexture = Shader.PropertyToID("_Color_Gradient_Texture");
        private static readonly int ColorR = Shader.PropertyToID("_Color_R");
        private static readonly int ColorQ = Shader.PropertyToID("_Color_Q");
        private static readonly int FresnelColor = Shader.PropertyToID("_Fresnel_Color");
        private static readonly int Scale = Shader.PropertyToID("_Scale");
        private static readonly int WarpAmount = Shader.PropertyToID("_Warp_Amount");
        private static readonly int FresnelPower = Shader.PropertyToID("_Fresnel_Power");
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
            _material.SetColor(ColorR, _colorR);
            _material.SetColor(ColorQ, _colorQ);
            _material.SetColor(FresnelColor, _fresnelColor);
            _material.SetFloat(Scale, _scale);
            _material.SetFloat(WarpAmount, _warpAmount);
            _material.SetFloat(FresnelPower, _fresnelPower);
            _material.SetFloat(FlowSpeed, _flowSpeed);
        }


    }
}