using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace MoonBika
{
    [RequireComponent(typeof(LineRenderer))]
    public class LASER : MonoBehaviour
    {
        [Header("Settings")]
        public LayerMask layerMask;
        public float defaultLength = 50;
        public int numOfReflections = 2;

        private LineRenderer _lineRenderer;
        private Camera _myCam;
        private RaycastHit hit;
        private Ray ray;
        private Vector3 direction;

        // Start is called before the first frame update
        void Start()
        {
            _lineRenderer = GetComponent<LineRenderer>();
            _myCam = Camera.main;
        }

        // Update is called once per frame
        void Update()
        {
            ReflectLaser();
        }

        void ReflectLaser()
        {
            ray = new Ray(transform.position, transform.forward);
            _lineRenderer.positionCount = 1;
            _lineRenderer.SetPosition(0, transform.position);

            float remainLength = defaultLength;

            for (int i = 0; i < numOfReflections; i++)
            {
                // Does the ray intersect any objects excluding the player layer
                if (Physics.Raycast(ray.origin, ray.direction, out hit, remainLength, layerMask))
                {
                    _lineRenderer.positionCount += 1;
                    _lineRenderer.SetPosition(_lineRenderer.positionCount - 1, hit.point);
                    remainLength -= Vector3.Distance(ray.origin, hit.point);
                    ray = new Ray(hit.point, Vector3.Reflect(ray.direction, hit.normal));
                }
                else
                {
                    _lineRenderer.positionCount += 1;
                    _lineRenderer.SetPosition(_lineRenderer.positionCount - 1, ray.origin + (ray.direction * remainLength));
                }
            }
        }

        void NormalLaser()
        {
            _lineRenderer.SetPosition(0, transform.position);

            // Does the ray intersect any objects excluding the player layer
            if (Physics.Raycast(transform.position, transform.forward, out hit, defaultLength, layerMask))
            {
                _lineRenderer.SetPosition(1, hit.point);
            }
        }
    }
}