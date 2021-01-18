#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
}InputBuffer;

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
}MetaCommandResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
}PrepareResult;

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
}StatementType;

typedef struct {
    StatementType type;
}Statement;

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

MetaCommandResult do_meta_command(InputBuffer *input_buffer) {
    if(strcmp(input_buffer->buffer, ".exit") == 0){
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    } else{
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement) {
    if(strncmp(input_buffer->buffer, "insert", 6) == 0){
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if(strncmp(input_buffer->buffer, "select", 6) == 0){
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement) {
    switch (statement->type) {
        case STATEMENT_SELECT:
            printf("todo select\n");
            break;
        case STATEMENT_INSERT:
            printf("todo insert\n");
            break;
    }
}

int main() {
    InputBuffer* input_buffer = new_input_buffer();
    while (true){
        print_promt();
        read_input(input_buffer);

        if(input_buffer->buffer[0] == '.'){
            switch (do_meta_command(input_buffer)) {
                case(META_COMMAND_SUCCESS):
                    continue;
                case(META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'.\n",
                           input_buffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case(PREPARE_SUCCESS):
                break;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'.\n",
                       input_buffer->buffer);
                continue;
        }

        execute_statement(&statement);
        printf("Executed.\n");
    }
}
