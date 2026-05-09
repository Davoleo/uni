using System.Collections.Generic;
using UnityEngine;

namespace MoonBika
{
    public class KillParticlesOnTrigger : MonoBehaviour
    {
        [Header("Settings")]
        [SerializeField] private float onExitRemainingLifeTime = 0;

        [Header("References")]
        [SerializeField] private ParticleSystem targetParticleSystem;

        private void OnParticleTrigger()
        {
            List<ParticleSystem.Particle> particles = new List<ParticleSystem.Particle>();
            int numParticles = targetParticleSystem.GetTriggerParticles(ParticleSystemTriggerEventType.Exit, particles);
            if (numParticles <= 0)
            {
                return;
            }

            ParticleSystem.Particle[] particlesArray = new ParticleSystem.Particle[numParticles];
            particles.CopyTo(particlesArray);

            for (int i = 0; i < particlesArray.Length; i++)
            {
                if (particlesArray[i].remainingLifetime <= onExitRemainingLifeTime)
                {
                    continue;
                }
                particlesArray[i].remainingLifetime = onExitRemainingLifeTime;
            }

            List<ParticleSystem.Particle> updatedParticlesList = new List<ParticleSystem.Particle>(particlesArray);
            targetParticleSystem.SetTriggerParticles(ParticleSystemTriggerEventType.Exit, updatedParticlesList);
        }
    }
}