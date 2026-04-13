## Experiment 4: Corner Detection (Harris vs Shi-Tomasi)

### Goal
Understand how corner (interest point) detection works and why corners are better features than edges for matching and tracking.

---

## What is a Corner?

A corner is a point where intensity changes significantly in **both directions (x and y)**.

- Flat region → no change  
- Edge → change in one direction  
- Corner → change in two directions  

Corners are more distinctive and stable compared to edges.

---

## Harris Corner Detector

### Idea
Harris computes a **corner response function** using image gradients.

It uses the **structure tensor**:

\[
M =
\begin{bmatrix}
I_x^2 & I_x I_y \\
I_x I_y & I_y^2
\end{bmatrix}
\]

The response:

\[
R = det(M) - k(trace(M))^2
\]

### Characteristics
- Produces a **response map**
- Requires manual thresholding
- Sensitive to noise and parameter tuning

### Observations
- Detects many candidate points
- Can include noisy or redundant detections
- Quality depends heavily on threshold selection

---

## Shi-Tomasi Corner Detector

### Idea
Instead of Harris response, Shi-Tomasi uses:

\[
R = min(\lambda_1, \lambda_2)
\]

where \( \lambda_1, \lambda_2 \) are eigenvalues of the structure tensor.

### Characteristics
- Directly selects **strongest corners**
- Built-in filtering (quality + distance)
- More stable and practical

### Observations
- Produces cleaner and more meaningful points
- Automatically avoids clustered detections
- Still requires tuning (max corners, distance)

---

## Key Differences

| Feature | Harris | Shi-Tomasi |
|--------|--------|------------|
| Output | Response map | Selected keypoints |
| Filtering | Manual threshold | Built-in |
| Noise sensitivity | Higher | Lower |
| Stability | Lower | Higher |
| Practical use | Less common | Widely used |

---

## Important Insights

- Harris detects **all possible corner responses**, but requires tuning
- Shi-Tomasi performs **selection + filtering automatically**
- Parameter choice (threshold, distance) strongly affects results
- Preprocessing (e.g., Gaussian blur) improves stability

---

## Conclusion

- Harris is useful for understanding the theory of corner detection  
- Shi-Tomasi is more suitable for real-world applications  

This experiment introduces the concept of **interest points**, which is fundamental for feature-based methods like ORB, SIFT, and SLAM.
