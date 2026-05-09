using UnityEngine;
using UnityEngine.UI;


public class Chat : MonoBehaviour
{

    private Text display;
    private uint idx = 0;
    private bool nextPhrase = false;
    public string[] phrases;

    void Start()
    {
        display = GetComponent<Text>();
        display.text = phrases[idx];
    }

    void Update()
    {
        if (nextPhrase)
        {
            if (idx <= phrases.Length - 1)
            {
                display.text = phrases[idx];
                nextPhrase = false;
            }
        }
    }

    public void Step()
    {
        nextPhrase = true;
        idx++;
    }

    public string CurrentPhrase()
    {
        return idx <= phrases.Length - 1 ? phrases[idx] : "";
    }

}
