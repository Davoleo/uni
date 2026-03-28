using UnityEngine;
using System;
using System.Collections.Generic;

[Serializable]
public struct IndexGameObject
{
    public int idx;
    public GameObject obj;
}

public class LightManager : MonoBehaviour
{

    private bool nextLights = false;
    private int idx = 0;
    private int maxStep = 0;
    public List<IndexGameObject> lights;


    void Start()
    {
        foreach (IndexGameObject light in lights)
        {
            if (light.idx > maxStep) maxStep = light.idx;
        }
    }

    void Update()
    {

        if (nextLights)
        {
            if (idx <= maxStep)
            {
                TurnOnCurrentLights();
                nextLights = false;
                idx++;
            }
        }
    }

    void TurnOnCurrentLights()
    {
        foreach (IndexGameObject light in lights) {
            if (light.idx == idx) light.obj.SetActive(true);
        }
    }

    public void Step()
    {
        nextLights = true;
    }
}
