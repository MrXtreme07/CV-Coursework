## Experiment 7: Homography and Image Alignment

### Goal
Compute geometric transformation between two images using feature matches.

---

## Homography

A homography maps points from one plane to another using a 3×3 matrix.

---

## Steps

1. Detect ORB keypoints
2. Match descriptors
3. Extract corresponding points
4. Compute homography using RANSAC
5. Warp image

---

## Observations

- Alignment works well for planar scenes
- RANSAC removes incorrect matches
- Good matches are critical for accurate transformation

---

## Key Insight

Feature matching enables geometric understanding of images.

This is the basis of:
- Panorama stitching
- Augmented reality
- SLAM