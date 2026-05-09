using UnityEngine;
using System.Collections.Generic;

public class ShootingSimulation : MonoBehaviour
{
    private List<GameObject> bullets = new List<GameObject>();
    private float cleanupTime;
    private float cleanupDuration;

    private bool canSimulate = false;
    private bool simulating = false;
    private int shotsFired = 0;
    private float emissionTime = 0.0f;

    public Vector3 shotDirection;
    public float shotSpeed;
    public Vector3 spawnPoint;
    public GameObject bullet;
    public int numShots;
    public float emissionDuration = 0.1f;

    void Start()
    {
        cleanupDuration = 2.0f * (emissionDuration * numShots);
    }

    void Update()
    {
        if (canSimulate && Input.GetKeyDown(KeyCode.P))
        {
            simulating = true;
        }

        if (simulating)
        {
            if (shotsFired >= numShots)
            {
                simulating = false;
                shotsFired = 0;
            }
            if (emissionTime >= emissionDuration)
            {
                bullets.Insert(0, Instantiate(bullet, spawnPoint, Quaternion.Euler(0.0f, 0.0f, 90.0f)));
                bullets[0].GetComponent<Rigidbody>().AddForce(shotDirection * shotSpeed, ForceMode.Impulse);
                emissionTime = 0.0f;
                shotsFired += 1;
            }

            emissionTime += Time.deltaTime;
        }

        if (bullets.Count > 0)
        {
            if (cleanupTime >= cleanupDuration)
            {
                foreach (GameObject g in bullets)
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
