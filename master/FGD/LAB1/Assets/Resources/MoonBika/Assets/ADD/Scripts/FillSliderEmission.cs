using UnityEngine;
using UnityEngine.UI;

namespace MoonBika
{
    [ExecuteInEditMode] // Run in Unity Editor
    public class FillSliderEmission : MonoBehaviour
    {
        [SerializeField] private float fillAmount = -2f; // Fill Amount in Shader Graph
        private MeshRenderer meshRenderer;
        private Material material; // Material to store
        [SerializeField] private float fillSpeed = 1f; // Speed of filling

        public Slider fillSlider; // Reference to the UI Slider

        void Start()
        {
            meshRenderer = GetComponent<MeshRenderer>();

            // Use sharedMaterial to avoid instantiating the material during edit mode
            material = meshRenderer.sharedMaterial;

            if (fillSlider == null)
            {
                Debug.LogError("FillSlider reference not set on " + name);
            }

            if (material == null)
            {
                Debug.LogError("Material not found on " + name);
            }
        }

        void Update()
        {
            if (material == null)
            {
                return; // Avoid processing if material is null
            }

            // Use the slider value to control fill amount
            fillAmount = Mathf.Lerp(-2f, 1f, fillSlider.value);

            // Incrementally update the fill value over time
            float targetFill = Mathf.Clamp(fillAmount, -2f, 1f);
            fillAmount = Mathf.Lerp(fillAmount, targetFill, Time.deltaTime * fillSpeed);

            material.SetFloat("_Fill", fillAmount); // Reference of Fill Property in Emission shader Graph
        }
    }
}