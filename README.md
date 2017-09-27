# raytracing

![alt text](http://people.tamu.edu/~rogervillanueva/img/raytracer.png)

This is a ray tracer that I wrote for Computer Graphics as well. It draws surfaces given their implicit equations, so they are as smooth as possible no matter how much you might zoom in. The ray tracer works by running a for loop through every pixel, taking a parametric line and intersecting it with all the surfaces in the scene. The surfaces may be infinite cylinders, spheres, ellipsoids, or infinite planes. The ray tracer also functions recursively, to calculate reflections between surfaces, as shown on the bottom left image.
