using UnityEngine;
using UnityEngine.UI;

namespace MoonBika
{
    [ExecuteInEditMode] // Run in Unity Editor
    public class DissolveController : MonoBehaviour
    {
        [SerializeField] private float dissolveAmount = -2f; // Dissolve Amount in Shader Graph
        private Renderer rend;
        private Material material; // Material to store
        [SerializeField] private float dissolveSpeed = 1f; // Speed of dissolving

        public Slider dissolveSlider; // Reference to the UI Slider

        void Start()
        {
            rend = GetComponent<Renderer>();

            // Use sharedMaterial to avoid instantiating the material during edit mode
            material = rend.sharedMaterial;

            if (dissolveSlider == null)
            {
                Debug.LogError("DissolveSlider reference not set on " + name);
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

            // Use the slider value to control dissolve amount
            dissolveAmount = Mathf.Lerp(-2f, 1f, dissolveSlider.value);

            // Incrementally update the dissolve value over time
            float targetDissolve = Mathf.Clamp(dissolveAmount, -2f, 1f);
            dissolveAmount = Mathf.Lerp(dissolveAmount, targetDissolve, Time.deltaTime * dissolveSpeed);

            material.SetFloat("_DissolveAmount", dissolveAmount); // Reference of Dissolve Property in Shader Graph
        }
    }
}