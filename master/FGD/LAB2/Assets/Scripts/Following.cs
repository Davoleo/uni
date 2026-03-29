using UnityEngine;

public class Following : MonoBehaviour
{

    public Transform player;
    private Transform spotLightT;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        spotLightT = transform.GetChild(2);
    }

    // Update is called once per frame
    void Update()
    {
        spotLightT.LookAt(player);
    }
}
