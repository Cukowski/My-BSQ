# Welcome to My Bsq
***
Introducing my_bsq, a high-performance C program designed for finding and printing the largest square on a given board, all while minimizing memory usage and runtime. 

## Task
Our task is to implement a solution that efficiently tackles the challenge of identifying the largest square on a board filled with obstacles. 
We should ensure our implementation is fast, memory-efficient, and capable of handling diverse board sizes.

### Problem Statement:
* Our task is to locate the largest square on a board filled with obstacles represented by 'o', ensuring optimal performance in terms of speed and memory usage. 
* The board is read from a file specified as a program argument, adhering to specific constraints. The board's first line indicates the number of lines present, and subsequent lines consist of only '.' (empty space) and 'o' (obstacle) characters. 
* All lines, except the first one, are of equal length, and each line is terminated by '\n'. The challenge lies in efficiently identifying the largest square on the board without compromising on speed or memory efficiency.

### Solution Highlights:
* This algorithmic solution is tailored to strike the perfect balance between speed and memory usage. 
* It rapidly identifies the largest square on the board, replacing the corresponding '.' with 'x' to visually represent the discovered square.

### Key Features:
* Efficiency: Achieve optimal performance with a focus on both speed and memory usage.
* Scalability: Scale seamlessly to handle varying board sizes while maintaining efficiency.
* Precision: Accurately locate and visualize the largest square on the board.

## Description
1. The program takes the argument which is given and checks for the size of the table map. 
Knowing the size and suitabelty of the map, find_biggest_square function called.

### Implementation Details:
* Efficiently parse the input board file.
* Dynamically identify the largest square on the board.
* Replace appropriate '.' characters with 'x' to represent the discovered square.
* Output the modified board with the identified square.

## Installation
* Only make command is necessary. You can use '$> make' '$> make re' '$> make clean' '$> make fclean'
* There is no other installation needed.

## Usage
After using the make command, call the function and give the desired map to process.

```
./my_bsq [file.txt]
./my_bsq map/1000x1000
./my_bsq map/500x500
./my_bsq map/100x100
./my_bsq map/10x10  

```

### The Core Team
Adrian Sardinata (sardinat_a), Selcuk Aksoy (aksoy_s)

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
