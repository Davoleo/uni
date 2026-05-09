using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;





public class Conversation : MonoBehaviour
{

    [System.Serializable]
    public struct PhraseObjectPair
    {
        public int phraseIndex;
        public GameObject toEnable;
    }

    [SerializeField] public GameObject chatBox;
    [SerializeField] public Text UIText;
    public PhraseObjectPair[] enableObjectWithPhrase;
    public int framesPerChar = 1;

    private string[] phrases = {
        "Hello! I'll be your TA for this course in Foundations of Game Design.",
        "This first part of today's lab will give you an overview of the Unity game engine.",
        "Unity allows you to create interactive environments both in 3D and 2D.",
        "However, it is **not** a CG artist toolbox such as Blender or Maya!",
        "This means that in this course, we will **not** cover how to make:",
        "- 3D meshes",
        "- Textures",
        "- Skeletons",
        "- Animations",
        "We will combine assets, which typically come from artist pipelines...",
        "...And define their behaviour via Unity components!",
        "Unity allows extensive control over the objects in the virtual world.",
        "Some examples of what we can do in Unity:",
        "- Custom animation behaviour (such as me floating up and down!)",
        "- VFX",
        "- Shaders",
        "- Various types of physical simulations",
        "- AI behaviour to control in-game agents",
        "While we will not cover all this, the main goal of our labs will be to...",
        "...Teach you fine-grained control over Unity via simple C# scripting.",
        "Now, for our first topic: basic coding in Unity. See you soon!"
    };
    private int phraseCounter = 0;
    private int letterCounter = 0;
    private int frameCounter = 0;
    private int lastPhrase = 0;
    private bool activated = false;
    private bool firstPress = true;


    void Start()
    {
        
    }


    void Update()
    {

        if (Input.GetKeyDown(KeyCode.Space))
        {
            activated = true;
            if (firstPress)
            {
                chatBox.SetActive(true);
                firstPress = false;
            }
        }

        if (phraseCounter < phrases.Length)
        {
            string currentPhrase = phrases[phraseCounter];
            string toDisplay;

            if (activated)
            {
                if (lastPhrase != phraseCounter)
                {
                    lastPhrase = phraseCounter;
                    foreach (PhraseObjectPair pair in enableObjectWithPhrase)
                    {
                        if (pair.phraseIndex == phraseCounter)
                        {
                            pair.toEnable.SetActive(true);
                        }
                        else
                        {
                            pair.toEnable.SetActive(false);
                        }
                    }
                }

                if (frameCounter + 1 == framesPerChar)
                {
                    frameCounter = 0;
                    letterCounter += 1;
                    toDisplay = currentPhrase.Substring(0, letterCounter);
                    UIText.text = toDisplay;
                    if (letterCounter == currentPhrase.Length)
                    {
                        letterCounter = 0;
                        phraseCounter += 1;
                        activated = false;
                    }
                }
                else
                {
                    frameCounter += 1;
                }

            }
        }
        
    }
}
