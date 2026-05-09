using UnityEngine;

public class AnimatorNotifier : MonoBehaviour
{
    private Animator animator;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.W))
        {
            animator.SetBool("forward", true);
        }
        else
        {
            animator.SetBool("forward", false);
        }
    }
}
