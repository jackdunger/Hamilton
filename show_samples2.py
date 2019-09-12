import numpy as np
import matplotlib.pyplot as plt

d = np.loadtxt("samples.dat")
plt.hist2d(d[:, 0], d[:, 1], bins = 70)

plt.legend()
plt.xlabel("q")
plt.ylabel("Probability")
plt.savefig("samples_test2.pdf")
