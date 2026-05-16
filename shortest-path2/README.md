# Shortest Path Dijkstra's Algorithm
Elliot Wyrick - 11/11/25

Example application of Dijkstra's Algorithm


### To run:

- initialize CMake in build directory 
```
cmake ..
```
- run the makefile it creates
```
make
```
- run the executable with dictionary file
```
./shortest-path2
```
### What It Does

- Loads graph edges from input file (`edges.txt`)
- Constructs graph with configurable number of nodes (default: 6 nodes)
- Implements Dijkstra's algorithm to find shortest path between two nodes
- Provides real-time updates during algorithm execution showing distance updates
- Outputs shortest distance and complete path from source to target
- Handles unreachable nodes gracefully


## [Demo video:](https://youtu.be/vZlzkpZPTmU)

[![Watch the demo](https://img.youtube.com/vi/vZlzkpZPTmU/maxresdefault.jpg)](https://youtu.be/vZlzkpZPTmU)

### Graph Implementation

- Mapped each node to a number:
```
a -> 0
b -> 1
c -> 2
d -> 3
e -> 4
f -> 5
```
- Uses adjacency list representation for efficient edge storage
- Each node stores a vector of outgoing edges (destination + cost + gain)
- Supports directed weighted graphs
- Edge weights are calculated from cost-gain pairs using the formula: **weight = cost / gain**

### Edge Weight Calculation Formula

Edge weights are calculated as: **weight = cost / gain**

This satisfies both requirements: higher cost increases weight, higher gain decreases weight. See [inc/map.hh:12-29](inc/map.hh) and [src/main.cc:52-56](src/main.cc) for implementation.

### Dijkstra's Algorithm Details

Implementation of shortest path algorithm with optimizations:
- Min-heap priority queue for efficient minimum distance extraction
- Distance vector initialized to infinity for all nodes except source (0.0)
- Parent tracking for path reconstruction
- Early termination when target node is reached
- Skips stale entries in priority queue (when better path already found)
- Relaxation step updates distances when shorter path discovered
- Real-time console output shows distance updates during execution

### Edge Cases

- Unreachable nodes: Algorithm detects and reports when no path exists
- Source equals target: Returns distance of 0.0
- Disconnected components: Correctly handles graphs with isolated nodes
- File loading errors: Graceful error handling with informative messages

## Example Usage

### edges.txt

The input file format is now: `from_node to_node cost gain`

```
0 1 3 2
0 2 4 5
1 2 2 1
1 3 6 4
1 4 1 6
2 4 5 3
2 5 3 1
3 4 3 2
4 5 2 10
```

Each line represents: source destination cost gain
The weight is automatically calculated as cost/gain when the algorithm runs.
### program output
```
Constructing Graph with 6 nodes...
Node 0 = Start (a)
Node 5 = End (f)

--- Starting Dijkstra's Algorithm ---
  • Updated Node 1: New Distance 1.5 (via Node 0)
  • Updated Node 2: New Distance 0.8 (via Node 0)
  • Updated Node 4: New Distance 2.4667 (via Node 2)
  • Updated Node 5: New Distance 3.8 (via Node 2)
  • Updated Node 3: New Distance 3 (via Node 1)
  • Updated Node 4: New Distance 1.6667 (via Node 1)
  • Updated Node 5: New Distance 1.8667 (via Node 4)

--- Results ---
Shortest Distance from Node 0 (a) to Node 5 (f): 1.8667
Path: 0 -> 1 -> 4 -> 5
```