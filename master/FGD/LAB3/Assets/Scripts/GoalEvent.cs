using System;
using UnityEngine;

public class GoalEvent : MonoBehaviour
{
    private int goals;
    
    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Football"))
        {
            goals++;
            Debug.Log($"Goal! Current goals: {goals}");   
        }
    }
}
