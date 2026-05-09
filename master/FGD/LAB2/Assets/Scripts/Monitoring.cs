using UnityEngine;

public class Monitoring : MonoBehaviour
{
    private const float MonitoringDist = 15;
    
    private Camera securityCamera;
    private float prevDistance = float.PositiveInfinity;
    
    public Camera mainCamera;
    public Transform player;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        securityCamera = GetComponent<Camera>();
        securityCamera.enabled = false;
    }

    // Update is called once per frame
    void Update()
    {
        transform.LookAt(player);

        var distance = Vector3.Distance(player.position, transform.position);
        
        //if (Input.GetKeyDown(KeyCode.F))
        if ((distance < MonitoringDist && prevDistance >= MonitoringDist) || (distance >= MonitoringDist && prevDistance < MonitoringDist))
        {
            securityCamera.enabled = !securityCamera.enabled;
            mainCamera.enabled = !mainCamera.enabled;
        }

        prevDistance = distance;
    }
}
