using UnityEngine;

public class Movement : MonoBehaviour
{

    public float moveSpeed = 0.1f;
    public float rotateSpeed = 0.1f;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.UpArrow))
        {
            transform.Translate(Vector3.forward * Time.deltaTime * moveSpeed);
        } 
        if (Input.GetKey(KeyCode.DownArrow))
        {
            transform.Translate(-Vector3.forward * Time.deltaTime * moveSpeed);
        }
        if (Input.GetKey(KeyCode.RightArrow))
        {
            transform.Translate(Vector3.right * Time.deltaTime * moveSpeed);
        }
        if (Input.GetKey(KeyCode.LeftArrow))
        {
            transform.Translate(-Vector3.right * Time.deltaTime * moveSpeed);
        }
        if (Input.GetKey(KeyCode.Q))
        {
            transform.Rotate(0.0f, -Time.deltaTime * rotateSpeed, 0.0f);
        }
        if (Input.GetKey(KeyCode.E))
        {
            transform.Rotate(0.0f, Time.deltaTime * rotateSpeed, 0.0f);
        }

        Vector3 newPos = new Vector3(Mathf.Clamp(transform.position.x, -13.0f, 13.0f), transform.position.y, Mathf.Clamp(transform.position.z, -13.0f, 13.0f));
        transform.position = newPos;
    }

}
