#include <iostream>
using std::cout, std::endl, std::cerr;
#include <string>
using std::string;
#include <fstream>
using std::ifstream, std::ofstream;
#include <vector>
using std::vector;
#include "Grid.h"

// void visualizing(vector<string>& solution, Grid& maze) {
// 	//print each slide so that it can be better visualized
// }

void print(vector<string>& solution) { //for debugging
	cout << "PRINTING PATH UP TIL NOW:" << endl;
	for (int i = 0; i < solution.size(); i++) {
		cout << solution[i] << endl;
	}
}

bool find_maze_path(vector<Grid>& mazes, int row, int col, int level, int dimension, vector<string>& solution) {
	//select correct dimensioned maze
	Grid& maze = mazes.at(dimension);

	//set as visited
	maze.at(row, col, level) = 2;

	//update Solution
	string loc = std::to_string(row) + "   " + std::to_string(col) + "   " + std::to_string(level) + "     " + std::to_string(dimension);
	solution.push_back(loc);

	// print(solution); //For Debugging

	//found the End
	if (row == maze.height() - 1 && col == maze.width() - 1 && level == maze.depth() - 1) {
		return true;
	}

	//TRYING ALL 8 DIRECTIONS
	//trying rows (down and up)
	if ((row != maze.height() - 1) && maze.at(row + 1, col, level) == 1) {
		if (find_maze_path(mazes, row + 1, col, level, dimension, solution)) {
			return true;
		} else {
			solution.pop_back();
		}
	}
	if ((row != 0) && maze.at(row - 1, col, level) == 1) {
		if (find_maze_path(mazes, row - 1, col, level, dimension, solution)) {
			return true;
		} else {
			solution.pop_back();
		}
	}
	//trying columns (right and left)
	if ((col != maze.width() - 1) && maze.at(row, col + 1, level) == 1) {
		if (find_maze_path(mazes, row, col + 1, level, dimension, solution)) {
			return true;
		} else {
			solution.pop_back();
		}
	}
	if ((col != 0) && maze.at(row, col - 1, level) == 1) {
		if (find_maze_path(mazes, row, col - 1, level, dimension, solution)) {
			return true;
		} else {
			solution.pop_back();
		}
	}
	//trying depths/floors (up and down)
	if ((level != maze.depth() - 1) && maze.at(row, col, level + 1) == 1) {
		if (find_maze_path(mazes, row, col, level + 1, dimension, solution)) {
			return true;
		} else {
			solution.pop_back();
		}
	}
	if ((level != 0) && maze.at(row, col, level - 1) == 1) {
		if (find_maze_path(mazes, row, col, level - 1, dimension, solution)) {
			return true;
		} else {
			solution.pop_back();
		}
	}
	//trying parrallel dimensions (upper and lower) //Maybe make these wrap? dimension 9 -> 0?
	if ((dimension != mazes.size() - 1) && mazes.at(dimension + 1).at(row, col, level) == 1) {
		if (find_maze_path(mazes, row, col, level, dimension + 1, solution)) {
			return true;
		} else {
			solution.pop_back();
		}
	}
	if ((dimension != 0) && mazes.at(dimension - 1).at(row, col, level) == 1) {
		if (find_maze_path(mazes, row, col, level, dimension - 1, solution)) {
			return true;
		} else {
			solution.pop_back();
		}
	}

	return false;
}


int main(int argc, char* argv[]) {

	//Initializing arguments
	if (argc < 3) {
		cerr << "Insufficent number of arguments given" << endl;
		return 1;
	}
	ofstream ofile(argv[argc - 1]);

	//Initializing the maze
	vector<Grid> mazes;
	for (int i = 1; i < argc - 1; i++) {
		ifstream ifile(argv[i]);
		Grid maze;
		ifile >> maze;
		mazes.push_back(maze);
		ifile.close();
		// cout << "added maze" << i << endl;
	}
	// cout << "Total number of dimensions: " << mazes.size() << endl;

	// cout << "The maze is " << maze.height() << " spaces tall, " << maze.width() << " spaces wide, and " << maze.depth() << " spaces deep" << endl; // access the maze's dimensions
	vector<string> solution;

	//Solving the maze and printing solution
	if (find_maze_path(mazes, 0, 0, 0, 0, solution)) {
		ofile << "SOLUTION" << endl;
		ofile << "row col level dimension" << endl;
		for (int i = 0; i < solution.size(); i++) {
			ofile << solution[i] << endl;
		}
	} else {
		ofile << "NO SOLUTION" << endl;
	}

	ofile.close();
    return 0;
}
