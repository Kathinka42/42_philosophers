# 42 Philosophers

## Introduction
42 Philosophers is a concurrent programming project that challenges students to solve the dining philosophers problem using multithreading concepts and synchronization mechanisms. The goal is to implement a solution where philosophers (threads) can peacefully share a meal without conflicting with each other.

## Features
- **Concurrency Management**: Implementing a solution using threads for each philosopher.
- **Mutex**: Using mutex locks for synchronization.
- **Timed Actions**: Handling time-related actions such as eating, sleeping, and thinking.
- **Error Handling**: Managing edge cases and errors gracefully.

## Requirements
- C programming language
- POSIX Threads library

## Installation and Usage
1. Clone the repository: `git clone https://github.com/Kathinka42/42_philosophers.git`
2. Compile the project: `make`
3. Run the application: `./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philosopher_must_eat]`

## Example Usage
```bash
./philo 5 800 200 200
