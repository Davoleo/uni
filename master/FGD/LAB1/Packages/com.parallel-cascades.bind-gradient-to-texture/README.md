# Bind Gradient To Texture

## Overview

Unity does not natively support exposing gradient properties for procedural materials. This package provides a simple solution:

- Bind a MonoBehaviour Gradient property to a shader texture property through a property attribute.
- Sample the texture instead of a gradient in the shader.
- Also included: a simple MenuItem script that allows you to create a 16 pixel gradient texture.

## Usage Guide

### 1. Create a Gradient Texture
1. In the **Project View**, navigate to the folder where you want to create the gradient.
2. **Right-click** inside the folder or on the folder itself.
3. Select:  
   `Create > Parallel Cascades > Color Gradient Texture`.
4. A 16-pixel gradient texture will be created.
5. Assign this texture to your procedural material.

---

### 2. Adjust your shader (Shader Graph example)
1. Replace the Sample Gradient node with a Sample Texture 2D node.
2. Use the gradient texture created in Step 1 as the input for the Sample Texture 2D node.
3. Connect the output of the Sample Texture 2D node to the rest of your shader logic.

---

### 3. Bind Gradient to Shader Texture

#### **Create a MonoBehaviour Script**
1. Add a **Gradient** field and a **Texture** field to your script.
2. Use the `[BindGradientToTexture]` attribute to bind the gradient to the texture.

#### **Example Script**
```csharp
public class GradientBinder : MonoBehaviour
{
   [BindGradientToTexture("gradientTexture")]
   public Gradient gradient;

   public Texture2D gradientTexture;
}
```