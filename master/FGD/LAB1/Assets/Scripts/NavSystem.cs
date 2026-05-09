using UnityEngine;

public class NavSystem : MonoBehaviour
{
    public float stabilizerDamping;
    public float linearThrust;
    public float angularThrust;
    private Rigidbody rb;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    void Update()
    {
        //Vector3 offset = new Vector3(-1.0f, 0.0f, 0.0f);
        //Debug.DrawRay(transform.position + offset, transform.forward);//rb.linearVelocity);

        bool isLinearAccelerating = false;
        bool isAngularAccelerating = false;

        if (Input.GetKey(KeyCode.Space))
        {
            isLinearAccelerating = true;
            rb.AddForce(transform.up * linearThrust, ForceMode.Acceleration);
        }
        if (Input.GetKey(KeyCode.LeftControl))
        {
            isLinearAccelerating = true;
            rb.AddForce(-transform.up * linearThrust, ForceMode.Acceleration);
        }
        if (Input.GetKey(KeyCode.W))
        {
            isLinearAccelerating = true;
            rb.AddForce(transform.forward * linearThrust, ForceMode.Acceleration);
        }
        if (Input.GetKey(KeyCode.S))
        {
            isLinearAccelerating = true;
            rb.AddForce(-transform.forward * linearThrust, ForceMode.Acceleration);
        }


        if (Input.GetKey(KeyCode.E))
        {
            isAngularAccelerating = true;
            rb.AddTorque(-transform.forward * angularThrust, ForceMode.Acceleration);
        }
        if (Input.GetKey(KeyCode.Q))
        {
            isAngularAccelerating = true;
            rb.AddTorque(transform.forward * angularThrust, ForceMode.Acceleration);
        }
        if (Input.GetKey(KeyCode.UpArrow))
        {
            isAngularAccelerating = true;
            rb.AddTorque(-transform.right * angularThrust, ForceMode.Acceleration);
        }
        if (Input.GetKey(KeyCode.DownArrow))
        {
            isAngularAccelerating = true;
            rb.AddTorque(transform.right * angularThrust, ForceMode.Acceleration);
        }
        if (Input.GetKey(KeyCode.A))
        {
            isAngularAccelerating = true;
            rb.AddTorque(-transform.up * angularThrust, ForceMode.Acceleration);
        }
        if (Input.GetKey(KeyCode.D))
        {
            isAngularAccelerating = true;
            rb.AddTorque(transform.up * angularThrust, ForceMode.Acceleration);
        }

        if (!isLinearAccelerating)
        {
            rb.AddForce(-rb.linearVelocity * stabilizerDamping, ForceMode.Acceleration);
        }

        if (!isAngularAccelerating)
        {
            rb.AddTorque(-rb.angularVelocity * stabilizerDamping, ForceMode.Acceleration);
        }
    }
}
