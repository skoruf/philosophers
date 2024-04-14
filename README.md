This program deals with the dining philosophers problem: https://en.wikipedia.org/wiki/Dining_philosophers_problem

It is about designing an efficient way of sharing resources in multiple threads. Each philosopher is represented with
a thread, the shared resources (forks) are mutexes.

The program inputs are:

- number of philosophers (limited to 200)
- time_to_die: time a philosopher has to start eating before he starves
- time_to_eat: time spent eating
- time_to_sleep: time spent sleeping after the eating process is finished
- (optional) number of meals: if set, the program will stop once every philosopher ate at least n number of times

The status of every philosopher is printed to console as follows: 
'time in ms since start' 'philosopher id starting with 1' 'status message'

Ideally, philosophers should not die. If however a philosopher dies, the program stops.
