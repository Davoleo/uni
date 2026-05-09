using UnityEngine;
using System.Collections.Generic;

public class Defense : MonoBehaviour
{

    public List<GameObject> enemies;
    public GameObject mainCamera;


    void Update()
    {
        Vector3 camPos = mainCamera.transform.position;
        
        foreach (GameObject enemy in enemies)
        {
            if (Vector3.Distance(camPos, enemy.transform.position) < 2F)
            {
                Destroy(enemy);
            }
        }
    }
}
