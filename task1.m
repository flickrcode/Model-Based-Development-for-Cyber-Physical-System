R = [cos(30) cos(60) sin(30); sin(30) sin(60) sin(60); cos(30) sin(30) sin(30)];
t = [3;4;5];
eta_b_to_w_4 = [0 0 0 1];

eta_b_to_w_1 = [R t];
eta_b_to_w_2 =  [0 0 0 1];
eta_b_to_w_tot = [eta_b_to_w_1;eta_b_to_w_2];

eta_w_to_b_1 = [R.' (-R')*t];
eta_w_to_b_2 =  [0 0 0 1];
eta_w_to_b_tot = [eta_w_to_b_1;eta_w_to_b_2];

p_w = [1;5;2;1];
p_b = eta_w_to_b_tot*p_w


              