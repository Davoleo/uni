using UnityEngine;

public class CharacterDetector : MonoBehaviour
{

    private void OnTriggerEnter(Collider other)
    {
        transform.parent.GetComponent<EventManager>().Trigger();
        gameObject.SetActive(false);
    }

}
