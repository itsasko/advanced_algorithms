import matplotlib.pyplot as plt
import numpy as np

array_sizes = []
rabin_karp = []
sunday = []


with open('../../part1/part_b/data3.txt', 'r') as file:
	for count, line in enumerate(file.readlines()):
            if(count > 0):
                array_sizes.append(float(line.split(" ")[0]))
                rabin_karp.append(float(line.split(" ")[1]))
                sunday.append(float(line.split(" ")[2]))
        

x = np.array(array_sizes)

y1 = np.array(rabin_karp)
y2 = np.array(sunday)



plt.figure(figsize=(10, 8))

plt.plot(x, y1, color = 'b', label = 'rabin-karp search')
plt.plot(x, y2, color = 'pink', label = 'sunday')



plt.xlabel("size of string")
plt.ylabel("time taken")

plt.legend()

plt.show()