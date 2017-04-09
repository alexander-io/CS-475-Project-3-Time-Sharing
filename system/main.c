/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5	//number of philosophers and forks

// locks must be declared and initialized here
mutex_t locks[N]; // c initializes global scope array index values to 0, FALSE is an alias to 0
mutex_t print_lock[1]; //
mutex_t iff[1];
/**
 * Delay for a random amount of time
 * @param alpha delay factor
 */
void	holdup(int32 alpha)
{
	long delay = rand() * alpha;
	while (delay-- > 0)
		;	//no op
}

/**
 * Eat for a random amount of time
 */
void	eat()
{
	holdup(10000);
}

/**
 * Think for a random amount of time
 */
void	think()
{
	holdup(1000);
}



/**
 * Philosopher's code
 * @param phil_id philosopher's id
 */
void	philosopher(uint32 phil_id)
{
	srand(phil_id);
	uint32 right = (phil_id+N-1)%N;				// right fork
	uint32 left = phil_id;	//  left fork
	int r; // declare random integer variable used for 30/70% comparison
	while (TRUE)
	{
		// 70/30
		r = rand()%10;
		if (TRUE){
			mutex_lock(&locks[right]); // locks[(phil_id+N-1)%N];
			// mutex_lock(&locks[left]);

			/*place new lock here*/
			mutex_lock(&iff[0]);

			// if philosopher can only obtain one fork but not the other,
			// you must release the fork that you acquired
			if (locks[left]/*left is acquired*/){
				/*, then release right one & do nothing & loop back*/
				mutex_unlock(&iff[0]);
				mutex_unlock(&locks[right]);


				// continue;
			} else {
				/*acquire lock & eat*/
				mutex_lock(&locks[left]);
				mutex_lock(&print_lock[0]);
				printf("Philosopher %d eating : nom nom nom\n", phil_id);
				mutex_unlock(&print_lock[0]);

				eat();
				/*place new lock here*/


				mutex_unlock(&locks[left]);
				mutex_unlock(&iff[0]);
				mutex_unlock(&locks[right]);
			}

			// /*place new lock here*/
			// mutex_unlock(&iff[0]);


		} //eat 30% of the time
		else {

			mutex_lock(&print_lock[0]);
			printf("Philosopher %d thinking : zzzzzZZZz\n", phil_id);
			mutex_unlock(&print_lock[0]);

			think();
		} //think 70% of the time
	}
}

int	main(uint32 argc, uint32 *argv)
{
	//do not change
	ready(create((void*) philosopher, INITSTK, 15, "Ph1", 1, 0), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph2", 1, 1), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph3", 1, 2), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph4", 1, 3), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph5", 1, 4), FALSE);

	return 0;
}
