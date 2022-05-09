#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TASK_NAME_LENGTH 20
#define SCHED_YES 1
#define SCHED_NO 2
#define SCHED_UNKNOWN 3

typedef struct task {
    char name[TASK_NAME_LENGTH];
    int period;
    int WCET;
    int priority;
    int deadline;
    struct task* next;
} task;

task* first_task = NULL;
task* last_task = NULL;

/* Allocate a task and add it to the end of the linked list */
void add_task(char* name, int period, int WCET, int priority, int deadline)
{
    task* new_task = (task*)malloc(sizeof(task));
    if (strlen(name) < TASK_NAME_LENGTH) {
        strcpy(new_task->name, name);
    }
    else {
        printf("The task name is too long.\n");
        exit(-1); // Exit with an error code
    }

    new_task->period = period;
    new_task->WCET = WCET;
    new_task->priority = priority;
    new_task->deadline = deadline;

    new_task->next = NULL;
    if (first_task == NULL && last_task == NULL) { // If this is the first task to be added
        first_task = new_task;
        last_task = new_task;
        return;
    }
    last_task->next = new_task;
    last_task = new_task;
}

/* Remove first task in the list */
void remove_first_task()
{
    task* temp = first_task;

    if (first_task == NULL) {
        printf("The task list is empty\n");
        return;
    }
    if (first_task == last_task) { // Exactly one task in the list
        first_task = NULL;
        last_task = NULL;
    }
    else { // Set first_task to be the second task in the list
        first_task = first_task->next;
    }
    free(first_task); // Deallocate the memory for the first task
}

/* Remove all tasks by iteratively removing the first task until the list is
   empty
*/
void remove_all_tasks()
{
    while (first_task != NULL) {
        remove_first_task();
    }
}

/* This function should return the number of tasks added to the system */
int nbr_of_tasks()
{
  int nbr_task = 0; // Define the initial number of task as zero
  task* curr_task = first_task; // Define the initial current task as the first task

  for (;curr_task != NULL;){ // Start the for loop when it has a value to assign
        nbr_task += 1 ; // Sum number of task at each loop
        curr_task = curr_task->next; // Set the current task as the next task in the list at respective loop
  }
	return nbr_task; // Return the number of tasks in the list
}

/* Print information about all tasks in the list
   Notice, how to iterate through all tasks in the list
*/
void print_tasks()
{
    task* curr_task = first_task;

    while (curr_task != NULL) {
        printf("Name: %s, period: %d, WCET: %d, priority %d, deadline: %d\n",
            curr_task->name, curr_task->period, curr_task->WCET,
            curr_task->priority, curr_task->deadline);
        curr_task = curr_task->next;
    }
}

/*
Test if the tasks is schedulable according to the critera by Liu and Layland.
Reference: C. L. Liu and J. Layland. Scheduling algorithms for multiprogramming
in a hard real-time environment, Journal of the ACM, 20(1), 1973, pp. 46-61.
Return:
   1: Yes, the tasks are schedulable (according to the criteria)
   2: No, the tasks are not schedulable
   3: The criteria cannot determine if the tasks are schedulable or not

Assumptions: Priorities are unique, the list of tasks contains at least one
task.
*/
int schedulable_Liu_Layland()
{
    double Utilisation_rate = 0; // Define the initial utilisation as double type with zero value
    double Number_of_Tasks = (double) nbr_of_tasks(); // Refer N as the number of tasks list
    double upper_bound = Number_of_Tasks*(pow(2,1/Number_of_Tasks)-1); // define upper bound as (N x (2^(1/N)-1))
    int schedulability = SCHED_YES; // Define initial schedulability as 1

    task* curr_task = first_task;

    for (;curr_task != NULL;) { // Start the while loop by incrementing the utilisation
        Utilisation_rate += ((double) curr_task->WCET / curr_task->period) ; // Define the calculation as sum of (Calculation time over Period) vector
        curr_task = curr_task->next;
    }

    int Liu_Layland_test = (Utilisation_rate <= upper_bound ); // Define that Passed test as when utilisation rate is less than or equal to the bound
                                                               
    if( Liu_Layland_test != 1 ){ // if we have the result of Utilisation rate > upper_bound, define schedulability as unknown 
        schedulability = SCHED_UNKNOWN;
    }

    return schedulability;
}

