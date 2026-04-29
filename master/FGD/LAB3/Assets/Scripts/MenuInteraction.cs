using UnityEngine;

public class MenuInteraction : MonoBehaviour
{
    private bool _gamePaused = false;

    private void SetPaused(bool paused)
    {
        _gamePaused = paused;
        Time.timeScale = _gamePaused ? 0F : 1F;
        
        for (int i = 0; i < transform.childCount; i++)
        {
            transform.GetChild(i).gameObject.SetActive(_gamePaused);
        }
    }
    
    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            SetPaused(!_gamePaused);
        }
    }

    public void Resume()
    {
        SetPaused(false);
    }
}
