using UnityEngine;

public class LaunchRigidbodies : MonoBehaviour
{

    public float force;

    private void OnTriggerEnter(Collider other)
    {
        Rigidbody rb = other.GetComponent<Rigidbody>();
        if (rb != null)
        {
            rb.AddForce(transform.up * force, ForceMode.Impulse);
        }
    }
}
