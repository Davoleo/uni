using UnityEngine;

public class Security : MonoBehaviour
{
    public Transform player;
    public Camera mainCamera;
    private Camera camera;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        camera = GetComponent<Camera>();
    }

    // Update is called once per frame
    void Update()
    {
        transform.LookAt(player);
        
        if (Input.GetKeyDown(KeyCode.F))
        {
            camera.enabled = !camera.enabled;
            mainCamera.enabled = !mainCamera.enabled;
        }
    }
}
