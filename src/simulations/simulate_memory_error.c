// File: src/simulations/simulate_memory_error.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_handler.h"

// Function to simulate a memory leak
void simulate_memory_leak() {
    printf("Simulating memory leak...\n");
    while (1) {
        malloc(1024 * 1024); // Allocate 1MB without freeing
        sleep(1);
    }
}

// Function to simulate a segmentation fault
void simulate_segmentation_fault() {
    printf("Simulating segmentation fault...\n");
    int *ptr = NULL;
    *ptr = 42; // Dereference NULL pointer
}

// Function to simulate a null pointer dereference
void simulate_null_pointer_deref() {
    printf("Simulating null pointer dereference...\n");
    int *ptr = NULL;
    if (ptr) {
        *ptr = 100;
    } else {
        printf("Attempted to dereference a null pointer.\n");
        handle_error(NULL_ERROR, "Null pointer dereference detected.", 0);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <leak|segfault|null>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "leak") == 0) {
        simulate_memory_leak();
    } else if (strcmp(argv[1], "segfault") == 0) {
        simulate_segmentation_fault();
    } else if (strcmp(argv[1], "null") == 0) {
        simulate_null_pointer_deref();
    } else {
        printf("Unknown simulation type.\n");
        return 1;
    }

    return 0;
}