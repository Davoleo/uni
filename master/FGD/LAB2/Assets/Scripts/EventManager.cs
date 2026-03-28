using UnityEngine;


public class EventManager : MonoBehaviour
{

    private string currentPhrase;

    private bool trigger = false;
    public ActivationManager activation;
    public Chat uiText;
    public LightManager lights;


    void Start()
    {
        currentPhrase = uiText.CurrentPhrase();
    }

    void Update()
    {
        bool condition = false;
        if (currentPhrase.IndexOf("Press L") >= 0)
        {
            condition = Input.GetKeyDown(KeyCode.L);
            if (condition)
            {
                activation.EnableMovement();
            }
        } else
        {
            condition = trigger;
            if (condition)
            {
                activation.DisableMovement();
            }
        }

        if (condition)
        {
            lights.Step();
            uiText.Step();

            currentPhrase = uiText.CurrentPhrase();
            if (trigger) trigger = false;
        }
    }

    public void Trigger()
    {
        trigger = true;
    }

}