/*
Test if the tasks is schedulable according to the exact response time analysisnd
Layland.
Return:
   1: Yes, the tasks are schedulable (according to the criteria)
   2: No, the tasks are not schedulable
   3: The criteria cannot determine if the tasks are schedulable or not

Assumptions: Priorities are unique, the list of tasks contains at least one
task.
*/
int schedulable_response_time_analysis()
{
    int schedulability = SCHED_YES; // Initial definition of schedulability as 1
    int w_i_n; // Definition of the w_n at the current iteration (i) in the task set

    task* curr_task = first_task; // Initialize the curr_task

    for (;curr_task != NULL;){ 
        
        int w_updated = curr_task->WCET; // Initialize the response time as the current task's computation time

        for (w_i_n = 0; w_i_n != w_updated;){ // Keep the iteration of the w_n vector as long as the updated iteration
                                              // value is different than its previous iteration value
            w_i_n = w_updated; // Update the current iteration of w with previous iteration of w

            w_updated = curr_task->WCET; // Initialize w as the current task's computation time

            task* higher_priority_task = first_task;// Define the initial higher priority task as the first task in the current task set

            for (;higher_priority_task != NULL;){

                if (higher_priority_task->priority > curr_task->priority){
                    w_updated += ceil((double)w_i_n/higher_priority_task->period) * higher_priority_task->WCET;
                } // Calculate the sum of the (ceiling function) when there is any higher priority task compared to current task

                higher_priority_task = higher_priority_task->next; // Update the priority of the current task
            }
        }
        int final_response_time = w_updated; // Define the final response time of the task

        if (final_response_time > curr_task->deadline){
            schedulability = SCHED_NO;
        }// Define the schedulability as SCHED_NO (0) when the response time is higher than the deadline time

        curr_task = curr_task->next; // Update the current task with the next task
    }
    return schedulability;
}

int check_schedulable(int correct_response_Liu_Layland,
    int correct_response_response_time_analysis)
{
    int nbr_of_failed_tests = 0;
    if (schedulable_Liu_Layland() != correct_response_Liu_Layland) {
        nbr_of_failed_tests++;
        printf("\n=== Schedulable test failed: Liu-Layland\n");
        print_tasks();
        printf("===\n");
    }

    if (schedulable_response_time_analysis() != correct_response_response_time_analysis) {
        nbr_of_failed_tests++;
        printf("\n=== Schedulable test failed: Response-Time Analysis\n");
        print_tasks();
        printf("===\n");
    }
    return nbr_of_failed_tests;
}

/* Do not change or remove any code in this function.
   If you like you can add additional test cases.
   TODO
*/
int check_tests()
{
    int nbr_of_failed_tests = 0;

    remove_all_tasks();

    // Add test
    // add_task(name, period, WCET, priority, deadline)
    add_task("T1", 25, 10, 5, 25);
    add_task("T2", 25, 8, 4, 25);
    add_task("T3", 50, 5, 3, 50);
    add_task("T4", 50, 4, 2, 50);
    add_task("T5", 100, 2, 1, 100);

    nbr_of_failed_tests += check_schedulable(SCHED_UNKNOWN, SCHED_YES); // 1st test schedulability correct result

    remove_all_tasks();
    // Add test
    add_task("T1", 50, 12, 1, 50);
    add_task("T2", 40, 10, 2, 40);
    add_task("T3", 30, 10, 3, 50);

    nbr_of_failed_tests += check_schedulable(SCHED_UNKNOWN, SCHED_NO); // 2nd test schedulability result

    remove_all_tasks();
    // Add test
    add_task("T1", 80, 12, 1, 50);
    add_task("T2", 40, 10, 2, 40);
    add_task("T3", 20, 10, 3, 50);

    nbr_of_failed_tests += check_schedulable(SCHED_UNKNOWN, SCHED_NO); // 3rd test schedulability result

    remove_all_tasks();
    // Add test
    add_task("T1", 7, 3, 3, 7);
    add_task("T2", 12, 3, 2, 12);
    add_task("T3", 20, 5, 1, 20);

    nbr_of_failed_tests += check_schedulable(SCHED_UNKNOWN, SCHED_YES); // 4th test schedulability result

    remove_all_tasks();
    // Add test
    add_task("T1", 7, 3, 3, 3);
    add_task("T2", 12, 3, 2, 6);
    add_task("T3", 20, 5, 1, 20);

    nbr_of_failed_tests += check_schedulable(SCHED_UNKNOWN, SCHED_YES); // 5th test schedulability result

    return nbr_of_failed_tests;
}

int main()
{
    int nbr_of_failed_tests = check_tests();
    printf("\n=== Total number of failed tests: %d\n", nbr_of_failed_tests);
    return 0;
}
