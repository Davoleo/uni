using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.RenderGraphModule;
using UnityEngine.Rendering.RenderGraphModule.Util;
using UnityEngine.Rendering.Universal;

namespace ParallelCascades.ProceduralCelestialBodyMaterials.PostProcessing
{
    public class GlowPostFXPass : ScriptableRenderPass
    {
        const string _passName = "GlowPostFXPass";

        Material _blitMaterial;

        public void Setup(Material material)
        {
            _blitMaterial = material;

            // The pass will read the current color texture. That needs to be an intermediate texture. It's not supported to use the BackBuffer as input texture. 
            // By setting this property, URP will automatically create an intermediate texture. 
            requiresIntermediateTexture = true;
        }

        public override void RecordRenderGraph(RenderGraph renderGraph, ContextContainer frameData)
        {
            // UniversalResourceData contains all the texture handles used by the renderer, including the active color and depth textures
            // The active color and depth textures are the main color and depth buffers that the camera renders into
            var resourceData = frameData.Get<UniversalResourceData>();

            // This should never happen since we set m_Pass.requiresIntermediateTexture = true;
            // Unless you set the render event to AfterRendering, where we only have the BackBuffer. 
            if (resourceData.isActiveTargetBackBuffer)
            {
                Debug.LogWarning(
                    $"Skipping render pass. GlowPostFXPass requires an intermediate ColorTexture, we can't use the BackBuffer as a texture input.");
                return;
            }
            
            var source = resourceData.activeColorTexture;

            var destinationDesc = renderGraph.GetTextureDesc(source);
            destinationDesc.name = $"CameraColor-{_passName}";
            destinationDesc.clearBuffer = false;

            TextureHandle destination = renderGraph.CreateTexture(destinationDesc);

            RenderGraphUtils.BlitMaterialParameters para = new(source, destination, _blitMaterial, 0);
            renderGraph.AddBlitPass(para, passName: _passName + " " + _blitMaterial.name);

            //FrameData allows to get and set internal pipeline buffers. Here we update the CameraColorBuffer to the texture that we just wrote to in this pass. 
            //Because RenderGraph manages the pipeline resources and dependencies, following up passes will correctly use the right color buffer.
            //This optimization has some caveats. You have to be careful when the color buffer is persistent across frames and between different cameras, such as in camera stacking.
            //In those cases you need to make sure your texture is an RTHandle and that you properly manage the lifecycle of it.
            resourceData.cameraColor = destination;
        }
    }
}