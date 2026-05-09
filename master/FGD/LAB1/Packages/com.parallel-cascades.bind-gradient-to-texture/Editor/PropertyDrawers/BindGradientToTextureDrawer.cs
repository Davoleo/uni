using ParallelCascades.BindGradientToTexture.Runtime.PropertyAttributes;
using ParallelCascades.ProceduralShaders.Editor;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;

namespace ParallelCascades.BindGradientToTexture.Editor.PropertyDrawers
{
    [CustomPropertyDrawer(typeof(BindGradientToTextureAttribute))]
    public class BindGradientToTextureDrawer : PropertyDrawer
    {
        private static string _invalidTypeMessage = "Use [BindGradientToTexture] with gradient.";

        private string _texturePropertyName;
        private float _saveDelay;
        
        private float _lastChangeTime;
        
        private Gradient _gradient;
        private Texture2D _texture;
        
        public override VisualElement CreatePropertyGUI(SerializedProperty property)
        {
            var container = new VisualElement();

            if(property.propertyType != SerializedPropertyType.Gradient)
                return new Label(_invalidTypeMessage);

            BindGradientToTextureAttribute attribute = (BindGradientToTextureAttribute)this.attribute;
            _texturePropertyName = attribute.TexturePropertyName;
            _saveDelay = attribute.SaveDelay;
            
            var gradientField = new GradientField(property.displayName);
            gradientField.hdr = attribute.HDR;
            gradientField.colorSpace = attribute.ColorSpace;
            gradientField.bindingPath = property.propertyPath;
            gradientField.AddToClassList(BaseField<Gradient>.alignedFieldUssClassName);

            gradientField.RegisterValueChangedCallback(evt =>
            {
                Undo.RecordObject(property.serializedObject.targetObject, "Update Gradient");
                _gradient = evt.newValue;
                CaptureTexture(property);
                TextureUtilities.SetTextureFromGradient(_gradient, _texture);
                ScheduleSave();
            });
            
            container.Add(gradientField);

            return container;
        }

        private void CaptureTexture(SerializedProperty property)
        {
            var textureProperty = property.serializedObject.FindProperty(_texturePropertyName);
            if (textureProperty == null) return;
                    
            _texture = textureProperty.objectReferenceValue as Texture2D;
        }

        private void ScheduleSave()
        {
            _lastChangeTime = Time.realtimeSinceStartup;
            EditorApplication.update -= SaveTextureAsset;
            EditorApplication.update += SaveTextureAsset;
        }

        private void SaveTextureAsset()
        {
            if (Time.realtimeSinceStartup - _lastChangeTime > _saveDelay)
            {
                if (_texture == null) return;
                    
                Undo.RecordObject(_texture, "Update Texture from Gradient");
                TextureUtilities.SetTextureFromGradient(_gradient, _texture);
                Undo.RecordObject(_texture, "Save Texture Asset");
                TextureUtilities.SaveTextureAsset(_texture);
                EditorApplication.update -= SaveTextureAsset;
            }
        }
    }
}