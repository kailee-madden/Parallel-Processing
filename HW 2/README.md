# Homework 2 - Running an OpenMP program

1. The selected program is Dijkstra's minimum distance algorithm. This algorithm takes a distance matrix, which is a way of represented a graph of connected nodes, and calculates a list of the minimum distance from node 0 to each of the other nodes.
The program first creates the distance matrix, essentially an array of arrays.
Then it starts with node 0 and begins to create a tree that will contain all the connected nodes eventually. A search is started to check for the closest unconnected node. This node then gets connected and its distance is added. For all the remaining unconnected nodes, we have to check to see if there is a different path to get to our newly connected node that would actually give us a smaller distance. This is then repeated for node 0 to each other node, which then gives us the minimum distance from node 0 to each of the other nodes.

2. This program uses the following categories of OpenMP language extensions:
    - Parallel: parallel
    - Work sharing: single
    - Data environment: private, shared
    - Synchronization: critical, barrier
    - Runtime functions, env. variables: omp_get_thread_num, omp_get_num_threads
This program defines a parallel region where the nodes of the graph are divided up among threads. 
There are private and shared variables. The private ones are those that are specific to the node for that thread and are as follows: private ( my_first, my_id, my_last, my_md, my_mv, my_step ). The shared ones are shared amongst all the threads and are as follows: shared ( connected, md, mind, mv, nth, ohd ). These shared variables denote the connections and relationships between each node that are necessary to even search for a minimum distance between two nodes.
The first directive within the parallel region is single and has the first thread that reaches it execute it. This part just prints out helpful information for the user (ie how many threads there are).
Next each thread starts a for loop to repeatedly search for the nearest unconnected node (because we want a minimum distance), if there is an unconnected node. 
Within these for loops that have been started for each thread, there are single, critical, and barrier directives.
The single directives include the one already explained above, a single directive to allow one thread to set the shared minimum distance to an extremely high value (so when comparing to find minimum we will), a single directive to update the shared connected tree value with the minimum distance that has been determined by all the threads, and the final single directive just prints out that we have completed dijkstra's algorithm.
The critical directives act similarly to locks in that only one thread can execute at a time (the threads execute serially). In this code the critical directive is the section that checks if one node has a smaller private minimum distance to another node than the shared minimum distance variable, if so, it updates the shared minimum distance variable.
The barrier directives have each thread wait at the barrier until all threads arrive. The first barrier directive ensures that all the nodes have executed the above critical directive for determining minimum distance. The next barrier ensures the connected value has been updated by a single thread. The last barrier ensures the whole update region has been completed by every thread.

3. Runtimes using an interactive node. The output files for these runs of the dijkstra algorithm are contained in the Interactive Node Output folder and contain what the dijkstra code actually outputs.
    - 1: real	0m0.002s
    - 2: real	0m0.002s
    - 4: real	0m0.002s
    - 8: real	0m0.003s
    - 16: real	0m0.004s
    - 32: real	0m0.006s
    - 64: real	0m0.009s
    - 128: real	0m0.016s

4. Average runtimes using a batch script and parallel speedup. The script is called dijkstra_openmp.sb. I edited the batch script based on the number of threads that I wanted to create. These output files are contained in the Batch Output folder and contain the average time to run.
    - 1: real 0m.0.0016s, parallel speedup 1
    - 2: real 0m.0.0026s, parallel speedup 0.615
    - 4: real 0m.0.0024s, parallel speedup 0.667
    - 8: real 0m.0.0028s, parallel speedup 0.571
    - 16: real 0m.0.0033s, parallel speedup 0.485
    - 32: real 0m.0.0052s, parallel speedup 0.308
    - 64: real 0m.0.0071s, parallel speedup 0.225
    - 128: real 0m.0.0102s, parallel speedup 0.157
5. From 3. and 4. it is clear that while one might think more threads is automatically better and faster, that is not always the case. There is an overhead cost for starting all those threads and if the time cost of starting the threads is longer than the speedup benefit provided by having those extra threads, then it is not worth it. Essentially, a balance must be struck to find the optimal number of threads based on the complexity of the parallel program. The threads need to provide enough speedup to justify their existence. In this case, the graph that dijkstra's algorithm is being run on is a very simple graph. So in this case, parallel programming does not actually make sense since the overhead cost of starting up extra threads outweighs any benefit that those threads may provide in computational power. The parallel speedup shows that we actually are losing time rather than getting any speedup.
Note that generally, one would expect to see a linear speedup that eventually flattens out (according to Amdahl's Law). This dijkstra's algorithm is unique because it has very minimal parallization and because it is tested on only 6 nodes (a very very small test case).
For instance, running the FFT (fast fourier transform) algorithm gives a time of 0m52.575s when using only one thread, a time of 0m34.217s when using two threads, and a time of 0m33.622s when using 127 threads. (Note I used 127 threads because can actually only use 127 threads when running on one shared node in a batch script). Thus, when the algorithm has sufficient parallelization and is complex enough that there is sufficient benefit that outweighs the overhead of starting up multiple threads, then parallizing the algorithm is worth it (ex. FFT). However, when this is not the case, such as with our very small 6 node Dijkstra example that has minimal parallization, then it is not worth it.