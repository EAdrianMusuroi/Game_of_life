/*
Command line arguments:
	- matrix size n
	- matrix size m
	- iterations 
	- file to read the initial state
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <time.h>

// Function prototypes
void error(char*);
void print_matrix(int**, int, int);
int** read_input_data(char**, int*, int*, int*, int**);
void print_matrix_to_file(int**, int, int, int);
void print_time_to_file(int, int, int, double);

void get_next_iteration(int **old_matrix, int **new_matrix, int n, int m) {

	int matrix_parse_i, matrix_parse_j;

	int neighbors_i[] = {-1, -1, -1, 0, 1, 1,  1,  0};
	int neighbors_j[] = {-1,  0,  1, 1, 1, 0, -1, -1};

	int alive_neighbors;
	int i, j, neighbor;

	for(matrix_parse_i = 0; matrix_parse_i < n; matrix_parse_i++) {
		for(matrix_parse_j = 0; matrix_parse_j < m; matrix_parse_j++) {

			alive_neighbors = 0;

			// Count alive neighbors
			for(neighbor = 0; neighbor < 8; neighbor++) {
				i = matrix_parse_i + neighbors_i[neighbor];
				j = matrix_parse_j + neighbors_j[neighbor];

				// Make sure we stay in the matrix
				if(i == -1 || i == n) continue;
				if(j == -1 || j == m) continue;

				if(old_matrix[i][j] == 1)
					alive_neighbors++;
			}

			// Update new matrix
			if(old_matrix[matrix_parse_i][matrix_parse_j] == 1) {  // if alive
				if(alive_neighbors == 2 || alive_neighbors == 3)
					new_matrix[matrix_parse_i][matrix_parse_j] = 1;
				else
					new_matrix[matrix_parse_i][matrix_parse_j] = 0;
			}
			else { // if dead
				if(alive_neighbors == 3)
					new_matrix[matrix_parse_i][matrix_parse_j] = 1;
				else
					new_matrix[matrix_parse_i][matrix_parse_j] = 0;
			}
		}
	}
}

int main(int argc, char **argv) {

	if(argc < 5)
		error("Too few arguments.");

	// Matrix size 
	int n, m;

	// Number of iterations to be made
	int iterations;

	// Initial state matrix
	int **matrix_A = NULL;

	// Read input data
	matrix_A = read_input_data(argv, &n, &m, &iterations, matrix_A);

	// Alloc space for auxiliary matrix
	int **matrix_B;
	int matrix_parse_i;
	matrix_B = (int**)malloc(sizeof(int*) * n);

	for(matrix_parse_i = 0; matrix_parse_i < n; matrix_parse_i++)
		matrix_B[matrix_parse_i] = (int*)malloc(sizeof(int) * m);

	// When 0, current state in matrix_A
	// When 1, current state in matrix_B
	int matrix_flag = 0;

	// Start timer
	struct timespec start, finish;
	double elapsed;

	clock_gettime(CLOCK_MONOTONIC, &start);

	int iteration_count;
	for(iteration_count = 0; iteration_count < iterations; iteration_count++) {

		if(matrix_flag == 0) {
			get_next_iteration(matrix_A, matrix_B, n, m);
			matrix_flag = 1;
		}
		else {
			get_next_iteration(matrix_B, matrix_A, n, m);
			matrix_flag = 0;
		}
	}

	clock_gettime(CLOCK_MONOTONIC, &finish);

	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	int **final_matrix;

	if(matrix_flag == 0)
		final_matrix = matrix_A;
	else 
		final_matrix = matrix_B;

	// Print final state of matrix
	print_matrix(final_matrix, n, m);
	print_matrix_to_file(final_matrix, n, m, iterations);

	// Print execution time
	printf("%f\n", elapsed);
	print_time_to_file(n, m, iterations, elapsed);

	return 0;
}

int** read_input_data(char **argv, int *matrix_n, int *matrix_m, int *nr_iterations, int **matrix_A) {

	// Get the matrix size
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
	int iterations = atoi(argv[3]);

	// Verify that the file exists
	struct stat file_stat;

	if(stat(argv[4], &file_stat) != 0)
		error("Input file does not exist.");

	if(!S_ISREG(file_stat.st_mode))
		error("Input file must be regular file.");

	// Open file
	int input_fd;

	input_fd = open(argv[4], O_RDONLY);

	if(input_fd == -1)
		error("Cannot open input file.");

	// Read data from file
	int **matrix;
	int matrix_parse_i, matrix_parse_j;

	matrix = (int**)malloc(sizeof(int*) * n);

	for(matrix_parse_i = 0; matrix_parse_i < n; matrix_parse_i++)
		matrix[matrix_parse_i] = (int*)malloc(sizeof(int) * m);

	char byte;
	int read_status;

	for(matrix_parse_i = 0; matrix_parse_i < n; matrix_parse_i++) {
		for(matrix_parse_j = 0; matrix_parse_j < m; matrix_parse_j++) {

			// Read one byte
			read_status = read(input_fd, &byte, 1);

			if(read_status == -1)
				error("Error occured while reading from file.");

			if(read_status < 1)
				error("Not enough data in input file.");

			if(byte == '0')
				matrix[matrix_parse_i][matrix_parse_j] = 0;
			else if(byte == '1')
				matrix[matrix_parse_i][matrix_parse_j] = 1;
		}
	}

	// Close file
	if(close(input_fd) != 0)
		error("Error closing input file.");

	*matrix_n = n;
	*matrix_m = m;
	*nr_iterations = iterations;
	
	return matrix;
}

void error(char *error_message) {

	printf("%s\n", error_message);
	exit(1);
}

void print_matrix(int **matrix, int n, int m) {

	int matrix_parse_i, matrix_parse_j;

	for(matrix_parse_i = 0; matrix_parse_i < n; matrix_parse_i++) {
		for(matrix_parse_j = 0; matrix_parse_j < m; matrix_parse_j++)
			printf("%d\t", matrix[matrix_parse_i][matrix_parse_j]);
		printf("\n");
	}
}

void print_matrix_to_file(int **matrix, int n, int m, int iterations) {

	char file_name[50];

	sprintf(file_name, "../output_matrix/GOL_%dx%d_%d", n, m, iterations);

	int fd = open(file_name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

	if(fd == -1)
		error("Error opening file to write.");

	char dead = '0', alive = '1';

	int i, j;

	for(i = 0; i < n; i++) {
		for(j = 0; j < m; j++) {
			if(matrix[i][j] == 0) {
				if(write(fd, &dead, 1) != 1)
					error("Error writing to file.");
			}
			else 
				if(write(fd, &alive, 1) != 1)
					error("Error writing to file.");	
		}
	}

	close(fd);
}

void print_time_to_file(int n, int m, int iterations, double elapsed) {

	char file_name[50];

	sprintf(file_name, "../output_time/GOL_%dx%d_%d", n, m, iterations);

	int fd = open(file_name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

	if(fd == -1)
		error("Error opening file to write.");

	char output[10];
	sprintf(output, "%f", elapsed);

	if(write(fd, output, strlen(output)) != strlen(output))
		error("Error writing execution time to file.");

	close(fd);
}