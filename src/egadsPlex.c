/*
*        Program is intended to read the Geometric Topology of an EGADSlite geometry file and store it
*        in a Petsc Plex
*
*/

#include "egads.h"
#include "petsc.h"
#include "petscdmplex.h"

int main(int argc, char *argv[])
{
  // Define Variables
  int i, j, k, l, n, ll, nn, mm, nloops, index, stat, oclass, mtype, nbodies, *senses;
  double limits[4];
  ego context, model, geom, *bodies, *objs, *nobjs, *mobjs, *lobjs;
  
  // Check for the right number or arguments
  if (argc != 2) {
    printf(" Usage: liteTest liteFile\n\n");
    exit(EXIT_FAILURE);
  }
  
  // Open EGADs file and load EGADs model data
  printf(" EG_open          = %d\n", EG_open(&context));
  printf(" EG_loadModel     = %d  %s\n", EG_loadModel(context, 0, argv[1],
                                                      &model), argv[1]);
  
  /* test bodyTopo functions */
  stat = EG_getTopology(model, &geom, &oclass, &mtype, NULL, &nbodies,
                        &bodies, &senses);
                        
  printf(" Number of BODIES (nbodies): %d \n", nbodies);
  
  // Loop through BODIES
  for (i = 0; i < nbodies; i++)
    {
    // Output Basic Model Topology
    stat = EG_getBodyTopos(bodies[i], NULL, SHELL, &n, &objs);  // Get number of SHELLS
    printf("   Number of SHELLS (n): %d \n", n);
    
    stat = EG_getBodyTopos(bodies[i], NULL, FACE, &n, &objs);  // Get number of FACES
    printf("     Number of FACES (n): %d \n", n);
    
    stat = EG_getBodyTopos(bodies[i], NULL, LOOP, &nloops, &lobjs);  // Get number of LOOPS
    printf("       Number of LOOPS (n): %d \n", nloops);

    stat = EG_getBodyTopos(bodies[i], NULL, EDGE, &l, &objs);  // Get number of EDGES
    printf("         Number of EDGES (n): %d \n", l);
    
    stat = EG_getBodyTopos(bodies[i], NULL, NODE, &n, &objs);  // Get number of NODES
    printf("           Number of NODES (n): %d \n", n);
    
    // Cycle through LOOPS
    for (ll = 0; ll < nloops; ll++)
      {
      index = EG_indexBodyTopo(bodies[i], lobjs[ll]);    // Print out Loop IDs
      printf("          LOOP ID: %d \n", index);
      
      // Get EDGE info which associated with the current LOOP
      stat = EG_getTopology(lobjs[ll], &geom, &oclass, &mtype, NULL, &n,
                        &objs, &senses);
      
      // Cycle through EDGES
      for (j = 0; j < n; j++)
        {
        index = EG_indexBodyTopo(bodies[i], objs[j]);    // Print out EDGE IDs
        printf("            EDGE ID: %d \n", index);
        
        // Get NODE info which associated with the current EDGE
        stat = EG_getTopology(objs[j], &geom, &oclass, &mtype, NULL, &nn,
                          &nobjs, &senses);
        
        // Cycle through NODES
        for (k = 0; k < nn; k++)
          {
          // Get Current NODE data
          stat = EG_getTopology(nobjs[k], &geom, &oclass, &mtype, limits, &mm,
                          &mobjs, &senses);
          
          index = EG_indexBodyTopo(bodies[i], nobjs[k]);    // Print out NODE IDs & coordinates
          printf("              NODE ID: %d \n", index);
          printf("                 (x, y, z) = ( %lf, %lf, %lf) \n", limits[0], limits[1], limits[2]);
          } 
        }
      }
    }
    
  // Generate Petsc Plex
  //    Get all Nodes in model, record coordinates in a correctly formated array
  //    Cycle through bodies, cycle through loops, recorde NODE IDs in a correctly formateed array
  
  // Get All NODEs in a model
  stat = EG_getBodyTopos(model, NULL, NODE, &n, &objs);
  printf("\n Number of NODEs in Model = %d \n", n);

  /* Close EGADSlite file */
  printf(" EG_close         = %d\n", EG_close(context));
  return 0;
}