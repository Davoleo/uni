using UnityEngine;
using System.Collections.Generic;

public class RainSimulation : MonoBehaviour
{
    private List<GameObject> droplets = new List<GameObject>();
    private float cleanupTime;
    private float cleanupDuration;

    private bool canSimulate = false;
    private bool simulating = false;
    private float simulationTime = 0.0f;
    private float emissionTime = 0.0f;

    public Vector3 spawnPoint;
    public GameObject droplet;
    public float simulationDuration;
    public float emissionDuration = 0.1f;

    void Start()
    {
        cleanupDuration = 2.0f * simulationDuration;
    }

    void Update()
    {
        if (canSimulate && Input.GetKeyDown(KeyCode.P))
        {
            simulating = true;
        }

        if (simulating)
        {
            if (simulationTime >= simulationDuration)
            {
                simulating = false;
                simulationTime = 0.0f;
}
            if (emissionTime >= emissionDuration)
            {
                droplets.Add(Instantiate(droplet, spawnPoint + Random.insideUnitSphere * 0.1f, Quaternion.identity));
                emissionTime = 0.0f;
            }

            emissionTime += Time.deltaTime;
            simulationTime += Time.deltaTime;
        }

        if (droplets.Count > 0)
        {
            if (cleanupTime >= cleanupDuration)
            {
                foreach (GameObject g in droplets) 
                {
                    Destroy(g);
                }
                cleanupTime = 0.0f;
            }
            cleanupTime += Time.deltaTime;
        }
    }

    void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            canSimulate = true;
        }
    }

    void OnTriggerExit(Collider other)
    {
        if (other.tag == "Player")
        {
            canSimulate = false;
        }
    }
}
