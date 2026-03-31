using System;
using UnityEngine;

public class Kicking : MonoBehaviour
{
    public Transform playerPos;
    public float multiplier = 1F;

    private Rigidbody ballRB;
    private float ballCharge;
    private bool playerClose;

    private void Start()
    {
        ballCharge = 0;
        playerClose = false;
        ballRB = GetComponent<Rigidbody>();
    }

    private void FixedUpdate()
    {
        if (Input.GetKeyDown(KeyCode.Mouse0))
        {
            ballCharge += Time.fixedDeltaTime;
        }

        if (Input.GetKeyUp(KeyCode.Mouse0))
        {
            Vector3 direction = Vector3.Normalize(playerPos.position - transform.position);
            ballRB.AddForce(direction * (multiplier * ballCharge));
            ballCharge = 0;
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (Vector3.Distance(playerPos.position, transform.position) < 2)
        {
            playerClose = true;
        }
        else
        {
            playerClose = false;
        }
    }
}
