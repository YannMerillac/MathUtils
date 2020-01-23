# -*- coding: utf-8 -*-

import numpy as np
import time
#from scipy.interpolate import Rbf
from RBFinterp import RBFinterp
import matplotlib
#matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib import cm

start_t = time.clock()

# 2-d tests - setup scattered data
n_src = 2000
x = np.random.rand(n_src)*4.0-2.0
y = np.random.rand(n_src)*4.0-2.0
data = x*np.exp(-x**2-y**2)
data = data.reshape((n_src,1))

grid_size = 100
n_eval =  grid_size**2
ti = np.linspace(-2.0, 2.0, grid_size)
XI, YI = np.meshgrid(ti, ti)

xi = XI.reshape(n_eval)
yi = YI.reshape(n_eval)

xyz_src = np.zeros((n_src,2))
xyz_src[:,0] = x
xyz_src[:,1] = y
#xyz_src = np.array((x,y)).T

xyz_eval = np.zeros((n_eval,2))
xyz_eval[:,0] = XI.reshape(n_eval)
xyz_eval[:,1] = YI.reshape(n_eval)

interp_data = np.zeros((n_eval,1))

# use RBF
rbf_interp = RBFinterp(xyz_src,data)
rbf_interp.set_use_poly_part(False)
rbf_interp.compute_weights()
rbf_interp.interpolate(xyz_eval,interp_data)

#interp_data[:,0]-=xi*np.exp(-xi**2-yi**2)

print interp_data
end_t = time.clock()

print "Elapsed time : ",end_t-start_t

data_eval = interp_data[:,0]
ZI = data_eval.reshape((100,100))

# plot the result
#n = plt.normalize(-2., 2.)
plt.subplot(1, 1, 1)
plt.pcolor(XI, YI, ZI, cmap=cm.jet)
#plt.scatter(x, y, 100, data, cmap=cm.jet)
plt.title('RBF interpolation - multiquadrics')
plt.xlim(-2, 2)
plt.ylim(-2, 2)
plt.colorbar()
plt.show()