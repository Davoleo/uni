using ParallelCascades.ProceduralCelestialBodyMaterials.PostProcessing;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.Universal;
using UnityEngine.Serialization;

namespace ParallelCascades.ProceduralCelestialBodyMaterials.Runtime
{
    public abstract class PostFXGlowEffect : MonoBehaviour
    {
        private static readonly int ObjectPosition = Shader.PropertyToID("_Object_Position");
        protected static readonly int EffectRadius = Shader.PropertyToID("_Effect_Radius");
        protected static readonly int ObjectRadius = Shader.PropertyToID("_Object_Radius");
        protected static readonly int DensityFalloff = Shader.PropertyToID("_Density_Falloff");
        
        [SerializeField] [Min(0.001f)] protected float _meshRadius = 0.5f;
        [FormerlySerializedAs("_coronaScale")] [SerializeField] [Range(0.1f,10)] protected float _effectScale = 3f;
        [SerializeField] protected float _densityFalloff = 20f;
        [SerializeField] protected Material _material;
        [SerializeField] private RenderPassEvent _renderPassEvent = RenderPassEvent.BeforeRenderingPostProcessing;
        
        private GlowPostFXPass _glowPostFXPass;
        protected float _objectScale;
        private bool _initialized;

        private void OnValidate()
        {
            UpdateMaterial();
        }

        private void OnDestroy()
        {
            CleanUpPostFXGlow();
        }

        private void OnDisable()
        {
            CleanUpPostFXGlow();
        }

        private void Update()
        {
            if (!_initialized)
            {
                InitializePostFXGlow();
                _initialized = true;
            }
            
            SetBodyScale();
            UpdateMaterial();
        }

        private void SetBodyScale()
        {
            _objectScale = transform.localScale.x;
        }

        protected abstract void UpdateMaterial();

        private void InitializePostFXGlow()
        {
            if (_glowPostFXPass == null)
            {
                _glowPostFXPass = new GlowPostFXPass
                {
                    renderPassEvent = _renderPassEvent
                };
            }

            if (_material == null)
            {
                Debug.Log("Assign a suitable post fx glow material to the PostFXGlowSettings asset");
                _material = new Material(Shader.Find("Hidden/InternalErrorShader"));
            }

            _glowPostFXPass.Setup(_material);
            
            RenderPipelineManager.beginCameraRendering += PostFXGlowOnBeginCamera;
        }

        private void CleanUpPostFXGlow()
        {
            RenderPipelineManager.beginCameraRendering -= PostFXGlowOnBeginCamera;
            _initialized = false;
        }

        private void PostFXGlowOnBeginCamera(ScriptableRenderContext context, Camera cam)
        {
            
            if (cam.cameraType is not (CameraType.Game or CameraType.SceneView))
            {
                return;
            }
            
            UpdateEffectPosition(transform.position);
            cam.GetUniversalAdditionalCameraData().scriptableRenderer.EnqueuePass(_glowPostFXPass);
        }

        private void UpdateEffectPosition(Vector3 position)
        {
            if(_material == null)
            {
                return;
            }
            
            _material.SetVector(ObjectPosition, position);
        }
    }
}