#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

# define MAX_HOLE_NUM 50
# define MAX_PROCESS_ID 8
# define MAX_NUM 1000000000

typedef struct {
    bool use;
    int start;
    int end;
    int size;
    char process[MAX_PROCESS_ID];
} hole;

bool request(char process[], int request_size, char strategy);
void release(char process[]);
void compact();
void state();

hole memory[MAX_HOLE_NUM];
int length = 0;
char op[5];

int main(int argc, char *argv[]) {
    int size = atoi(argv[1]);
    char process[MAX_PROCESS_ID];
    int request_size;
    char strategy;

    memory[0].use = false;
    memory[0].start = 0;
    memory[0].end = size - 1;
    memory[0].size = size;
    ++length;

    for (int i = 1; i < MAX_HOLE_NUM; ++i)
        memory[i].use = false;

    while (true) {
        printf("allocator> ");
        fflush(stdout);

        scanf("%s", op);
        if (strcmp(op, "X") == 0)
            break;
        else if (strcmp(op, "RQ") == 0) {
            scanf(" %s %d %ch", process, &request_size, &strategy);
            request(process, request_size, strategy);
        }
        else if (strcmp(op, "RL") == 0) {
            scanf(" %s", process);
            release(process);
        }
        else if (strcmp(op, "C") == 0)
            compact();
        else if (strcmp(op, "STAT") == 0)
            state();
        else
            printf("Wrong instruction!\n");
    }
    return 0;
}

bool request(char process[], int request_size, char strategy) {
    int index = 0;
    int i;
    bool flag = false;

    if (strategy == 'F') {
        for (i = 0; i < length; ++i)
            if (!memory[i].use && memory[i].size >= request_size) {
                flag = true;
                break;
            }
        index = i;
    }
    else if (strategy == 'B') {
        int min = MAX_NUM;
        for (i = 0; i < length; ++i)
            if (!memory[i].use && memory[i].size >= request_size && memory[i].size < min) {
                flag = true;
                index = i;
                min = memory[i].size;
            }
    }
    else if (strategy == 'W') {
        int max = 0;
        for (i = 0; i < length; ++i)
            if (!memory[i].use && memory[i].size >= request_size && memory[i].size > max) {
                flag = true;
                index = i;
                max = memory[i].size;
            }
    }
    else {
        printf("Wrong strategy!\n");
        return false;
    }

    if (!flag) {
        printf("Allocation fails!\n");
        return false;
    }

    // the chosen hole fits perfectly, allocation ends
    if (memory[index].size == request_size) {
        strcpy(memory[index].process, process);
        memory[index].use = true;
        return true;
    }

    // more than one holes occurrs, move forward
    for (i = length - 1; i >= index; --i) {
        memory[i + 1].use = memory[i].use;
        memory[i + 1].start = memory[i].start;
        memory[i + 1].end = memory[i].end;
        memory[i + 1].size = memory[i].size;
        strcpy(memory[i + 1].process, memory[i].process);
    }
    ++length;
    memory[index].use = true;
    memory[index].end = memory[index].start + request_size - 1;
    memory[index].size = request_size;
    strcpy(memory[index].process, process);
    memory[index + 1].start = memory[index].end + 1;
    memory[index + 1].size = memory[index + 1].end - memory[index + 1].start + 1;
    return true;
}

void release(char process[]) {
    int index;
    bool flag = false;
    for (int i = 0; i < length; ++i)
        if (memory[i].use && strcmp(process, memory[i].process) == 0) {
            flag =true;
            index = i;
            break;
        }
    if (!flag) {
        printf("No such a process!\n");
        return;
    }

    memory[index].use = false;
    // eat holes behind
    if (index < length - 1 && !memory[index + 1].use) {
        memory[index].end = memory[index + 1].end;
        memory[index].size += memory[index + 1].size;
        for (int i = index + 1; i < length; ++i) {
            memory[i].use = memory[i + 1].use;
            memory[i].start = memory[i + 1].start;
            memory[i].end = memory[i + 1].end;
            memory[i].size = memory[i + 1].size;
            strcpy(memory[i].process, memory[i + 1].process);
        }
        --length;
    }

    // eat holes forward
    if (index >= 1 && !memory[index - 1].use) {
        memory[index - 1].end = memory[index].end;
        memory[index - 1].size += memory[index].size;
        for (int i = index; i < length; i++) {
            memory[i].use = memory[i + 1].use;
            memory[i].start = memory[i + 1].start;
            memory[i].end = memory[i + 1].end;
            memory[i].size = memory[i + 1].size;
            strcpy(memory[i].process, memory[i + 1].process);
        }
        --length;
    }
}

void compact() {
    int used_hole_index[MAX_HOLE_NUM];
    int used_num = 0;
    int unused_space = 0;
    for (int i = 0; i < length; ++i) {
        if (memory[i].use) {
            used_hole_index[used_num] = i;
            ++used_num;
        }
        else
            unused_space += memory[i].size;
    }

    if (used_num == 0) return;

    // compact
    for (int i = 0; i < used_num; i++) {
        memory[i].use = true;
        memory[i].start = i > 0 ? memory[i - 1].end + 1 : 0;
        memory[i].end =  memory[i].start + memory[used_hole_index[i]].size - 1;
        memory[i].size = memory[used_hole_index[i]].size;
        strcpy(memory[i].process, memory[used_hole_index[i]].process);
    }

    memory[used_num].use = false;
    memory[used_num].start = memory[used_num - 1].end + 1;
    memory[used_num].end = memory[used_num].start + unused_space - 1;
    memory[used_num].size = unused_space;

    // initialize the other space
    for (int i = used_num + 1; i < MAX_HOLE_NUM; i++)
        memory[i].use = false;
    length = used_num + 1;
}

void state() {
    for (int i = 0; i < length; ++i) {
        if (memory[i].use)
            printf("Addresses [%d:%d] Process %s\n", memory[i].start, memory[i].end, memory[i].process);
        else
            printf("Addresses [%d:%d] Unused\n", memory[i].start, memory[i].end);
    }
}