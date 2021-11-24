/**
 * Truman Johnston, tjohn54
 * Assignment 5, CS3305
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

struct account
{
    char name[4];
    int balance;
    int semaphore;
};

struct client
{
    char name[4];
    char *actions[1024];
    int num_actions;
};
typedef struct arg_struct
{
    int client_number;
    struct client *client_ptr;
    struct account *account_ptr;

} arg;


struct account accounts[];
struct client clients[];



int find_account_index(char *account_name)
{

    int i = 0;

    while (accounts[i].name != NULL)
    {
        if (accounts[i].name == account_name)
            return i;

        i++;
    }
}

void *transact_client(void *argc)
{
    int i = 0;
    arg *thread_data  = (arg*)argc;
    int client_number = thread_data->client_number;



    printf("thread data test: %d\n", thread_data->client_number);

    while((strcmp(thread_data->client_ptr[client_number].actions[i], "d") == 0) || (strcmp(thread_data->client_ptr[client_number].actions[i], "w") == 0)){
    printf("thread data name: %s\n", thread_data->client_ptr[client_number].actions[i]);
        
        i++;
        printf("account to edit: %s\n", thread_data->client_ptr[client_number].actions[i++]);
        printf("amount: %s\n", thread_data->client_ptr[client_number].actions[i++]);



    }
    return 0;

}

int main()
{

    // parse the input file

    FILE *file = fopen("assignment_6_input.txt", "r");
    char line[512];
    char *array[100];

    int num_accounts = 0;
    int num_clients = 0;

    int i = 0;

    // splits up each line into a master array
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\r\n")] = 0;

        if (line[0] == 'a')
            num_accounts++;
        else if (line[0] == 'c')
            num_clients++;

        char *token = strtok(line, " ");

        while (token != NULL)
        {
            array[i] = malloc(strlen(token));
            strcpy(array[i], token);

            token = strtok(NULL, " ");
            i++;
        }
    }

    // CREATE ACCOUNT AND CLIENT STRUCTS

    struct account accounts[num_accounts];
    struct client clients[num_clients];
    int account_number = 0;

    for (int i = 0; i < num_accounts * 3; i += 3)
    {
        strcpy(accounts[account_number].name, array[i]);
        accounts[account_number].balance = atoi(array[i + 2]);
        accounts[account_number].semaphore = 0;

        account_number++;
    }

    i = num_accounts * 3;

    int client_number = 0;
    while (num_clients > client_number)
    {

        strcpy(clients[client_number].name, array[i++]);
        clients[client_number].num_actions = 0;

        int j = 0;
        while (1)
        {

            if ((strcmp(array[i], "d") == 0) || (strcmp(array[i], "w") == 0))
            {

                clients[client_number].actions[j] = malloc(sizeof(array[i]));
                strcpy(clients[client_number].actions[j++], array[i++]);

                clients[client_number].actions[j] = malloc(sizeof(array[i]));
                strcpy(clients[client_number].actions[j++], array[i++]);

                clients[client_number].actions[j] = malloc(sizeof(array[i]));
                strcpy(clients[client_number].actions[j++], array[i++]);

                clients[client_number].num_actions++;
            }
            else
            {

                break;
            }
        }
        client_number++;
    }

    // for each client, open a new process
    pthread_t thread;
    i = 0;
    printf("&&client test: '%s'\n", clients[0].actions[0]);
    printf("&&account test: '%s'\n", accounts[0].name);
    printf("&&account test: '%d'\n", accounts[0].balance);
    arg thread_data;
    thread_data.client_number = 1;
    thread_data.client_ptr = clients;
    pthread_create(&thread, NULL, transact_client, &thread_data);
    pthread_join(thread, NULL);


    while (num_clients > i)
    {
        
        // pthread_join(thread, NULL);
        i++;    
        
    }
    // pthread_create(&thread_1, NULL, sum, thread_id_1); //thread 100
    // pthread_join(thread_1, NULL);
    // printf()

    fclose(file);
    return 1;
}