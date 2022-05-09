clear all; close all; clc;
load FlightData.mat
d=0.046;
k=2.5383e-11;
b=1.9796e-9;
Jx =1.1463e-5;
Jy = 1.6993e-5;
Jz = 2.9944e-5;
g = 9.81;
A=[0 0 1 0 0;
    0 0 0 1 0;
    0 0 0 0 0;
    0 0 0 0 0;
    0 0 0 0 0];
B=[0 0 0 0;
   0 0 0 0;
    -d/(sqrt(2)*Jx) -d/(sqrt(2)*Jx) d/(sqrt(2)*Jx) d/(sqrt(2)*Jx);
    -d/(sqrt(2)*Jy) d/(sqrt(2)*Jy) d/(sqrt(2)*Jy) -d/(sqrt(2)*Jy);
    -k/(b*Jz) k/(b*Jz) -k/(b*Jz) k/(b*Jz)];
Ts=0.0001;
Q=[1/(25^2) 0 0 0 0;
    0 1/(25^2) 0 0 0;
    0 0 1/(100^2) 0 0;
    0 0 0 1/(100^2) 0;
    0 0 0 0 1/(100^2)];

R=(1/(0.1472^2))*eye(4);
N = 0;
[K,S,E]=lqrd(A,B,Q,R,N,Ts);
