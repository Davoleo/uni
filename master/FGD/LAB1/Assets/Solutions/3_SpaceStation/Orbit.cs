using UnityEngine;

public class Orbit : MonoBehaviour
{

    public float orbitSpeed;
    public Vector3 orbitOffset;
    public float xRotation;
    public float zRotation;

    private Vector3 rotationAxis;

    void Start()
    {
        transform.localPosition = orbitOffset;

        rotationAxis = Quaternion.Euler(xRotation, 0.0f, zRotation) * Vector3.up;
    }


    void Update()
    {
        transform.RotateAround(transform.parent.position, rotationAxis, Time.deltaTime * orbitSpeed);
    }
}
