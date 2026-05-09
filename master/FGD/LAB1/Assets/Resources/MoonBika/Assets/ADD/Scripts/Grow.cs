using UnityEngine;

namespace MoonBika
{
    public class Grow : MonoBehaviour
    {
        public float minSize = 1f;
        public float maxSize = 10f;
        public float growthTime = 5f;
        public float smoothTime = 0.3f;
        public KeyCode growKey = KeyCode.Space; // Change this to the desired key

        private float currentSize;
        private float sizeVelocity;

        void Start()
        {
            currentSize = minSize;
            transform.localScale = new Vector3(currentSize, currentSize, currentSize);
        }

        void Update()
        {
            // Check if the specified key is pressed
            if (Input.GetKey(growKey))
            {
                // Call the function to make the sphere grow
                GrowSphere();
            }
        }

        void GrowSphere()
        {
            // Calculate the target size based on the current time and growth time
            float targetSize = Mathf.Lerp(minSize, maxSize, Mathf.PingPong(Time.time / growthTime, 1f));

            // Smoothly adjust the current size towards the target size
            currentSize = Mathf.SmoothDamp(currentSize, targetSize, ref sizeVelocity, smoothTime);

            // Set the new scale of the sphere
            transform.localScale = new Vector3(currentSize, currentSize, currentSize);
        }
    }
}