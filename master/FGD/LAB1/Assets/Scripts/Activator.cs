using UnityEngine;

public class Activator : MonoBehaviour
{

    public GameObject evilCapsule;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.A))
        {
            for (int i = 0; i < 5; i++)
            {
                GameObject capsule = Instantiate(evilCapsule);
                capsule.SetActive(true);
                Vector3 oldPos = capsule.transform.position;
                capsule.transform.position = new Vector3(oldPos.x + 2*i, oldPos.y, oldPos.z);
            }
        }
    }
}
