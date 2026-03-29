using ParallelCascades.CommonUtilities.Editor;
using UnityEngine;

namespace ParallelCascades.ProceduralCelestialBodyMaterials.Editor
{
    public static class AssetGenerationUtility
    {
        public static Mesh GetIcoSphereMesh()
        {
            return Resources.Load<Mesh>("Meshes/icosphere_high");
        }

        public static Mesh GetDoubleSidedPlaneMesh()
        {
            return Resources.Load<Mesh>("Meshes/double_sided_plane");
        }

        public static Material CreateProceduralStarMaterial(string projectRelativeFolderPath)
        {
            return EditorAssetUtility.CreateMaterial(projectRelativeFolderPath, "Parallel Cascades/Procedural Star", "Star Material");
        }
        
        public static Material CreateProceduralGasGiantMaterial(string projectRelativeFolderPath)
        {
            return EditorAssetUtility.CreateMaterial(projectRelativeFolderPath, "Parallel Cascades/Procedural Gas Giant", "Gas Giant Material");
        }
        
        public static Material CreateGasGiantGlowMaterial(string projectRelativeFolderPath)
        {
            return EditorAssetUtility.CreateMaterial(projectRelativeFolderPath, "Parallel Cascades/Procedural Gas Giant Glow", "Gas Giant Glow Material");
        }
        
        public static Material CreateStarCoronaMaterial(string projectRelativeFolderPath)
        {
            return EditorAssetUtility.CreateMaterial(projectRelativeFolderPath, "Parallel Cascades/Procedural Star Corona", "Star Corona Material");
        }
        
        public static Material CreateAsteroidRingMaterial(string projectRelativeFolderPath)
        {
            return EditorAssetUtility.CreateMaterial(projectRelativeFolderPath, "Parallel Cascades/Procedural Asteroid Ring", "Asteroid Ring Material");
        }
    }
}