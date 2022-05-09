
figure(1)
clf
hold on
plot(simulation.time, simulation.actual_roll);
plot(simulation.time, simulation.estimated_roll);
plot(simulation.time, simulation.reference_roll);
xlabel('Time [s]')
ylabel('Orientation angles [deg]')
title('Estimated Roll Angle Performance')
legend("\phi_{true}", "\phi_{est}", "\phi_{ref}");


figure(2)
clf
hold on
plot(simulation.time, simulation.actual_pitch);
plot(simulation.time, simulation.estimated_pitch);
plot(simulation.time, simulation.reference_pitch);
xlabel('Time [s]')
ylabel('Orientation angles [deg]')
title('Estimated Pitch Angle Performance')
legend("\theta_{true}", "\theta_{est}", "\theta_{ref}");

figure(3)
subplot(2,2,1)
plot(simulation.time, simulation.m1);

xlabel('Time [s]')
ylabel('Percentage of Max Ouput [%]')
title('Motor Signal for M1')
legend("M_{1}",'Location','southeast');

subplot(2,2,2)
plot(simulation.time, simulation.m2);

xlabel('Time [s]')
ylabel('Percentage of Max Ouput [%]')
title('Motor Signal for M2')
legend("M_{2}",'Location','southeast');

subplot(2,2,3)
plot(simulation.time, simulation.m3);

xlabel('Time [s]')
ylabel('Percentage of Max Ouput [%]')
title('Motor Signal for M3')
legend("M_{3}",'Location','southeast');

subplot(2,2,4)
plot(simulation.time, simulation.m4);

xlabel('Time [s]')
ylabel('Percentage of Max Ouput [%]')
title('Motor Signal for M4')
legend("M_{4}",'Location','southeast');

