#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "./ode-0.12/include/ode/ode.h"
#include "./ode-0.12/include/drawstuff/drawstuff.h"

// dynamics and collision objects
static dWorldID world;
static dSpaceID space;
static dBodyID body;
static dGeomID geom;
static dMass m;
static dJointGroupID contactgroup;

// this is called by dSpaceCollide when two objects in space are
// potentially colliding.
static void nearCallback (void * data, dGeomID o1, dGeomID o2)
  {
    dBodyID b1 = dGeomGetBody (o1);
    dBodyID b2 = dGeomGetBody (o2);
    dContact contact;  

    contact . surface . mode = dContactBounce | dContactSoftCFM;

    // friction parameter
    contact . surface . mu = dInfinity;

    // bounce is the amount of "bouncyness".
    contact . surface . bounce = 0.6;

    // bounce_vel is the minimum incoming velocity to cause a bounce
    contact . surface . bounce_vel = 0.4;

    // constraint force mixing parameter
    contact . surface . soft_cfm = 0.001;  

    if (dCollide (o1, o2, 1, & contact . geom, sizeof (dContact)))
      {
        dJointID c = dJointCreateContact (world, contactgroup, & contact);
        dJointAttach (c, b1, b2);
      }
  }

static float xyz [3] = {6.0f, -6.0f, 5.5000f};
static float hpr [3] = {140.000f, -17.0000f, 0.0000f};

// start simulation - set viewpoint
static void start (void)
  {
    dsSetViewpoint (xyz, hpr);
  }

static int deadCount = 20;
// simulation loop
static void simLoop (int pause)
  {
    const dReal * pos;
    const dReal * R;
    dReal rad, leng;

    // find collisions and add contact joints
    dSpaceCollide (space, 0, & nearCallback);

    // step the simulation
    dWorldQuickStep (world,0.1);  

    // remove all contact joints
    dJointGroupEmpty (contactgroup);

    // redraw sphere at new location
    pos = dGeomGetPosition (geom);
    R = dGeomGetRotation (geom);
    dGeomCylinderGetParams (geom, & rad, & leng);
{
    xyz [0] = pos [0] + 4.0;
    xyz [1] = pos [1] - 4.0;
    xyz [2] = 4.0;
    dsSetViewpoint (xyz, hpr);
}
    dsDrawCylinder (pos,R,leng,rad);

    const dReal * v = dBodyGetLinearVel (body);
    const dReal * p = dBodyGetPosition (body);
    const dReal * r = dBodyGetRotation (body);
    if (p[2] < .01 && fabs (v [0] + v [1] + v [2]) < .01)
      {
        if (deadCount -- < 0)
{
          dsStop ();
//printf ("%g %g %g %g\n", r [0], r [1], r [2], r [3]);
//printf ("%g %g %g %g\n", r [4], r [5], r [6], r [7]);
//printf ("%g %g %g %g\n", r [8], r [9], r [10], r [11]);
printf ("\n\n      %s\n\n", r [10] < 0.0 ? "Tails (NO)" : "Heads (YES)");
      }
}
  }

int main (int argc, char * * argv)
  {
    dMatrix3 R;

    srand48 (time (NULL));

    // setup pointers to drawstuff callback functions
    dsFunctions fn;
    fn . version = DS_VERSION;
    fn . start = & start;
    fn . step = & simLoop;
    fn . stop = 0;
    fn . command = 0;
    fn . path_to_textures = "./ode-0.12/drawstuff/textures";
 
    dInitODE ();

    // create world
    world = dWorldCreate ();
    space = dHashSpaceCreate (0);
    dWorldSetGravity (world, 0, 0, -0.2);
    dWorldSetCFM (world, 1e-5);
    dCreatePlane (space, 0, 0, 1, 0);
    contactgroup = dJointGroupCreate (0);

    // create object
    body = dBodyCreate (world);
    geom = dCreateCylinder (space, 0.5, 0.5 / 13.0);
    dMassSetCylinder (& m, 1, 1, 0.5, 0.5 / 13.0);
    dBodySetMass (body, & m);
    dGeomSetBody (geom, body);

    // set initial position
    dBodySetPosition (body, 0, 0, 6);

    dRSetIdentity (R);
    dRFromAxisAndAngle (R, drand48 () * 2.0 - 1.0, drand48 () * 2.0 - 1.0,
                           drand48 () * 2.0 - 1.0, drand48 () * 10.0 - 5.0);

    dBodySetRotation (body, R);
    dBodySetAngularVel (body, drand48 ()* 3.0, drand48 ()* 3.0, drand48 ());

    // run simulation
    dsSimulationLoop (argc, argv, 800, 800, & fn);

    // clean up
    dJointGroupDestroy (contactgroup);
    dSpaceDestroy (space);
    dWorldDestroy (world);

    dCloseODE ();
    return 0;
  }

