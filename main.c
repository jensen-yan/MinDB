#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
}InputBuffer;

InputBuffer *new_input_buffer() {
    InputBuffer *inputBuffer = malloc(sizeof(InputBuffer));
    inputBuffer->buffer = NULL;
    inputBuffer->buffer_length = 0;
    inputBuffer->input_length = 0;

    return inputBuffer;
}

void print_promt() {
    printf("db > ");
}

void read_input(InputBuffer *inputBuffer) {
//    ssize_t bytes_read = getline(&(inputBuffer->buffer), )
    inputBuffer->buffer = malloc(1000);
    gets(inputBuffer->buffer);
}


void close_input_buffer(InputBuffer *inputBuffer) {
    free(inputBuffer->buffer);
    free(inputBuffer);
}

int main() {
    InputBuffer* input_buffer = new_input_buffer();
    while (true){
        print_promt();
        read_input(input_buffer);

        if(strcmp(input_buffer->buffer, ".exit") == 0){
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        }else{
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
    }
}
