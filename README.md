# space_simulation
Simulates 2D celestial object motions

The program takes input in the form of a file. The name of the file must be entered in the console.

Format of the file must be as follows:
->First line must contain no. of planetary objects who's motion is to be simulated
->Next, details about each object must be given in this order
  ->Mass
  ->X-coordinate of position
  ->Y-coordinate of position
  ->Radius
  ->Initial velocity(x component)
  ->Initial velocity(y component)
  ->Constant force (x component)
  ->Constant force (y component)

The constant force is constant with respect to global coordinates, and does not change with direction of motion of the body.
