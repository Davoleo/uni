using UnityEngine;

public class HealthHUD : MonoBehaviour
{

    private RectTransform _rectTransform;
    private float _initialWidth;
    
    void Start()
    {
        _rectTransform = GetComponent<RectTransform>();
        _initialWidth = _rectTransform.sizeDelta.x;
    }

    public void SetPercentage(float percentage)
    {
        _rectTransform.SetSizeWithCurrentAnchors(RectTransform.Axis.Horizontal, percentage * _initialWidth);
    }
}
