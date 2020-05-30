#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np


# In[9]:


sizes = [100, 500, 1000, 5000, 10000, 50000]


# In[3]:





# In[10]:


for x in sizes:
    randInts = np.random.random_integers(0, x, x)
    with open( str(x)+".txt", "w") as fp:
        fp.write(str(x))
        for x in range(0, len(randInts)):
            fp.write("\n" + str(randInts[x]))


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:




