using System;
using UnityEngine;

public class EnvironmentalHazard : MonoBehaviour
{
    public HealthManager playerHealth;
    
    private void OnTriggerEnter(Collider other)
    {
        playerHealth.TakeDamage(1);
    }
}