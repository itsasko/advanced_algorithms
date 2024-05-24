import matplotlib.pyplot as plt
import numpy as np

array_sizes = []
z_search = []
rabin_karp = []



with open('../run_tests/data.txt', 'r') as file:
	for count, line in enumerate(file.readlines()):
            if(count > 0):
                array_sizes.append(float(line.split(" ")[0]))
                z_search.append(float(line.split(" ")[1]))
                rabin_karp.append(float(line.split(" ")[2]))




x = np.array(array_sizes)

y1 = np.array(z_search)
y2 = np.array(rabin_karp)


plt.figure(figsize=(10, 8))

plt.plot(x, y1, color = 'c', label = 'z search')
plt.plot(x, y2, color = 'b', label = 'rabin-karp search')


plt.xlabel("size of string")
plt.ylabel("time taken")

plt.legend()

plt.show()