# -*- coding: utf-8 -*-
"""
Created on Thu Nov  2 17:02:00 2023

@author: Tin
"""

import math

radius = 1.0 
height = 2.0
num_segments = 16 

def generate_v():
    vertices = []
    for i in range(num_segments): 
        theta = 2.0 * math.pi * i / num_segments 
        x = radius * math.cos(theta)    
        z = radius * math.sin(theta)    
        vertices.append((x, 0.0, z))    
        vertices.append((x, height, z)) 
    return vertices

def generate_n():
    normals = []
    for i in range(num_segments):
        theta = 2.0 * math.pi * i / num_segments
        normal_x = math.cos(theta)
        normal_z = math.sin(theta)
        normals.append((normal_x, 0.0, normal_z))
        normals.append((normal_x, 0.0, normal_z))
    return normals

def generate_f():
    faces = []
    for i in range(num_segments):
        base_index = 2 * i + 1
        next_index = (base_index + 2) % (2 * num_segments)
        faces.append((base_index, next_index, next_index + 1, base_index + 1))
        
    
    bottom_face = list(range(1, num_segments * 2 + 1, 2))
    faces.append(bottom_face)

    
    top_face = list(range(2, num_segments * 2 + 1, 2))
    top_face.append(2)  
    faces.append(top_face)
    
    return faces

output_file = "cilindar.obj"

vertices = generate_v()
normals = generate_n()
faces = generate_f()

with open(output_file, "w") as f:
    for v in vertices:
        f.write(f"v {v[0]:.6f} {v[1]:.6f} {v[2]:.6f}\n")
    
    for n in normals:
        f.write(f"vn {n[0]:.4f} {n[1]:.4f} {n[2]:.4f}\n")
    
    for face in faces:
        f.write("f")
        for vertex_index in face:
            f.write(f" {vertex_index}")
        f.write("\n")

print("Generiran")
