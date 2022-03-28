# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define MAX_LINE_BUF 5
# define TRUE 1
# define MAX_CUSTOMER 50

int resource_num;

int customer_num;

int * available;

int ** maximum;

int ** allocation;

int ** need;


void initialization(int argc, char *argv[]);
void print_the_bank();
void get_the_need(int ** need, int ** maximum, int ** allocation);
int check_safe(void);
int request_resources(int customer_id, int request[]);
void release_resources(int customer_id, int release[]);


int main(int argc, char *argv[]) {
	initialization(argc, argv);

	print_the_bank();

	int res = check_safe();
	if (res) {
		fprintf(stdout, "Unsafe! Process terminates!\n");
		exit(1);
	}
	
	char op[MAX_LINE_BUF];
	int *arg = (int *) malloc (sizeof(int) * (1 + resource_num));
    int tmp;
    int pos;
    char ch;

	while(TRUE) {

		fprintf(stdout, "Banker >> ");
        fflush(stdout);
		
        scanf("%s",op);
        scanf("%c",&ch);

        pos = 0;

        while (ch != '\n' && scanf("%d", &tmp)) {
            arg[pos] = tmp;
            scanf("%c", &ch);
            pos++;
            if(ch == '\n')
                break;
        } 

		if (strcmp(op, "exit") == 0) break;
		else if (strcmp(op, "*") == 0) print_the_bank();
		else if (strcmp(op, "RQ") == 0 && pos == resource_num + 1) {
			if (request_resources(arg[0], arg + 1) == -1) fprintf(stdout, "Request command should be denied.\n");
			else fprintf(stdout, "Request command should be accepted.\n");
		}
		else if (strcmp(op, "RL") == 0 && pos == resource_num + 1) release_resources(arg[0], arg + 1);
		else {
			fprintf(stdout, "Wrong instruction!\n");
			continue;
		}
	}

	free(arg);
	
	free(available);
	for (int i = 0; i < customer_num; ++ i) {
		free(maximum[i]);
		free(allocation[i]);
		free(need[i]);
	}
	free(maximum);
	free(allocation);
	free(need);
	return 0;
}


// Initialize according to the input of command line
void initialization(int argc, char *argv[]) {	
	resource_num = argc - 1;

	available = (int *) malloc (sizeof(int) * resource_num);

	for (int i = 1; i < argc; ++ i)
		available[i - 1] = atoi(argv[i]);

	// initial graph of resource
	customer_num = 0;
	maximum = (int **) malloc (sizeof(int *) * MAX_CUSTOMER);

	FILE *fp = fopen("maximum.txt", "r");
	int data;	
	while(~fscanf(fp, "%d", &data)) {
		maximum[customer_num] = (int *) malloc (sizeof(int) * resource_num);
		maximum[customer_num][0] = data;
		for (int i = 1; i < resource_num; ++ i) {
			fscanf(fp, ",%d", &data);
			maximum[customer_num][i] = data;
		}
		customer_num ++;
	}
	fclose(fp);

	allocation = (int **) malloc (sizeof(int *) * customer_num);
	for (int i = 0; i < customer_num; ++ i)
		allocation[i] = (int *) malloc (sizeof(int) * resource_num);
	need = (int **) malloc (sizeof(int *) * customer_num);
	for (int i = 0; i < customer_num; ++ i)
		need[i] = (int *) malloc (sizeof(int) * resource_num);
	
	for (int i = 0; i < customer_num; ++ i)
		for (int j = 0; j < resource_num; ++ j) 
			allocation[i][j] = 0;
	
	get_the_need(need, maximum, allocation);
}


