import matplotlib.pyplot as plt
import numpy as np

size = []
list = []
set = []
trie = []
hash = []

with open('../data/build.txt', 'r') as file:
    for count, line in enumerate(file.readlines()):
        if count > 0:
            data = line.split()
            size.append(data[0])
            list.append(float(data[1]))
            set.append(float(data[2]))
            trie.append(float(data[3]))
            hash.append(float(data[4]))

x = np.array(size)
y1 = np.array(list)
y2 = np.array(set)
y3 = np.array(trie)
y4 = np.array(hash)

plt.figure(figsize=(10, 8))
plt.plot(x, y1, color='c', label='List')
plt.plot(x, y2, color='b', label='Set')
plt.plot(x, y3, color='g', label='Trie')
plt.plot(x, y4, color='y', label='Hash')

plt.xlabel("Size")
plt.ylabel("Search Time")
plt.legend()

plt.xticks(ticks=np.arange(0, len(x), step=max(1, len(x)//10)), labels=x[::max(1, len(x)//10)])

plt.xticks(rotation=45)

plt.tight_layout() 
plt.show()
