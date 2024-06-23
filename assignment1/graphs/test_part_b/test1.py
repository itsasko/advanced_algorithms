



import matplotlib.pyplot as plt
import numpy as np

array_sizes = []
binary_sunday = []
gusfield = []


with open('../../part1/part_b/data.txt', 'r') as file:
	for count, line in enumerate(file.readlines()):
            if(count > 0):
                array_sizes.append(float(line.split(" ")[0]))
                binary_sunday.append(float(line.split(" ")[1]))
                gusfield.append(float(line.split(" ")[2]))
                

x = np.array(array_sizes)

y1 = np.array(binary_sunday)
y2 = np.array(gusfield)



plt.figure(figsize=(10, 8))

plt.plot(x, y1, color = 'orange', label = 'binary sunday')
plt.plot(x, y2, color = 'b', label = 'gusfield')



plt.xlabel("size of string")
plt.ylabel("time taken")

plt.legend()

plt.show()