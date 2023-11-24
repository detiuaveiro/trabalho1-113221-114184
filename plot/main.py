import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.optimize import curve_fit

# Define the dimensions
# W_values = np.linspace(50, 500, 10)  # Image widths from 10 to 100
# H_values = np.linspace(50, 500, 10)  # Image heights from 10 to 100
# dw_values = np.linspace(5, 15, 10)      # Blur window widths from 1 to 10
# dh_values = np.linspace(5, 15, 10)      # Blur window heights from 1 to 10

# Initialize lists to store the areas and execution times
A1 = []
R1 = []
T1 = []

A2 = []
R2 = []
T2 = []

with open('first-blur-data.txt', 'r') as f:
    for line in f.readlines():
        line = line.strip()
        if line:
            W, H, dw, dh, Z = line.split(',')
            A1.append(int(W.split(':')[1]) * int(H.split(':')[1]))
            R1.append((2*int(dw.split(':')[1])+1) * (2*int(dh.split(':')[1])+1))
            T1.append(float(Z.split(':')[1]))

with open('second-blur-data.txt', 'r') as f:
    for line in f.readlines():
        line = line.strip()
        if line:
            W, H, dw, dh, Z = line.split(',')
            A2.append(int(W.split(':')[1]) * int(H.split(':')[1]))
            R2.append((2*int(dw.split(':')[1])+1) * (2*int(dh.split(':')[1])+1))
            T2.append(float(Z.split(':')[1]))

# Iterate over each combination of W, H, dw, and dh
# for W in W_values:
#     for H in H_values:
#         for dw in dw_values:
#             for dh in dh_values:
#                 # Calculate the areas
#                 A.append(W * H)
#                 R.append((2*dw+1) * (2*dh+1))  # Calculate the rectangle area
#
#                 # Input the execution time manually
#                 Z.append(float(input(f"Enter the execution time for W={W}, H={H}, dw={dw}, dh={dh}: ")))

# Convert the lists to numpy arrays
A1 = np.array(A1)
R1 = np.array(R1)
T1 = np.array(T1)

A2 = np.array(A2)
R2 = np.array(R2)
T2 = np.array(T2)

# Define a function to fit to the data
def func(X, a, b, c):
    A, R = X
    return a * A * R + b * A + c * R

# Fit the function to the data
popt, pcov = curve_fit(func, (A1, R1), T1)

# Print the function
print(f"The function is: T = {popt[0]} * A * R + {popt[1]} * A + {popt[2]} * R")

# Create a 3D plot
fig = plt.figure()
ax1 = fig.add_subplot(111, projection='3d')
ax2 = fig.add_subplot(222, projection='3d')

ax1.scatter(A1, R1, T1)
#ax2.scatter(A2, R2, T2)

# # Create a grid of x and y values
# A_values = np.linspace(A.min(), A.max(), 100)
# R_values = np.linspace(R.min(), R.max(), 100)
# A_grid, R_grid = np.meshgrid(A_values, R_values)
#
# # Calculate the corresponding z values
# T_values = func((A_grid, R_grid), *popt)
#
# # Plot the surface
# ax.plot_surface(A_grid, R_grid, T_values, alpha=0.5, rstride=100, cstride=100)

ax1.set_xlabel('Área da Imagem')
ax1.set_ylabel('Área de Desfocagem')
ax1.set_zlabel('Tempo de Execução (s)')

ax2.set_xlabel('Área da Imagem')
ax2.set_ylabel('Área de Desfocagem')
ax2.set_zlabel('Tempo de Execução (s)')

#ax1.view_init(elev=0, azim=270)

# Save the figure to a file
plt.savefig('3d_plot.png')
