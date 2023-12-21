# Game-of-Life

## Description
This C++ program simulates a life-like system, resembling cellular automata, similar to Conway's Game of Life. It uses a grid where each cell can either be alive or dead, and the state of each cell changes over generations based on specific rules.

## Features
- **Grid-Based Simulation:** Utilizes a 25x80 grid to simulate life patterns.
- **File Input:** Reads initial configurations from a file, allowing for custom starting setups.
- **Dynamic Evolution:** Each cell's state evolves based on its neighbors, showcasing complex patterns over generations.
- **User Interaction:** Allows users to progress through generations manually and to quit the simulation at any point.

## How to Use
1. **Compile the Program:** Use a C++ compiler to compile the program. For example, using GCC, you can compile with `g++ -o LifeSimulation main.cpp`.
2. **Run the Program:** Start the program. It will prompt you to enter the name of a file containing the initial configuration.
3. **Interact with the Simulation:** Press ENTER to move to the next generation or Q + ENTER to quit the simulation.

## Installation
To run this program, clone this repository or download the source code. Ensure you have a C++ compiler for compiling and running the program.

```bash
git clone https://github.com/yourusername/life-simulation.git
cd life-simulation
g++ -o LifeSimulation main.cpp
./LifeSimulation
```

Contributing

Feel free to fork this repository and contribute to the project. Any improvements or new features are welcome.

Authors

Nathaniel Ramirez
Talal Elhitu
Sven Reyes
License

This project is licensed under the MIT License - see the LICENSE.md file for details.

Acknowledgments

Inspiration from Conway's Game of Life.
Thanks to everyone who has contributed to this project in any way.
