# Flight Route Finder

COP3530 Project 2. This program uses BFS and DFS to find routes between airports in a directed flight graph. BFS finds a route with the fewest flights. DFS follows the first available branch and does not guarantee the shortest route.

## Requirements

- A C++20 compiler
- CMake 4.1 or newer

## Build

Open a terminal in the `DSAProject2` folder and run:

```sh
cmake -S . -B build
cmake --build build --config Release
```

## Run

Run from the project folder so the program can find the `data` directory. In Windows PowerShell:

```powershell
.\build\DSAProject2.exe
```

The program uses `data/sample_flights.csv` by default. To use the full dataset:

```powershell
.\build\DSAProject2.exe data/Full_Flight_Data.csv
```

If your build places the executable in `build/Release`, use `.\build\Release\DSAProject2.exe` instead. On Linux or macOS, use `./build/DSAProject2` with the same optional dataset path.

Choose `1` for DFS, `2` for BFS, or `3` to exit. Enter the origin and destination as uppercase airport codes separated by a space, for example:

```text
JFK LAX
```

Each search prints the route, number of flights, airports visited, edges examined, and search time in microseconds. Search time includes setup and traversal but excludes rebuilding the final route. Unknown airport codes and routes that cannot be reached are reported separately.

Flights are directed, so a route in one direction does not guarantee a return route. Cancelled, diverted, and invalid rows are skipped when loading the data. The searches use airport connections, not departure times, fares, or travel duration.

If the program cannot load the CSV, check your working directory or pass the full path to the file.

## Tests

After building, run:

```sh
ctest --test-dir build -C Release --output-on-failure
```

This runs `BFS_TEST` and `DFS_TEST`. The tests cover route selection, unreachable destinations, invalid indices, cycles, duplicate flights, and searches where the origin and destination are the same.

## Files

- `main.cpp`: menu and route output
- `graph.h` / `graph.cpp`: graph storage and CSV loading
- `BFS.h` / `BFS.cpp`: breadth-first search
- `DFS.h` / `DFS.cpp`: depth-first search
- `BFS_TEST.cpp` / `DFS_TEST.cpp`: search tests
- `data/`: sample and full flight datasets
