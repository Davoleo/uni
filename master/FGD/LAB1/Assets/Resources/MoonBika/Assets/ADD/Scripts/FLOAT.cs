using UnityEngine;

namespace MoonBika
{
    public class FloatingInAir : MonoBehaviour
    {
        public float amplitude = 1.0f;     // The maximum distance the object will move up and down.
        public float frequency = 1.0f;     // The speed of the floating motion.

        private Vector3 initialPosition;   // The initial position of the object.

        private void Start()
        {
            // Store the initial position of the object.
            initialPosition = transform.position;
        }

        private void Update()
        {
            // Calculate the floating motion based on the amplitude and frequency.
            float yPosition = initialPosition.y + amplitude * Mathf.Sin(Time.time * frequency);

            // Update the object's position to create the floating effect.
            transform.position = new Vector3(transform.position.x, yPosition, transform.position.z);
        }
    }
}