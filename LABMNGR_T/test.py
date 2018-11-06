#!/usr/bin/env python3
import numpy as np
import time

n = 1000

x = np.random.randn(n,n)

#print(str(x))

a = time.time()

x = x.dot(x)

print(time.time() - a)