void print_the_bank() {
	fprintf(stdout, "Customer Number = %d\nResource Number = %d\n", customer_num, resource_num);
	fprintf(stdout, "Available = ");
	for (int i = 0; i < resource_num; ++ i)
		fprintf(stdout, "%d%c", available[i] , (i == resource_num - 1) ? '\n' : ' ');

	fprintf(stdout, "Maximum = \n");
	for (int i = 0; i < customer_num; ++ i) {
		for (int j = 0; j < resource_num; ++ j)
			fprintf(stdout, "%d%c", maximum[i][j], (j == resource_num - 1) ? '\n' : ' ');
	}
	
    fprintf(stdout, "Allocation = \n");
    for (int i = 0; i < customer_num; ++ i) {
        for (int j = 0; j < resource_num; ++ j)
            fprintf(stdout, "%d%c", allocation[i][j], (j == resource_num - 1) ? '\n' : ' ');
    }
	
    fprintf(stdout, "Need = \n");
    for (int i = 0; i < customer_num; ++ i) {
        for (int j = 0; j < resource_num; ++ j)
            fprintf(stdout, "%d%c", need[i][j], (j == resource_num - 1) ? '\n' : ' ');
    }
}


// Update the need matrix
void get_the_need(int ** need, int ** maximum, int ** allocation) {
	for (int i = 0; i < customer_num; ++ i)
		for (int j = 0; j < resource_num; ++ j)
			need[i][j] = maximum[i][j] - allocation[i][j];
}


// Check whether the initial state is safe
int check_safe(void) {
	// if maximum > initial avaible, unsafe.
	for (int i = 0; i < customer_num; ++ i)
		for (int j = 0; j < resource_num; ++ j)
			if(maximum[i][j] > available[j]) return 1;

	return 0;
}


int request_resources(int customer_id, int request[]) {
	int * available_t, * served;

	for (int i = 0; i < resource_num; ++ i) {
        if (request[i] > available[i]) {
			fprintf(stdout, "No enough available resources!\n");
			return -1;
        }
        if (request[i] > need[customer_id][i]) {
			fprintf(stdout, "The request should not be greater than need!\n");
			return -1;
		}
    }
	
	// if accept
	available_t = (int *) malloc (sizeof(int) * resource_num);
	served = (int *) malloc (sizeof(int) * customer_num);
	for (int i = 0; i < customer_num; ++ i)
		served[i] = 0;
	for (int i = 0; i < resource_num; ++ i) {
		available_t[i] = available[i] - request[i];
		allocation[customer_id][i] += request[i];
	}
	get_the_need(need, maximum, allocation);
	
	int res = 1;
	for (int k = 0; k < customer_num; ++ k) {		
		int p = -1;
		for (int i = 0; i < customer_num; ++ i) {
			if (served[i]) continue;
			int flag = 1;
			for (int j = 0; j < resource_num; ++ j)
				if (need[i][j] > available_t[j]) {
					flag = 0;
					break;
				}
			if (flag) {
				p = i;
				break;
			}
		}

		if(p == -1) {
			res = 0;
			break;
		}
		served[p] = 1;
		for (int i = 0; i < resource_num; ++ i)
			available_t[i] += allocation[p][i];
	}
	
	if (res) {
		fprintf(stdout, "Safe request!\n");
		for (int i = 0; i < resource_num; ++ i)
			available[i] -= request[i];
		free(available_t);
		free(served);
		return 0;
	} else {
		fprintf(stdout, "Unsafe request!\n");
        // roll back to unaccept
		for (int i = 0; i < resource_num; ++ i)
			allocation[customer_id][i] -= request[i];
		get_the_need(need, maximum, allocation);
		free(available_t);
		free(served);
		return -1;
	}
}


void release_resources(int customer_id, int release[]) {
	for (int i = 0; i < resource_num; ++ i)
		if (release[i] > allocation[customer_id][i]) {
			fprintf(stdout, "The release should not be greater than allocation!\n");
			return ;
		}
	for (int i = 0; i < resource_num; ++ i) {
		available[i] += release[i];
		allocation[customer_id][i] -= release[i];
	}
	get_the_need(need, maximum, allocation);
	fprintf(stdout, "The resources are released.\n");
	return ;
}
