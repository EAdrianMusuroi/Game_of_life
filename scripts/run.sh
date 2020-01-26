rm /home/adrian/Documents/PA/Project/output/*

gcc -Wall -fopenmp -o /home/adrian/Documents/PA/Project/open_mp_game_of_life_1D /home/adrian/Documents/PA/Project/open_mp_game_of_life_1D.c
gcc -Wall -fopenmp -o /home/adrian/Documents/PA/Project/game_of_life /home/adrian/Documents/PA/Project/game_of_life.c

##############################################################################################################
# Game of life, no parallelization

echo "Running GOL with 50x50 matrix and 50 iterations..."
/home/adrian/Documents/PA/Project/game_of_life 50 50 50 /home/adrian/Documents/PA/Project/input/input_size_50

echo "Running GOL with 50x50 matrix and 500 iterations..."
/home/adrian/Documents/PA/Project/game_of_life 50 50 500 /home/adrian/Documents/PA/Project/input/input_size_50

echo "Running GOL with 50x50 matrix and 1000 iterations..."
/home/adrian/Documents/PA/Project/game_of_life 50 50 1000 /home/adrian/Documents/PA/Project/input/input_size_50



echo "Running GOL with 150x150 matrix and 50 iterations..."
/home/adrian/Documents/PA/Project/game_of_life 150 150 50 /home/adrian/Documents/PA/Project/input/input_size_150

echo "Running GOL with 150x150 matrix and 500 iterations..."
/home/adrian/Documents/PA/Project/game_of_life 150 150 500 /home/adrian/Documents/PA/Project/input/input_size_150

echo "Running GOL with 150x150 matrix and 1000 iterations..."
/home/adrian/Documents/PA/Project/game_of_life 150 150 1000 /home/adrian/Documents/PA/Project/input/input_size_150



echo "Running GOL with 500x500 matrix and 50 iterations..."
/home/adrian/Documents/PA/Project/game_of_life 500 500 50 /home/adrian/Documents/PA/Project/input/input_size_500

echo "Running GOL with 500x500 matrix and 500 iterations..."
/home/adrian/Documents/PA/Project/game_of_life 500 500 500 /home/adrian/Documents/PA/Project/input/input_size_500

echo "Running GOL with 500x500 matrix and 1000 iterations..."
/home/adrian/Documents/PA/Project/game_of_life 500 500 1000 /home/adrian/Documents/PA/Project/input/input_size_500


##############################################################################################################
# Game of life, OpenMP 1D decomposition

echo "Running OMP_1D with 50x50 matrix and 50 iterations..."
/home/adrian/Documents/PA/Project/open_mp_game_of_life_1D 50 50 50 /home/adrian/Documents/PA/Project/input/input_size_50

echo "Running OMP_1D with 50x50 matrix and 500 iterations..."
/home/adrian/Documents/PA/Project/open_mp_game_of_life_1D 50 50 500 /home/adrian/Documents/PA/Project/input/input_size_50

echo "Running OMP_1D with 50x50 matrix and 1000 iterations..."
/home/adrian/Documents/PA/Project/open_mp_game_of_life_1D 50 50 1000 /home/adrian/Documents/PA/Project/input/input_size_50


echo "Running OMP_1D with 150x150 matrix and 50 iterations..."
/home/adrian/Documents/PA/Project/open_mp_game_of_life_1D 150 150 50 /home/adrian/Documents/PA/Project/input/input_size_150

echo "Running OMP_1D with 150x150 matrix and 500 iterations..."
/home/adrian/Documents/PA/Project/open_mp_game_of_life_1D 150 150 500 /home/adrian/Documents/PA/Project/input/input_size_150

echo "Running OMP_1D with 150x150 matrix and 1000 iterations..."
/home/adrian/Documents/PA/Project/open_mp_game_of_life_1D 150 150 1000 /home/adrian/Documents/PA/Project/input/input_size_150


echo "Running OMP_1D with 500x500 matrix and 50 iterations..."
/home/adrian/Documents/PA/Project/open_mp_game_of_life_1D 500 500 50 /home/adrian/Documents/PA/Project/input/input_size_500

echo "Running OMP_1D with 500x500 matrix and 500 iterations..."
/home/adrian/Documents/PA/Project/open_mp_game_of_life_1D 500 500 500 /home/adrian/Documents/PA/Project/input/input_size_500

echo "Running OMP_1D with 500x500 matrix and 1000 iterations..."
/home/adrian/Documents/PA/Project/open_mp_game_of_life_1D 500 500 1000 /home/adrian/Documents/PA/Project/input/input_size_500