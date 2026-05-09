using UnityEngine;
namespace MoonBika
{
    [RequireComponent(typeof(LineRenderer))]
    public class LaserStop : MonoBehaviour
    {
        [Header("Settings")]
        public LayerMask layerMask;
        public float defaultLength = 50;
        public Transform laserHitParticlePrefab; // Reference to the laser hit particle prefab

        private LineRenderer _lineRenderer;
        private RaycastHit hit;
        private Transform laserHitParticle; // Reference to the instantiated laser hit particle

        // Start is called before the first frame update
        void Start()
        {
            _lineRenderer = GetComponent<LineRenderer>();
            // Instantiate the laser hit particle at the start (inactive)
            laserHitParticle = Instantiate(laserHitParticlePrefab, Vector3.zero, Quaternion.identity);
            laserHitParticle.gameObject.SetActive(false);
        }

        // Update is called once per frame
        void Update()
        {
            ShootLaser();
        }

        void ShootLaser()
        {
            Ray ray = new Ray(transform.position, transform.forward);

            _lineRenderer.positionCount = 2;
            _lineRenderer.SetPosition(0, transform.position);

            // Does the ray intersect any objects excluding the specified layer
            if (Physics.Raycast(ray, out hit, defaultLength, layerMask))
            {
                _lineRenderer.SetPosition(1, hit.point);
                ShowLaserHitParticle(hit.point);
            }
            else
            {
                _lineRenderer.SetPosition(1, ray.origin + ray.direction * defaultLength);
                laserHitParticle.gameObject.SetActive(false);
            }
        }

        void ShowLaserHitParticle(Vector3 hitPoint)
        {
            // Activate the laser hit particle and move it to the hit point
            laserHitParticle.gameObject.SetActive(true);
            laserHitParticle.position = hitPoint;
        }
    }
}