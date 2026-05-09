using System.Collections;
using UnityEngine;

namespace MoonBika
{
    public class Displacement : MonoBehaviour
    {
        public float maxDisplacementDistance = 10f;
        public ParticleSystem explosionParticles;
        private MeshRenderer meshRenderer;
        private Transform targetObject;
        public bool increaseWhenClose = true; // Set to true if you want displacement to increase when close
        public float maxStablePosition = 0.5f; // Maximum stable position when not displaced

        // Start is called before the first frame update
        void Start()
        {
            meshRenderer = GetComponent<MeshRenderer>();
            targetObject = GameObject.FindGameObjectWithTag("IN").transform;
        }

        // Update is called once per frame
        void Update()
        {
            if (targetObject != null)
            {
                float distanceToTarget = Vector3.Distance(transform.position, targetObject.position);
                float normalizedDistance = Mathf.Clamp01(distanceToTarget / maxDisplacementDistance);

                float displacementAmount;

                if (increaseWhenClose)
                {
                    // Increase displacement when close
                    displacementAmount = Mathf.Lerp(maxStablePosition, 1f, normalizedDistance);
                }
                else
                {
                    // Increase displacement when far
                    displacementAmount = Mathf.Lerp(1f, maxStablePosition, normalizedDistance);
                }

                meshRenderer.material.SetFloat("_Amount", displacementAmount);

                // Check if explosionParticles is not null before playing
                if (explosionParticles != null)
                {
                    explosionParticles.Play();
                }
            }
        }
    }
}