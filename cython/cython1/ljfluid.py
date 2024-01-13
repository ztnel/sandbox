from numpy import *
from matplotlib.pyplot import *
from lj import *

# CONSTANTS
# density
density = 0.7
# number of particles per side
n = 3
# timestep
dt = 0.01
# length of run
tmax = 1.0
# cutoff
rcut = 2.5
# potential shift
shift = -0.016316891136

# COMPUTED CONSTANTS
# total number of particles
N = n*n*n
# volume of the system
volume = N/density
# side length of the system
L = volume**(1./3.)

# RUNNING VARIABLES
t = 0.0

# particle positions on cubic lattice
x = empty((3,N))
l = L/n
count = 0
for i in range(n):
    for j in range(n):
        for k in range(n):
            x[:,count] = [i*l, j*l, k*l]
            count += 1

# random particle velocities
v = 2.0*random.random((3,N))-1.0

# variables to cumulate data
ts = []
Es = []
traj = []

# open the trajectory file
vtffile = open('ljfluid.vtf', 'w')
# write the structure of the system into the file: 
# N particles ("atoms") with a radius of 0.5
vtffile.write('atom 0:{} radius 0.5\n'.format(N-1))
vtffile.write('pbc {} {} {}\n'.format(L, L, L))

# write out that a new timestep starts
vtffile.write('timestep\n')
# write out the coordinates of the particles
for i in range(N):
    vtffile.write("{} {} {}\n".format(x[0,i], x[1,i], x[2,i]))

def step_vv(x, v, f, dt):
    # update positions
    x += v*dt + 0.5*f * dt*dt
    # half update of the velocity
    v += 0.5*f * dt
        
    # compute new forces
    f = compute_forces(x)
    # we assume that m=1 for all particles

    # second half update of the velocity
    v += 0.5*f * dt

    return x, v, f

# main loop
set_globals(L, N, rcut, shift)
f = compute_forces(x)

while t < tmax:
    x, v, f = step_vv(x, v, f, dt)
    t += dt

    print "t=%s" % t

    #E = compute_energy(x, v)
    #print "t=%s, E=%s" % (t, E)
    #ts.append(t)
    #Es.append(E)

    # write out that a new timestep starts
    vtffile.write('timestep\n')
    # write out the coordinates of the particles
    for i in range(N):
        vtffile.write("{} {} {}\n".format(x[0,i], x[1,i], x[2,i]))

vtffile.close()

#plot(ts, Es)
#show()
