using UnityEngine;

public class AutoRotate : MonoBehaviour
{

    public float speed;

   

    void Update()
    {
        transform.RotateAround(transform.position, transform.forward, speed * Time.deltaTime);
    }
}
