using System;
using UnityEngine;

public class HealthManager : MonoBehaviour
{
    public HealthHUD healthHUD;
    
    private int _health;
    public const int MaxHealth = 10;

    public int Health
    {
        get => _health;
        private set
        {
            _health = value;
            healthHUD.SetPercentage( (float) _health / MaxHealth);
        }
    }

    private void Start()
    {
        Health = MaxHealth;
    }

    public void TakeDamage(int damage)
    {
        Health = Math.Max(Health - damage, 0);
    }
    
    public void Heal(int heal)
    {
        Health = Math.Min(Health + heal, MaxHealth);
    }
}