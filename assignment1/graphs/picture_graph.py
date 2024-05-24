import matplotlib.pyplot as plt
import numpy as np

array_sizes = []
picture_search = []



with open('../run_tests/pic_data.txt', 'r') as file:
	for count, line in enumerate(file.readlines()):
            if(count > 0):
                array_sizes.append(float(line.split(" ")[0]))
                picture_search.append(float(line.split(" ")[1]))





x = np.array(array_sizes)

y1 = np.array(picture_search)

plt.figure(figsize=(10, 8))

plt.plot(x, y1, color = 'c', label = 'picture_search')



plt.xlabel("size of string")
plt.ylabel("time taken")

plt.legend()

plt.show()