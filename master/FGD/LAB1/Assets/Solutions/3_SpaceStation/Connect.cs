using UnityEngine;

public class Connect : MonoBehaviour
{

    public float raiseAmount;
    public float rotateAmount;
    public float animationTime;

    private bool activated = false;
    private bool raised = false;
    private float elapsedTime = 0.0f;

    private Vector3 targetPos;
    private Vector3 targetRot;
    private Vector3 sourcePos;
    private Vector3 sourceRot;

    void Start()
    {
        sourcePos = transform.position;
        sourceRot = transform.eulerAngles;
    }

    void Update()
    {

        if (Input.GetKeyDown(KeyCode.B))
        {
            activated = true;
            Vector3 posOffset = new Vector3(0.0f, raised ? -raiseAmount : raiseAmount, 0.0f);
            Vector3 rotOffset = new Vector3(0.0f, raised ? -rotateAmount : rotateAmount, 0.0f);
            targetPos = sourcePos + posOffset;
            targetRot = sourceRot + rotOffset;
        }

        if (activated)
        {
            transform.position = Vector3.Lerp(sourcePos, targetPos, elapsedTime / animationTime);
            transform.eulerAngles = Vector3.Lerp(sourceRot, targetRot, elapsedTime / animationTime);

            elapsedTime += Time.deltaTime;

            if (elapsedTime >= animationTime)
            {
                activated = false;
                raised = !raised;
                elapsedTime = 0.0f;
                sourcePos = transform.position;
                sourceRot = transform.eulerAngles;
            }
        }       
    }
}
