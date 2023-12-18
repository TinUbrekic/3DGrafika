#pragma once
#include <cmath>
#include "geometry.h"
#include "ray.h"
#include "material.h"
#include<limits>
#include<iostream>

class Object 
{
  public:
    Material material;
    virtual bool ray_intersect(const Ray &ray, float &t, Vec3f &normal) const = 0;  
};

class Sphere : public Object
{
    float r;
    Vec3f c;
      
  public:
    Sphere(const Vec3f &c, const float &r) : c(c), r(r) { }
    Sphere(const Vec3f &c, const float &r, const Material &mat) : c(c), r(r)
    { 
        Object::material = mat;
    }

    bool ray_intersect(const Ray &ray, float &t, Vec3f &normal) const
    {
        Vec3f e_minus_c = ray.origin - c;
        float d2 = ray.direction * ray.direction;
        
        float disc = pow(ray.direction * e_minus_c, 2) - d2 * (e_minus_c * e_minus_c - r * r);
        
        if (disc < 0)
        {
            return false;
        }
        else
        {
            bool ray_inside_sphere = e_minus_c * e_minus_c <= r * r;
            if (ray_inside_sphere)
            {
                float t1 = (-ray.direction * e_minus_c + sqrt(disc)) / d2;
                t = t1;
            }
            else
            {
                float t2 = (-ray.direction * e_minus_c - sqrt(disc)) / d2;
                t = t2;
            }
            
            Vec3f hit_point = ray.origin + ray.direction * t;
            normal = (hit_point - c).normalize();
            return true;
        }
    }
};
struct Cuboid:public Object
{
    Vec3f a;
    Vec3f b;
public:
    Cuboid(const Vec3f &a, const Vec3f &b) : a(a), b(b) { }
    Cuboid(const Vec3f &a, const Vec3f &b, const Material &mat): a(a), b(b){
        Object::material=mat;
    }
    bool ray_intersect(const Ray &ray, float &t, Vec3f &normal) const{
        float t_min = numeric_limits<float>::min();
        float t_max = numeric_limits<float>::max();

        float minX = min(a.x, b.x);
        float minY = min(a.y, b.y);
        float minZ = min(a.z, b.z);

        float maxX = max(a.x, b.x);
        float maxY = max(a.y, b.y);
        float maxZ = max(a.z, b.z);

        if(ray.direction.x == 0 && (ray.origin.x<minX || ray.origin.x > maxX)){
            return false;
        }
        else{
            float t1 = (minX - ray.origin.x) / ray.direction.x;
            float t2 = (maxX - ray.origin.x) / ray.direction.x;

            if(t1>t2){
                swap(t1,t2);
            }
            t_min=max(t_min,t1);
            t_max=min(t_max,t2);

            if(t_min>t_max || t_max<0){
                return false;
            }
        }
        t=t_min;

        if(ray.direction.y == 0 && (ray.origin.y < minZ || ray.origin.y > maxZ)){
                return false;
    }

        else{
            float t1=(minZ-ray.origin.y)/ray.direction.y;
            float t2=(maxZ-ray.origin.z)/ray.direction.z;

            if(t1>t2){
                swap(t1,t2);
            }
            t_min=max(t_min,t1);
            t_max=min(t_max,t2);
            if(t_min>t_max || t_max<0){
                return false;
            }
        }
        t=t_min;
        if(abs(ray.origin.x - a.x) < 0.01){
            normal = Vec3f(1, 0, 0);
        }else if(abs(ray.origin.x - b.x) < 0.01){
            normal = Vec3f(-1, 0, 0);
        }else if(abs(ray.origin.y - a.y) < 0.01){
            normal = Vec3f(0, 1, 0);
        }else if(abs(ray.origin.y - b.y) < 0.01){
            normal = Vec3f(0, -1, 0);
        }else if(abs(ray.origin.z - a.z) < 0.01){
            normal = Vec3f(0, 0, 1);
        }else if(abs(ray.origin.z - b.z) < 0.01){
            normal = Vec3f(0, 0, -1);
        }


        return true;
    }

};
