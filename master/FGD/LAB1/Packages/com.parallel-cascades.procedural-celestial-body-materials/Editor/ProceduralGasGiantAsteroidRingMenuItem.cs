using ParallelCascades.CommonUtilities.Editor;
using ParallelCascades.ProceduralCelestialBodyMaterials.Runtime;
using ParallelCascades.ProceduralShaders.Editor;
using UnityEditor;
using UnityEngine;

namespace ParallelCascades.ProceduralCelestialBodyMaterials.Editor
{
    public static class ProceduralGasGiantAsteroidRingMenuItem
    {
        [MenuItem("GameObject/Parallel Cascades/Procedural Gas Giant", false, 100)]
        private static void CreateProceduralGasGiant(MenuCommand menuCommand)
        {
            if(!EditorAssetUtility.ChooseProjectRelativeFolderPath(out var relativeFolderPath, "Select Folder to Save Gas Giant Material and Texture"))
            {
                return;
            }
            
            var go = EditorAssetUtility.CreateGameObject(menuCommand.context as GameObject, "Procedural Gas Giant", true);
            
            SetupProceduralGasGiant(go, relativeFolderPath);
            
            EditorAssetUtility.SaveAssetsAndFocusFolder(relativeFolderPath);
        }
        
        [MenuItem("GameObject/Parallel Cascades/Procedural Gas Giant with Asteroid Ring", false, 100)]
        private static void CreateProceduralGasGiantWithAsteroidRing(MenuCommand menuCommand)
        {
            if(!EditorAssetUtility.ChooseProjectRelativeFolderPath(out var relativeFolderPath, "Select Folder to Save Materials and Texture"))
            {
                return;
            }
            
            var go = EditorAssetUtility.CreateGameObject(menuCommand.context as GameObject, "Procedural Gas Giant", true);
            
            SetupProceduralGasGiant(go, relativeFolderPath);
            
            GameObject asteroidRingGO = EditorAssetUtility.CreateGameObject(go, "Asteroid Ring");
            SetupProceduralAsteroidRing(asteroidRingGO, relativeFolderPath);
            
            EditorAssetUtility.SaveAssetsAndFocusFolder(relativeFolderPath);
        }
        
        [MenuItem("GameObject/Parallel Cascades/Asteroid Ring", false, 100)]
        private static void CreateProceduralAsteroidRing(MenuCommand menuCommand)
        {
            if(!EditorAssetUtility.ChooseProjectRelativeFolderPath(out var relativeFolderPath, "Select Folder to Save Asteroid Ring Material and Texture"))
            {
                return;
            }
            
            var go = EditorAssetUtility.CreateGameObject(menuCommand.context as GameObject, "Asteroid Ring");
            
            SetupProceduralAsteroidRing(go, relativeFolderPath);
            
            EditorAssetUtility.SaveAssetsAndFocusFolder(relativeFolderPath);
        }
        
        private static void SetupProceduralGasGiant(GameObject go, string relativeFolderPath)
        {

            Material gasGiantMaterial =
                AssetGenerationUtility.CreateProceduralGasGiantMaterial(relativeFolderPath);
            
            MeshFilter meshFilter = go.AddComponent<MeshFilter>();
            meshFilter.sharedMesh = AssetGenerationUtility.GetIcoSphereMesh();
            
            MeshRenderer meshRenderer = go.AddComponent<MeshRenderer>();
            meshRenderer.sharedMaterial = gasGiantMaterial;
            
            Texture2D colorGradientTexture = TextureUtilities.CreateGradientTexture(relativeFolderPath, "Gas Giant Gradient");
            
            ProceduralGasGiant proceduralGasGiant = go.AddComponent<ProceduralGasGiant>();
            SerializedObject serializedGasGiant = new SerializedObject(proceduralGasGiant);
            serializedGasGiant.FindProperty("_material").objectReferenceValue = gasGiantMaterial;
            serializedGasGiant.FindProperty("_colorGradientTexture").objectReferenceValue = colorGradientTexture;
            serializedGasGiant.ApplyModifiedProperties();
            
            GasGiantGlow gasGiantGlow = go.AddComponent<GasGiantGlow>();
            SerializedObject serializedGasGiantGlow = new SerializedObject(gasGiantGlow);
            Material gasGiantGlowMaterial = AssetGenerationUtility.CreateGasGiantGlowMaterial(relativeFolderPath);
            serializedGasGiantGlow.FindProperty("_material").objectReferenceValue = gasGiantGlowMaterial;
            serializedGasGiantGlow.ApplyModifiedProperties();
            
        }

        private static void SetupProceduralAsteroidRing(GameObject go, string relativeFolderPath)
        {
            ProceduralAsteroidRing proceduralAsteroidRing = go.AddComponent<ProceduralAsteroidRing>();
            
            Material asteroidRingMaterial = AssetGenerationUtility.CreateAsteroidRingMaterial(relativeFolderPath);
            
            MeshFilter meshFilter = go.AddComponent<MeshFilter>();
            meshFilter.sharedMesh = AssetGenerationUtility.GetDoubleSidedPlaneMesh();
            
            MeshRenderer meshRenderer = go.AddComponent<MeshRenderer>();
            meshRenderer.shadowCastingMode = UnityEngine.Rendering.ShadowCastingMode.Off;
            meshRenderer.sharedMaterial = asteroidRingMaterial;
            
            Texture2D colorGradientTexture = TextureUtilities.CreateGradientTexture(relativeFolderPath, "Asteroid Ring Gradient");
            SerializedObject serializedAsteroidRing = new SerializedObject(proceduralAsteroidRing);
            serializedAsteroidRing.FindProperty("_material").objectReferenceValue = asteroidRingMaterial;
            serializedAsteroidRing.FindProperty("_colorGradientTexture").objectReferenceValue = colorGradientTexture;
            serializedAsteroidRing.ApplyModifiedProperties();
        }
        
    }
}