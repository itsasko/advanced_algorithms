



import matplotlib.pyplot as plt
import numpy as np

array_sizes = []
kmp = []
rabin_karp = []


with open('../../part1/part_b/data2.txt', 'r') as file:
	for count, line in enumerate(file.readlines()):
            if(count > 0):
                array_sizes.append(float(line.split(" ")[0]))
                kmp.append(float(line.split(" ")[1]))
                rabin_karp.append(float(line.split(" ")[2]))
                

x = np.array(array_sizes)

y1 = np.array(kmp)
y2 = np.array(rabin_karp)



plt.figure(figsize=(10, 8))

plt.plot(x, y1, color = 'orange', label = 'kmp')
plt.plot(x, y2, color = 'b', label = 'rabin-karp search')



plt.xlabel("size of string")
plt.ylabel("time taken")

plt.legend()

plt.show()