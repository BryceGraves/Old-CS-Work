import numpy as np
import matplotlib.pyplot as plt

sample = np.random.normal(25, 5, size=10)
h = plt.hist(sample)
plt.show(h)
