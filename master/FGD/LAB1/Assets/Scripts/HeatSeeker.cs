using System;
using UnityEngine;

public class HeatSeeker : MonoBehaviour
{

    public GameObject target;
    public float moveSpeed = 1.0f;
    public float rotateSpeed = 1.0f;
    public GameObject enemyDefenseSystem;

    private Rigidbody rb;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        var defense = enemyDefenseSystem.GetComponent<Defense>();
        defense.enemies.Add(gameObject);
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 targetPos = target.transform.position;
        targetPos.y = 0.0f;
        rb.linearVelocity = moveSpeed * (targetPos - transform.position);
        Quaternion targetRot = Quaternion.LookRotation(target.transform.position - transform.position);
        transform.rotation = Quaternion.Lerp(transform.rotation, targetRot, rotateSpeed * Time.deltaTime);
    }

    private void OnDestroy()
    {
        var defense = enemyDefenseSystem.GetComponent<Defense>();
        defense.enemies.Remove(gameObject);
        Debug.Log("Ouch");
    }
}
