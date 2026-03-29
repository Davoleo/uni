using UnityEngine;
using UnityEngine.Rendering;

namespace ParallelCascades.CommonUtilities.Runtime
{
    [ExecuteInEditMode]
    internal class CheckAssignedRenderPipelineAsset : MonoBehaviour
    {
        [SerializeField] private RenderPipelineAsset _pipelineAsset;
        
        private bool _lastCorrectPipelineResults = false;
        
        private bool CorrectAssetAssigned => QualitySettings.renderPipeline == _pipelineAsset
                                               || QualitySettings.renderPipeline == null && GraphicsSettings.defaultRenderPipeline == _pipelineAsset;
        private void Awake()
        {
            CheckIfCorrectAssetIsAssigned();
        }
        
        private void Update()
        {
            CheckIfCorrectAssetIsAssigned();
        }
        
        private void CheckIfCorrectAssetIsAssigned()
        {
            if (_pipelineAsset == null)
                return;
        
            bool correctAssetAssigned = CorrectAssetAssigned;
            if (!correctAssetAssigned && _lastCorrectPipelineResults != correctAssetAssigned)
                Debug.LogWarning("This sample scene requires a specific pipeline asset to function best.\nPlease assign" +
                                 " \"" + _pipelineAsset.name + "\" to the Pipeline Asset property in Edit/Project Settings under the Quality tab.");
        
            _lastCorrectPipelineResults = correctAssetAssigned;
        }
    }
}