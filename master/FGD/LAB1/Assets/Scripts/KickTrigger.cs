using UnityEngine;

public class KickTrigger : MonoBehaviour
{
    public KickIt kickRef;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.K))
        {
            kickRef.kick = true;
        }
        
    }
}
