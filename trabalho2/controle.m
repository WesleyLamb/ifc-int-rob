%Rotação continuo -> discreto
clear all;
clc;

pkg load control;

d = 0.05; % Distância entre a roda e o centro de massa do carrinho
r = 0.05; % Raio da roda
m = 0.2; % Massa do carrinho
a = 2*d; % Largura do carrinho
b = 2*d; % Comprimento do carrinho

Jz = (1/12) * m * (a^2 + b^2);

A = [0, 1; 0 0]; % Matriz de estados
B = [0, 0; -d/(r*Jz), d/(r*Jz)]; % Matriz de entrada
C = [1, 0]; % Matriz de saída
D = [0, 0]; % Matriz de transmissão direta

Xc = ss(A, B, C, D); % Sistema contínuo
ts = 0.1; % Período de amostragem
Xd = c2d(Xc, ts); % Sistema discreto

Q = [100, 0; 0, 100]; % Matriz de ponderação do estado
R = [1, 0; 0, 1]; % Matriz de ponderação da entrada

K = dlqr(Xd, Q, R); % Ganho de realimentação de estado
Ad2 = Xd.A - Xd.B*K; % Matriz de estados do sistema em malha fechada
Xd2 = ss(Ad2, [1, 1; 0, 0], Xd.C, Xd.D, ts); % Sistema discreto em malha fechada
