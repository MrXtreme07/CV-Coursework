## Transformation Comparison

### Rotation (Euclidean Transform)
- Preserves shape, angles, and distances
- Only changes orientation
- No distortion introduced

### Affine Transformation
- Includes rotation, translation, scaling, and shear
- Preserves straight lines and parallelism
- Does NOT preserve angles or exact shape

### Perspective Transformation (Homography)
- Simulates camera viewpoint changes
- Preserves straight lines but NOT parallelism
- Introduces depth effects (vanishing points)

---

## Comparison Table

| Property | Rotation | Affine | Perspective |
|----------|--------|--------|------------|
| Preserves shape | ✅ | ❌ | ❌ |
| Preserves angles | ✅ | ❌ | ❌ |
| Parallel lines | ✅ | ✅ | ❌ |
| Depth effect | ❌ | ❌ | ✅ |
| Points required | 1 (center) | 3 | 4 |
| Matrix type | 2×3 | 2×3 | 3×3 |

---

## Observations

- Rotation keeps the image structure intact
- Affine introduces skew but maintains parallel lines
- Perspective transformation creates realistic viewpoint changes and depth effects