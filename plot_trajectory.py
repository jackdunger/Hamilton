import matplotlib.pyplot as plt
import numpy as np

d = np.loadtxt("unreflected.dat")
plt.plot(d[:, 0], d[:, 1], label = "No Boundaries")

d = np.loadtxt("reflected.dat")
plt.plot(d[:, 0], d[:, 1], label = "Boundary at $q = 0$", ls = "--")

plt.legend()
plt.xlabel("q")
plt.ylabel("p")
plt.xlim([-10, 10])
plt.ylim([-10, 10])

plt.savefig("trajectory.pdf")

plt.clf()
plt.xlabel("x")
plt.ylabel("y")

d = np.loadtxt("onebounce.dat")
plt.plot(d[:, 0], d[:, 1])
plt.savefig("onebounce.pdf")
