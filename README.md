# opengl_3dgraphing_attempt

!!!   THE MAIN CODE IS IN ./src/main.cpp.  THE REST IS THE INCLUDES AND THE BUILD SCRIPTS    !!!

This is my unsuccessful attempt at creating a 3d graphing engine.  Stuck on triangulation as of now.  Somehow implement delaunay 
triangulation in 3d or a projection onto 2d at some point.

I have just started with opengl.  So as of now the entire codebase is primarily just initializing the stuff that opengl needs.
As of now, I have done all things that are needed to fire up opengl and drawn out 3 lines (that are supposed to be the axes of 
a coordinate system) in 3D.  The lines look kind of weird though.  I don't know what's wrong with it.  The details of the 
implementation can sort of be found in the notes.txt file.

The tutorial I have used primarily for these code is learnopengl.com and some other websites.  Very little of this code is original
by any means.  This is just a frankensteined bit to help me understand opengl.  I originally built this to graph out a function in 3D,
but later got lazy and gave up and just used meshlab and blender to do it.

To execute this code, you need a bit of work to get GLFW running.  But other things are built into the include directory.  
