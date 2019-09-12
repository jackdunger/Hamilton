import numpy as np
import matplotlib.pyplot as plt

d = np.loadtxt("samples.dat")
plt.hist(d, bins = np.linspace(-5, 5, 101), normed = True, label = "Samples")

xs = np.linspace(-5, 5, 100)
ys = 2 * np.exp(-xs**2/2)/np.sqrt(2*np.pi)

plt.xlabel("q")
plt.ylabel("Probability")
plt.savefig("samples_test.pdf")
