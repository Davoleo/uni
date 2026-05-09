using ParallelCascades.CommonUtilities.Editor;
using ParallelCascades.ProceduralCelestialBodyMaterials.Runtime;
using ParallelCascades.ProceduralShaders.Editor;
using UnityEditor;
using UnityEngine;

namespace ParallelCascades.ProceduralCelestialBodyMaterials.Editor
{
    public static class ProceduralStarMenuItem
    {
        [MenuItem("GameObject/Parallel Cascades/Procedural Star", false, 101)]
        private static void CreateProceduralStar(MenuCommand menuCommand)
        {
            if(!EditorAssetUtility.ChooseProjectRelativeFolderPath(out var relativeFolderPath, "Select Folder to Save Generated Procedural Star Assets"))
            {
                return;
            }
            
            var go = EditorAssetUtility.CreateGameObject(menuCommand.context as GameObject, "Procedural Star", true);

            SetupProceduralStar(go, relativeFolderPath);
            SetupStarCorona(go, relativeFolderPath);

            EditorAssetUtility.SaveAssetsAndFocusFolder(relativeFolderPath);
        }
        
        private static void SetupProceduralStar(GameObject go, string relativeFolderPath)
        {
            ProceduralStar proceduralStar = go.AddComponent<ProceduralStar>();

            Texture2D colorGradientTexture = TextureUtilities.CreateGradientTexture(relativeFolderPath, "Procedural Star Gradient");
            Material starMaterial =
                AssetGenerationUtility.CreateProceduralStarMaterial(relativeFolderPath);

            SerializedObject serializedStar = new SerializedObject(proceduralStar);
            serializedStar.FindProperty("_material").objectReferenceValue = starMaterial;
            serializedStar.FindProperty("_colorGradientTexture").objectReferenceValue = colorGradientTexture;
            serializedStar.ApplyModifiedProperties();
            
            MeshFilter meshFilter = go.AddComponent<MeshFilter>();
            meshFilter.sharedMesh = AssetGenerationUtility.GetIcoSphereMesh();
            
            MeshRenderer meshRenderer = go.AddComponent<MeshRenderer>();
            meshRenderer.sharedMaterial = starMaterial;
        }
        
        private static void SetupStarCorona(GameObject go, string relativeFolderPath)
        {
            StarCorona starCorona = go.AddComponent<StarCorona>();
            Material starCoronaMaterial = AssetGenerationUtility.CreateStarCoronaMaterial(relativeFolderPath);
            
            SerializedObject serializedStarCorona = new SerializedObject(starCorona);
            serializedStarCorona.FindProperty("_material").objectReferenceValue = starCoronaMaterial;
            serializedStarCorona.ApplyModifiedProperties();
        }
    }
}