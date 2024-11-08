# Vetor inicial
P_b = [-1; 2; 3; 1]

# Vetor deslocamento
P_a_b_org = [7; -2; 10]

# Rotações (theta = X, phi = Y, psi = Z)
theta = 15 * pi / 180
phi = 45 * pi / 180
psi = -20 * pi / 180

# Matriz de rotação no eixo X
Rx = [1, 0, 0;
      0, cos(theta), -sin(theta);
      0, sin(theta), cos(theta)]

# Matriz de rotação no eixo Y
Ry = [cos(phi), 0, sin(phi);
      0, 1, 0;
      -sin(phi), 0, cos(phi)]

# Matriz de rotação no eixo Z
Rz = [cos(psi), -sin(psi), 0;
      sin(psi), cos(psi), 0;
      0, 0, 1]

# Matriz de transformação homogênea
T_a_b = [Rx * Ry * Rz, P_a_b_org;
        0, 0, 0, 1]

# Posição final
P_a = T_a_b * P_b
