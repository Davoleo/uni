using UnityEngine;

public class KickIt : MonoBehaviour
{

    public bool kick = false;

    void Update()
    {
        if (kick)
        {
            Rigidbody rb = GetComponent<Rigidbody>();
            rb.AddForce(Vector3.Normalize(transform.forward + transform.right) * 400.0f);
            kick = false;
        }
    }
}
