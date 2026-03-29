using UnityEngine;

public class SimulationListener : MonoBehaviour
{

    public float animationTime;
    public float moveSpeed;

    private bool translating = false;
    private bool activatedOnce = false;

    private float elapsedTime = 0.0f;

    // Update is called once per frame
    void Update()
    {
        if (!activatedOnce)
        {

            if (Input.GetKeyDown(KeyCode.P))
            {
                translating = true;
            }

            if (translating)
            {
                transform.Translate(-transform.forward * Time.deltaTime * moveSpeed);
                elapsedTime += Time.deltaTime;
                if (elapsedTime >= animationTime)
                {
                    activatedOnce = true;
                }
            }
        }

        
    }
}
