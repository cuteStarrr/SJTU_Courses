# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "task.h"
# include "list.h"
# include "cpu.h"
# include "schedulers.h"

struct node *tasks = NULL;

int now_time = 0;
int totalwait_time = 0;
int totalresponse_time = 0;
int totalturn_time = 0;
int tasks_num = 0;


void add(char *name, int priority, int burst) {
    Task *new_task;
    new_task = (Task *) malloc (sizeof(Task));
    new_task -> tid = __sync_fetch_and_add(&tid_global, 1);
	new_task -> name = (char *) malloc (sizeof(char) * (1 + strlen(name)));
	strcpy(new_task -> name, name);
	new_task -> priority = priority;
	new_task -> burst = burst;
	new_task -> starting_time = now_time;
	new_task -> last_time = now_time;
	new_task -> waiting_time = 0;
	new_task -> response_time = 0;
	new_task -> turn_time = 0;
	insert(&tasks, new_task);
}


void schedule() {
    while(tasks != NULL) {
        struct node *point = tasks;
        struct node *compare = tasks -> next;
        while(compare != NULL) {
            if (compare -> task -> priority >= point -> task -> priority) 
                point = compare;
            compare = compare -> next;
        }

        Task *chosen = point -> task;
        run(chosen, chosen -> burst);
        delete(&tasks, chosen);

        now_time += chosen -> burst;
        int last_wait = now_time - chosen -> last_time - chosen -> burst;
        chosen -> waiting_time += last_wait;
        if(chosen -> last_time == chosen -> starting_time)
            chosen -> response_time = last_wait;
        chosen -> last_time = now_time;
        chosen -> turn_time = now_time - chosen -> starting_time;

        tasks_num++;
        totalwait_time += chosen -> waiting_time;
        totalresponse_time += chosen -> response_time;
        totalturn_time += chosen -> turn_time;

        /* free memory */
        free(chosen -> name);
        free(chosen);
    }

    printf("There are %d tasks using Priority.\n", tasks_num);
    double Avwait_time = 1.0 * totalwait_time / tasks_num;
    double Avresponse_time = 1.0 * totalresponse_time / tasks_num;
    double Avturn_time = 1.0 * totalturn_time / tasks_num;
    printf("Average waiting time: %.6lf\n", Avwait_time);
    printf("Average response time: %.6lf\n", Avresponse_time);
    printf("Average turnaround time: %.6lf\n", Avturn_time);
    return ;

}