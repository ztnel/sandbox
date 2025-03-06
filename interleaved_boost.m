pkg load control;

% timesteps
t = 0:0.01:10;

% state parameters
r = 1000;
l = 1e-3;
c = 450e-6;
d = 0.5;

% state space model matrices
A = [0 -(1-d)/l; (1-d)/c -1/(r*c)];
B = [1/l; 0];
C = [0 1];
D = 0;

% build state space model and transfer functions
sys = ss(A,B,C,D);
G = tf(sys);

rlocus(G);
