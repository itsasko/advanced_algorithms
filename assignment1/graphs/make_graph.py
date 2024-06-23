import matplotlib.pyplot as plt
import numpy as np

array_sizes = []
z_search = []
rabin_karp = []
fsm = []
brute_force = []
sunday = []
kmp = []

with open('../run_tests/data.txt', 'r') as file:
	for count, line in enumerate(file.readlines()):
            if(count > 0):
                array_sizes.append(float(line.split(" ")[0]))
                z_search.append(float(line.split(" ")[1]))
                rabin_karp.append(float(line.split(" ")[2]))
                fsm.append(float(line.split(" ")[3]))
                brute_force.append(float(line.split(" ")[4]))
                sunday.append(float(line.split(" ")[5]))
                kmp.append(float(line.split(" ")[6]))



x = np.array(array_sizes)

y1 = np.array(z_search)
y2 = np.array(rabin_karp)
y3 = np.array(fsm)
y4 = np.array(brute_force)
y5 = np.array(sunday)
y6 = np.array(kmp)


plt.figure(figsize=(10, 8))

plt.plot(x, y1, color = 'c', label = 'z search')
plt.plot(x, y2, color = 'b', label = 'rabin-karp search')
plt.plot(x, y3, color = 'g', label = 'fsm')
plt.plot(x, y4, color = 'r', label = 'brute force')
plt.plot(x, y5, color = 'pink', label = 'sunday')
plt.plot(x, y6, color = 'orange', label = 'kmp')


plt.xlabel("size of string")
plt.ylabel("time taken")

plt.legend()

plt.show()