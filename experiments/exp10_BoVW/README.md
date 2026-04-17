## Experiment 10: Bag of Visual Words (BoVW)

### Goal
Convert images into vector representations using clustered feature descriptors and perform basic image classification.

---

## Pipeline

1. Extract SIFT descriptors from images
2. Collect descriptors from training set
3. Cluster descriptors using KMeans (visual vocabulary)
4. Represent each image as histogram of visual words
5. Compare histograms using L2 distance
6. Predict label using nearest neighbor

---

## Dataset Structure

```
data/bovw/
├── train/
│ ├── accordion/
│ ├── motorbike/
│ ├── dollar_bill/
│ ├── Soccer_Ball/
├── test/
├── accordion/
├── motorbike/
├── dollar_bill/
├── Soccer_Ball/
```

---

## Output

```
outputs/exp10/
├── result_0.jpg (annotated image)
├── result_0.txt (distance logs)
```

---

## Observations

- Similar images produce similar histograms
- Classification is based on nearest histogram
- Performance depends on:
  - vocabulary size (K)
  - quality of features
  - dataset variability

---

## Key Insights

- Images can be represented as vectors
- Feature matching is replaced by vector comparison
- This is a precursor to modern deep learning methods

---

## Limitations

- Ignores spatial information
- Sensitive to clustering quality
- Not robust to large variations

---

## Conclusion

BoVW transforms raw visual data into structured representations,
enabling classical machine learning approaches for image classificati
