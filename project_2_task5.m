clear all; close all; clc;
syms d drag lift Jx Jy Jz w1 w2 w3 a1 a2
Tm = sym('Tm',[4 1])
w_speed =  sqrt(abs(Tm)/lift);
    %Torque,
Tx = d*cos(pi/4) * (Tm(3) + Tm(4) - Tm(1) - Tm(2));
Ty = d*cos(pi/4) * (Tm(2) + Tm(3) - Tm(1) - Tm(4));
Tz = drag * (-w_speed(1).^2-w_speed(3).^2+w_speed(2).^2+w_speed(4).^2);
T = [Tx;Ty;Tz];
J = [Jx 0 0;0 Jy 0;0 0 Jz];
w = [w1;w2;w3];
xdot = [w1;w2;inv(J)*(cross(-w,J*w) + T)];
A = jacobian(xdot, [a1,a2,w1,w2,w3]);
B = jacobian(xdot, Tm);
