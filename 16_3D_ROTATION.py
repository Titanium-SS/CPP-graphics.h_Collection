"""
The following program is done in Python and using libraries available in Python like Matplotlib and Numpy 
because of their ease in use. The previously used SDL-bgi (graphics.h) is discontinued due to its inability 
to  perform 3D operations. Moreover, 3D graphics often involve a rendering pipeline that includes stages 
like modelling, viewing, projection, and rendering. SDL-BGI lacks the infrastructure to support a 3D rendering pipeline, 
which is crucial for realistic 3D graphics. SDL-BGI does not have built-in support for 3D graphics primitives, 
such as points, lines, or polygons in three-dimensional space. It lacks functions for 3D transformations, 
projections, and rendering. 

"""


import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
import matplotlib.patches as mpatches

def draw_cube(ax, vertices, color, label):
    ax.add_collection3d(Poly3DCollection([[
         vertices[0], vertices[1], vertices[2], vertices[3]],
        [vertices[4], vertices[5], vertices[6], vertices[7]],
        [vertices[0], vertices[1], vertices[5], vertices[4]],
        [vertices[2], vertices[3], vertices[7], vertices[6]],
        [vertices[1], vertices[2], vertices[6], vertices[5]],
        [vertices[0], vertices[3], vertices[7], vertices[4]]
        ], facecolors=color, edgecolors='k', alpha=0.5, label=label))

def rotate_point(x, y, z, angle_x, angle_y, angle_z):
    rotation_matrix_x = np.array([
        [1,          0,                0 ,             0],
        [0,    np.cos(angle_x),   -np.sin(angle_x),    0],
        [0,    np.sin(angle_x),    np.cos(angle_x),    0],
        [0,          0,                0,              1]
    ])

    rotation_matrix_y = np.array([
        [np.cos(angle_y),      0,      np.sin(angle_y),       0],
        [      0,              1,             0,              0],
        [-np.sin(angle_y),     0,      np.cos(angle_y),       0],
        [      0,              0,             0,              1]
    ])

    rotation_matrix_z = np.array([
        [np.cos(angle_z),    -np.sin(angle_z),        0,      0],
        [np.sin(angle_z),     np.cos(angle_z),        0,      0],
        [      0,                   0,                1,      0],
        [      0,                   0,                0,      1]
    ])

    rotation_matrix = np.dot(rotation_matrix_z, np.dot(rotation_matrix_y, rotation_matrix_x))

    homogeneous_point = np.array([x, y, z, 1])
    rotated_point = np.dot(rotation_matrix, homogeneous_point)

    return rotated_point[:3]

def print_vertices_info(vertices, prefix):
    print(f"\n{prefix} Cube Corner Points:")
    for i, vertex in enumerate(vertices):
        print(f"Corner {i + 1}: ({vertex[0]}, {vertex[1]}, {vertex[2]})")

def main():
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Define the vertices of a cube
    cube_vertices = np.array([
        [0, 0, 0],
        [1, 0, 0],
        [1, 1, 0],
        [0, 1, 0],
        [0, 0, 1],
        [1, 0, 1],
        [1, 1, 1],
        [0, 1, 1]
    ])

    # Print initial cube vertices
    print_vertices_info(cube_vertices, "Initial")

    # Initial cube
    draw_cube(ax, cube_vertices, 'm', label='Original Cube')

    # Rotation angles (in radians)
    angle_x, angle_y, angle_z = np.radians(30), np.radians(45), np.radians(60)

    # Rotate each vertex using 3D rotation matrix
    rotated_cube = [rotate_point(x, y, z, angle_x, angle_y, angle_z) for x, y, z in cube_vertices]

    # Rotated cube
    draw_cube(ax, np.array(rotated_cube), 'g', label='Rotated Cube')

    # Print rotated cube vertices
    print_vertices_info(rotated_cube, "Rotated")

    # Set axis labels
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    # Set expanded visible areas
    ax.set_xlim([-1, 2])
    ax.set_ylim([-2, 2])  # Extend the y-axis to the negative direction
    ax.set_zlim([0, 2])

    # Create legend handles
    magenta_patch = mpatches.Patch(color='m', label='Original Cube')
    green_patch = mpatches.Patch(color='g', label='Rotated Cube')

    # Add legend
    ax.legend(handles=[magenta_patch, green_patch])

    plt.show()

if __name__ == "__main__":
    main()
