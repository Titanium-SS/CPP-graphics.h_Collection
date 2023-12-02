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
         vertices[0], vertices[1], vertices[2], vertices[3], vertices[0]],
        [vertices[4], vertices[5], vertices[6], vertices[7], vertices[4]],
        [vertices[0], vertices[1], vertices[5], vertices[4], vertices[0]],
        [vertices[2], vertices[3], vertices[7], vertices[6], vertices[2]],
        [vertices[1], vertices[2], vertices[6], vertices[5], vertices[1]],
        [vertices[0], vertices[3], vertices[7], vertices[4], vertices[0]]
    ], facecolors=[color], edgecolors='k', alpha=0.5, label=label))

def translate_point(x, y, z, tx, ty, tz):
    translation_matrix = np.array([
        [1, 0, 0, tx],
        [0, 1, 0, ty],
        [0, 0, 1, tz],
        [0, 0, 0,  1]
    ])

    homogeneous_point = np.array([x, y, z, 1])
    translated_point = np.dot(translation_matrix, homogeneous_point)

    return translated_point[:3]  # Discard the homogeneous coordinate

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
    draw_cube(ax, cube_vertices, 'b', label='Original Cube')

    # Translation vector
    tx, ty, tz = 1, 2, 3

    # Translate each vertex using 3D translation matrix
    translated_cube = [translate_point(x, y, z, tx, ty, tz) for x, y, z in cube_vertices]

    # Translated cube
    draw_cube(ax, np.array(translated_cube), 'r', label='Translated Cube')

    # Print translated cube vertices
    print_vertices_info(translated_cube, "Translated")

    # Set axis labels
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    # Set expanded visible areas
    ax.set_xlim([0, 4])
    ax.set_ylim([0, 4])
    ax.set_zlim([0, 4])

    # Create legend handles
    blue_patch = mpatches.Patch(color='b', label='Original Cube')
    red_patch = mpatches.Patch(color='r', label='Translated Cube')

    # Add legend
    ax.legend(handles=[blue_patch, red_patch])

    plt.show()

if __name__ == "__main__":
    main()
