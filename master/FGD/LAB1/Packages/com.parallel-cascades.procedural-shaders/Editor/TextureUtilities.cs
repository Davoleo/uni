using System.IO;
using UnityEditor;
using UnityEngine;
using UnityEngine.Experimental.Rendering;

namespace ParallelCascades.ProceduralShaders.Editor
{
    public static class TextureUtilities
    {
        public static Texture2D SetTextureFromGradient(Gradient gradient, Texture2D texture)
        {
            int resolution = texture.width;
            for (int i = 0; i < resolution; i++)
            {
                float t = i / (float)(resolution - 1);
                Color color = gradient.Evaluate(t);
                texture.SetPixel(i, 0, color);
            }

            texture.Apply();
            return texture;
        }
    
        public static void SaveTextureAsset(Texture2D texture)
        {
            string assetPath = AssetDatabase.GetAssetPath(texture);
            if (!string.IsNullOrEmpty(assetPath))
            {
                byte[] textureData;
            
                if(GraphicsFormatUtility.IsHDRFormat(texture.graphicsFormat))
                {
                    textureData = texture.EncodeToEXR();                
                }
                else
                {
                    textureData = texture.EncodeToPNG();
                }
            
                System.IO.File.WriteAllBytes(assetPath, textureData);
                AssetDatabase.ImportAsset(assetPath);
            }
            else
            {
                Debug.LogError("The texture is not associated with an asset in the project. Please save it as an asset first.");
            }
        }
        
        public static Texture2D CreateGradientTexture(string projectRelativeFolderPath, string name)
        {
            Texture2D colorGradientTexture = new Texture2D(16, 1);
        
            for(int x = 0; x < colorGradientTexture.width; x++)
            {
                float t = x / (float)(colorGradientTexture.width - 1);
                Color color = Color.HSVToRGB(t, 1, 1);
                colorGradientTexture.SetPixel(x, 0, color);
            }
        
            colorGradientTexture.Apply();
        
            string texturePath = $"{projectRelativeFolderPath}/{name}.png";
            texturePath = AssetDatabase.GenerateUniqueAssetPath(texturePath);
        
            File.WriteAllBytes(texturePath, colorGradientTexture.EncodeToPNG());
        
            AssetDatabase.ImportAsset(texturePath);
        
            Texture2D importedTexture = AssetDatabase.LoadAssetAtPath<Texture2D>(texturePath);
            TextureImporter textureImporter = AssetImporter.GetAtPath(texturePath) as TextureImporter;
            if(textureImporter != null)
            {
                textureImporter.isReadable = true;
                textureImporter.textureCompression = TextureImporterCompression.Uncompressed;
                textureImporter.mipmapEnabled = false;
                textureImporter.wrapMode = TextureWrapMode.Clamp;
                AssetDatabase.ImportAsset(texturePath, ImportAssetOptions.ForceUpdate);
            }

            return importedTexture;
        }
    }
}
