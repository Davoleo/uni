using UnityEngine;
using KinematicCharacterController.Examples;


public class ActivationManager : MonoBehaviour
{

    private bool isEnabled;
    private ExampleCharacterController controller;

    void Start()
    {
        controller = GetComponent<ExampleCharacterController>();
        DisableMovement();
        isEnabled = false;
    }

    void Update()
    {
        
    }

    public void DisableMovement()
    {
        controller.MaxStableMoveSpeed = 0.0f;
        controller.JumpUpSpeed = 0.0f;
        isEnabled = false;
    }

    public void EnableMovement()
    {
        controller.MaxStableMoveSpeed = 10.0f;
        controller.JumpUpSpeed = 5.0f;
        isEnabled = true;
    }

    public void Toggle()
    {
        if (isEnabled)
        {
            DisableMovement();
        } else
        {
            EnableMovement();
        }
    }
}
