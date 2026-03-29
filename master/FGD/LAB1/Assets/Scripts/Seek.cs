using UnityEngine;

public class Seek : MonoBehaviour
{

    public GameObject target;
    public float speed;

    private Quaternion toRotation;

    void Start()
    {
        Vector3 direction = target.transform.position - transform.position;
        toRotation = Quaternion.FromToRotation(transform.forward, direction);
    }

    void Update()
    {
        transform.rotation = Quaternion.Lerp(transform.rotation, toRotation, speed * Time.deltaTime);
    }
}
