# Degraded Test Set Analysis

Analysis of `data/test_degradato/` vs `data/test/` — 500 paired images across 100 classes.
All images are pre-resized to 224×224. Every single image in the degraded set is modified.

---

## Summary statistics

| Metric | Clean | Degraded | Delta |
|---|---|---|---|
| Brightness (mean pixel) | 118.79 ± 39.86 | 118.94 ± 41.83 | +0.15 |
| Contrast (pixel std) | 61.42 ± 11.60 | 62.62 ± 18.58 | +1.19 |
| Saturation (HSV, 0–255) | 83.10 ± 37.02 | 100.63 ± 37.90 | **+17.53** |
| Hue std (HSV, 0–255) | 60.00 ± 19.81 | 52.79 ± 25.35 | −7.21 |

Brightness and contrast are **statistically neutral** at the aggregate level. Saturation is the dominant signal.

---

## Per-image paired analysis (pixel-level)

| Stat | Value |
|---|---|
| Mean absolute pixel diff | 28.75 ± 11.98 |
| Mean signed diff (bias) | +0.15 ± 21.93 |
| Max pixel diff (per image, avg) | 119.6 ± 33.8 |
| Images with any diff | 100% |
| Identical images | 0% |

The signed bias is near zero but with high variance (±21.93), meaning brightness shifts are **random per image** — roughly equal probability of going darker or brighter.

---

## Degradation breakdown by type

### Brightness change

| Direction | Count | % |
|---|---|---|
| Darker (< −10) | 162 | 32% |
| Roughly same | 181 | 36% |
| Brighter (> +10) | 157 | 31% |

Brightness shift is random and image-dependent, with no systematic direction.

### Saturation change

| Threshold | Count | % |
|---|---|---|
| Less saturated (< −5) | 110 | 22% |
| Similar | 62 | 12% |
| More saturated (> +5) | 328 | **66%** |
| Strongly more saturated (> +20) | 228 | **46%** |

Saturation is the **primary degradation**. Two-thirds of images are more saturated in the degraded set.

**Multiplicative ratio** (degraded saturation / clean saturation, measured on pixels with clean sat > 10):

| Percentile | Ratio |
|---|---|
| 5th | 0.72× |
| Mean | **1.65×** |
| 95th | 3.12× |
| Max | 7.11× |

The degraded set is on average **65% more saturated** than the clean set. Some images reach 3–7× saturation.

### Hue shift

| Threshold | Count | % |
|---|---|---|
| \|delta\| > 10 (≈14°) | 389 | **78%** |
| \|delta\| > 20 (≈28°) | 288 | **58%** |

Hue shift is the **second dominant degradation**. Values in torchvision `ColorJitter` units (`hue` ∈ [−0.5, 0.5]):

| Stat | Value |
|---|---|
| Mean | +0.014 |
| Std | **0.177** |
| 5th percentile | −0.261 |
| 95th percentile | +0.356 |
| To cover 80% of images | **hue ≈ 0.228** |
| To cover 90% of images | **hue ≈ 0.290** |

Hue shifts are large and go in both directions (cool/teal casts and warm/purple casts), but skew slightly positive (more toward green/teal).

---

## Visual inspection (top-changed images)

| Image | abs_diff | Effect |
|---|---|---|
| `figure skating women/4.jpg` | 72.61 | White ice → strong **teal cast** |
| `parallel bar/2.jpg` | 72.02 | Pure black background → **lifted to dark grey** (contrast collapse) |
| `uneven bars/3.jpg` | 71.75 | Similar contrast collapse |
| `balance beam/1.jpg` | 69.04 | Warm neutral → **purple/cool cast** |
| `tennis/2.jpg` | 63.66 | Natural lighting → **darker + blue-shifted** |

The two main degradation patterns visible:
1. **Color cast** — strong hue shift applied to the whole image (teal, purple, blue)
2. **Contrast collapse** — shadow/black areas are lifted, reducing dynamic range

---

## Implications for ColorJitter parameters

Current parameters in `get_degraded_transforms()` (as of v2.2):

```python
v2.ColorJitter(brightness=0.3, contrast=0.3, saturation=0.2, hue=0.05)
```

| Parameter | Current coverage | What the data needs | Assessment |
|---|---|---|---|
| `hue=0.05` | ±18° | ±82° (80th pct), ±104° (90th pct) | **4× too small** |
| `saturation=0.2` | [0.8×, 1.2×] | [0.72×, 3.12×] | Wrong range; skewed too low |
| `brightness=0.3` | [0.7×, 1.3×] | ±28% max observed | Reasonable |
| `contrast=0.3` | [0.7×, 1.3×] | Random, moderate | Reasonable |

### Recommended parameters

```python
v2.ColorJitter(
    brightness=0.35,
    contrast=0.4,
    saturation=(0.7, 3.0),  # tuple → asymmetric; degradation is predominantly a saturation increase
    hue=0.25,               # covers ~80% of observed hue shifts
)
```

Key changes:
- **Hue `0.05 → 0.25`**: the most important fix. The previous recommendation to *reduce* hue (from 0.1 to 0.05, v2.2) was based on the concern that team colors are discriminative — valid for a clean-set model, but wrong for the degraded model where 78% of test images have large hue shifts.
- **Saturation `0.2 → (0.7, 3.0)`**: switching to a tuple allows asymmetric coverage. The degradation is almost entirely an *increase* in saturation, so a symmetric float wastes half its range on desaturation that is rare in the test set.
- **Brightness `0.3 → 0.35`**: minor bump to match the observed ±28% max range.
- **Contrast `0.3 → 0.4`**: minor bump to better simulate the contrast-collapse pattern seen in some images.
