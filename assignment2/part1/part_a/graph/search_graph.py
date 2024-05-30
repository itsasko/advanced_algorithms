import matplotlib.pyplot as plt
import numpy as np

size = []

list = []
set = []
trie = []
hash = []



with open('../data/search.txt', 'r') as file:
	for count, line in enumerate(file.readlines()):
            if(count > 0):
                size.append(line.split(" ")[0])
                list.append(float(line.split(" ")[1]))
                set.append(float(line.split(" ")[2]))
                trie.append(float(line.split(" ")[3]))
                hash.append(float(line.split(" ")[0]))



x = np.array(size)

y1 = np.array(list)
y2 = np.array(set)
y3 = np.array(trie)
y4 = np.array(hash)

plt.figure(figsize=(10, 8))

plt.plot(x, y1, color = 'c', label = 'List')
plt.plot(x, y2, color = 'b', label = 'Set')
plt.plot(x, y3, color = 'g', label = 'Trie')
plt.plot(x, y4, color = 'black', label = 'Hash')


plt.xlabel("size")
plt.ylabel("search time")

plt.legend()

plt.show()