data = readmatrix("log.txt");

t    = data(:,1)/1000;
temp = data(:,2);
pwm  = data(:,3);
fault= data(:,4);

plot(t,temp,'LineWidth',2)
hold on
plot(t,pwm,'LineWidth',2)

grid on
xlabel("Time (s)")
ylabel("Value")