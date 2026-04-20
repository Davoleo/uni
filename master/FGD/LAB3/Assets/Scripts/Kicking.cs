using System;
using UnityEngine;

public class Kicking : MonoBehaviour
{
    public GameObject playerPos;
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

    private void OnCollisionEnter(Collision other)
    {
        Debug.Log(other.transform.name);
    }

    private void FixedUpdate()
    {
        if (!playerClose)
        {
            ballCharge = 0;
            return;
        }

        if (Input.GetKey(KeyCode.Mouse0))
        {
            ballCharge += Time.fixedDeltaTime;
        } 
        else if (ballCharge > 0)
        {
            Vector3 direction = Vector3.Normalize(transform.position - playerPos.transform.position);
            ballRB.AddForce(direction * (multiplier * ballCharge));
            ballCharge = 0;
        }
    }

    // Update is called once per frame
    private void Update()
    {
        playerClose = Vector3.Distance(playerPos.transform.position, transform.position) < 3;
    }
}
