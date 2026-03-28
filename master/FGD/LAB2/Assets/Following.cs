using System.Numerics;
using UnityEngine;
using UnityEngine.Experimental.GlobalIllumination;
using Vector3 = UnityEngine.Vector3;

public class Following : MonoBehaviour
{
    public GameObject player;

    private Transform spotLight;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        spotLight = transform.Find("Spot Light");
    }

    // Update is called once per frame
    void Update()
    {
        spotLight.LookAt(player.transform.position, Vector3.up);
    }
}
