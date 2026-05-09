using UnityEngine;

public class Breathing : MonoBehaviour
{


    [SerializeField] float moveDuration = 1.0f;
    [SerializeField] float maximumHeight;

    private float currentTime = 0.0f;
    private bool breathingIn = true;
    private Vector3 breathIn;
    private Vector3 breathOut;

    void Start()
    {
        breathIn = transform.localPosition;
        breathIn.y += maximumHeight;
        breathOut = transform.localPosition;
    }


    void Update()
    {

        Vector3 targetPosition = breathingIn ? breathIn : breathOut;
        Vector3 startPosition = breathingIn ? breathOut : breathIn;

        currentTime += Time.deltaTime;
        float lerpFactor = currentTime / moveDuration;

        transform.localPosition = Vector3.Lerp(startPosition, targetPosition, lerpFactor);

        if (lerpFactor >= 1.0f)
        {
            currentTime = 0.0f;
            breathingIn = !breathingIn;
        }

    }
}
