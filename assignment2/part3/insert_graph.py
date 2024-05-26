import matplotlib.pyplot as plt
import numpy as np

load = []

chaining = []
probing = []
hashing = []



with open('insert_dt.txt', 'r') as file:
	for count, line in enumerate(file.readlines()):
            if(count > 0):
                load.append(round(float(line.split(" ")[0])/2048, 2))
                chaining.append(float(line.split(" ")[1]))
                probing.append(float(line.split(" ")[2]))
                hashing.append(float(line.split(" ")[3]))



x = np.array(load)

y1 = np.array(chaining)
y2 = np.array(probing)
y3 = np.array(hashing)


plt.figure(figsize=(10, 8))

plt.plot(x, y1, color = 'c', label = 'separate chaining')
plt.plot(x, y2, color = 'b', label = 'linear probing')
plt.plot(x, y3, color = 'g', label = 'double hashing')


plt.xlabel("load percent")
plt.ylabel("insert time")

plt.legend()

plt.show()