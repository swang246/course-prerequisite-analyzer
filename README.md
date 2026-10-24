# Course Prerequisite Analyzer

A C++ graph algorithm project that models course prerequisites as a directed graph and analyzes course dependencies to determine a topological ordering and the minimum number of semesters needed to complete the courses.


### Compile

Run the following command in the terminal from the directory containing `course_scheduler.cpp`:

```bash
g++ course_scheduler.cpp -o course_scheduler
```

### Run

Pass the input and output filenames as command-line arguments.

**Windows PowerShell:**

```powershell
.\course_scheduler input.txt output.txt
```

**Linux/macOS:**

```bash
./course_scheduler input.txt output.txt
```

## Input Format

Each line contains two integers representing a prerequisite relationship:

```text
prerequisite_course course_that_requires_it
```

For example:

```text
2 4
4 5
1 6
3 6
```

This means courses 2 and 1 are prerequisites for other courses, including course 4 requiring course 2 and course 6 requiring course 1 and course 3.

The program currently assumes that course IDs range from 1 to 15.

## Output

The output file is intended to contain:

- Whether the graph contains a cycle
- The classified edges
- A topological ordering of the courses
- The minimum number of semesters required
- The program's running time

## Algorithms and Concepts

### Topological Sorting

Uses depth-first search to traverse course dependencies and build an ordering of courses. A valid topological ordering exists only when the directed graph has no cycles.

### Edge Classification

During depth-first search, edges can be classified as:

- **Tree edges:** Discover a previously unvisited vertex.
- **Back edges:** Point to an ancestor in the current DFS path and indicate a cycle.
- **Forward edges:** Point to a previously discovered descendant.
- **Cross edges:** Connect vertices that are neither ancestors nor descendants in the DFS tree.

### Minimum Semesters

Uses a queue-based, indegree-driven traversal similar to Kahn's algorithm. Each course is assigned the earliest semester in which it can be taken, based on its prerequisites. Courses without prerequisite dependencies can be taken in the first semester.
## Purpose

This project demonstrates practical applications of graph algorithms to course planning, dependency analysis, and scheduling problems.
