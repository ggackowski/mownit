import numpy as np 
from matplotlib import pyplot as plt 
import sys

x = np.linspace(-2,2, num=50); 
y = 0
for i in range(1, len(sys.argv)):
    y += float(sys.argv[i]) * x ** (i - 1)

plt.title("Matplotlib demo") 
plt.xlabel("x axis caption") 
plt.ylabel("y axis caption") 
plt.plot(x,y) 
plt.show()
print(len(sys.argv))