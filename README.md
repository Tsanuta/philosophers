# philosophers
3 programs to solve the [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)  

1. philo_one  
First approach using only mutexes and threads

2. philo_two  
Second approach using only semaphores and threads

3. philo_three  
Last approach using only semaphores and fork

### Context
This project was done as part of 42's Software Engineer program. Project was passed the 22nd January 2020.

### How to run

Launch the program
Use the Makefile to compile each program
```
make
```
Each program takes 4 arguments and one optional:
- arg1: number of philosophers
- arg2: time_to_die in milliseconds
- arg3: time_to_eat in milliseconds
- arg4: time_to_sleep in milliseconds
- arg5(optional): number of times the philosopher must eat before the program stops

To launch each program (philo_one for example):
```
./philo_one arg1 arg2 arg3 arg4 [arg5]
```
Tests used for the programs:
```
./philo_one 1 50 200 200 ""a""
./philo_one 1 50 200a 200
./philo_one 1 50a 200 200
./philo_one "1a" 50 200 200
./philo_one 0 200 200 200
./philo_one 1 400 200 200
./philo_one 1 200 200 200
./philo_one 2 410 200 200
./philo_one 4 410 200 200
./philo_one 4 410 200 000
./philo_one 4 310 200 100
./philo_one 4 399 200 200 10
./philo_one 4 400 200 200 10
./philo_one 4 310 200 200 10
./philo_one 4 310 200 100 2
./philo_one 4 310 200 100 1
./philo_one 5 800 200 200
./philo_one 5 310 200 100 0
./philo_one 5 310 200 100 1
./philo_one 5 800 200 200 7
./philo_one 5 600 200 200
./philo_one 5 800 2000 200
./philo_one 200 800 200 200
./philo_one 200 6000 200 200  
```
```
./philo_two 1 50 200 200 ""a""
./philo_two 1 50 200a 200
./philo_two 1 50a 200 200
./philo_two "1a" 50 200 200
./philo_two 0 200 200 200
./philo_two 1 400 200 200
./philo_two 1 200 200 200
./philo_two 2 410 200 200
./philo_two 4 410 200 200
./philo_two 4 410 200 000
./philo_two 4 310 200 100
./philo_two 4 399 200 200 10
./philo_two 4 400 200 200 10
./philo_two 4 310 200 200 10
./philo_two 4 310 200 100 2
./philo_two 4 310 200 100 1
./philo_two 5 800 200 200
./philo_two 5 310 200 100 0
./philo_two 5 310 200 100 1
./philo_two 5 800 200 200 7
./philo_two 5 600 200 200
./philo_two 5 800 2000 200
./philo_two 200 800 200 200
./philo_two 200 6000 200 200
```
```
./philo_three 1 50 200 200 ""a""
./philo_three 1 50 200a 200
./philo_three 1 50a 200 200
./philo_three "1a" 50 200 200
./philo_three 0 200 200 200
./philo_three 1 400 200 200
./philo_three 1 200 200 200
./philo_three 2 410 200 200
./philo_three 4 410 200 200
./philo_three 4 410 200 000
./philo_three 4 310 200 100
./philo_three 4 399 200 200 10
./philo_three 4 400 200 200 10
./philo_three 4 310 200 200 10
./philo_three 4 310 200 100 2
./philo_three 4 310 200 100 1
./philo_three 5 800 200 200
./philo_three 5 310 200 100 0
./philo_three 5 310 200 100 1
./philo_three 5 800 200 200 7
./philo_three 5 600 200 200
./philo_three 5 800 2000 200
./philo_three 200 800 200 200
./philo_three 200 6000 200 200
```
