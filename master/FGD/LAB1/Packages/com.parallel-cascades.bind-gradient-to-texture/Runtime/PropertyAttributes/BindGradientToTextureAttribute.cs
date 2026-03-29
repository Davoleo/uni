using UnityEngine;

namespace ParallelCascades.BindGradientToTexture.Runtime.PropertyAttributes
{
    public class BindGradientToTextureAttribute : PropertyAttribute
    {
        public string TexturePropertyName { get; }
        
        public float SaveDelay { get; }
        
        public bool HDR { get; }
        
        public ColorSpace ColorSpace { get; }

        public BindGradientToTextureAttribute(string texturePropertyName, bool hdr = false, ColorSpace colorSpace = ColorSpace.Gamma, float saveDelay = 0.5f)
        {
            TexturePropertyName = texturePropertyName;
            SaveDelay = saveDelay;
            HDR = hdr;
            ColorSpace = colorSpace;
        }

    }
}