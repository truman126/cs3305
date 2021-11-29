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
    char *actions[100];
    int num_actions;
};
typedef struct arg_struct
{
    int client_number;
    struct client *client_ptr;
    struct account *account_ptr;
    int account_number;

} arg;

struct account accounts[0];
struct client clients[0];

void *transact_client(void *argc)
{
    int i = 0;
    arg *thread_data = (arg *)argc;
    int client_number = thread_data->client_number;
    int account_number;

    while ((thread_data->client_ptr[client_number].actions[i] != NULL) && ((strcmp(thread_data->client_ptr[client_number].actions[i], "d") == 0) || (strcmp(thread_data->client_ptr[client_number].actions[i], "w") == 0)))
    {

        //find account number
        int j = 0;
        for (j = 0; j < thread_data->account_number; j++)
        {
            if (strcmp(thread_data->account_ptr[j].name, thread_data->client_ptr[client_number].actions[i + 1]) == 0)
            {
                account_number = j;
            }
        }
        

        //check semaphore

        while (1)
        {
            if (thread_data->account_ptr[account_number].semaphore == 0)
            {
                break;
            }
        }

        //client leaves waiting period, able to
        //CRITICAL SECTION BEGINS / SET SEMAPHORE TO 1
        thread_data->account_ptr[account_number].semaphore = 1;

        //printf("type: %s. acc: %s. amount: %s\n", thread_data->client_ptr[client_number].actions[i], thread_data->client_ptr[client_number].actions[i+1], thread_data->client_ptr[client_number].actions[i+2]);

        if (strcmp(thread_data->client_ptr[client_number].actions[i], "d") == 0)
        {
            thread_data->account_ptr[account_number].balance += atoi(thread_data->client_ptr[client_number].actions[i + 2]);
            
        }
        else if (strcmp(thread_data->client_ptr[client_number].actions[i], "w") == 0)
        {
           
            if (thread_data->account_ptr[account_number].balance >= atoi(thread_data->client_ptr[client_number].actions[i + 2]))
            {
                thread_data->account_ptr[account_number].balance -= atoi(thread_data->client_ptr[client_number].actions[i + 2]);
            }
        }

        //CRITICAL SECTION ENDS / SET SEMAPHORE TO 0
        thread_data->account_ptr[account_number].semaphore = 0;
        i += 3;
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

    fclose(file);

    // CREATE ACCOUNT AND CLIENT STRUCTS

    struct account accounts[num_accounts];
    struct client clients[num_clients];
    int account_number = 0;
    
    for (i = 0; i < num_accounts * 3; i += 3)
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
                clients[client_number].actions[j] = NULL;

                break;
            }
        }
        client_number++;
    }

    // for each client, open a new thread
    pthread_t thread[num_clients];
    int k = 0;
    for (k = 0; k < num_clients; k++)
    {
        arg thread_data;
        thread_data.client_number = k;
        thread_data.client_ptr = clients;
        thread_data.account_ptr = accounts;
        thread_data.account_number = num_accounts;
        pthread_create(&thread[k], NULL, transact_client, &thread_data);
        
    }

    //close all the threads
    for (k = 0; k < num_clients; k++)
    {
        pthread_join(thread[k], NULL);

    }


    //print details at the end

    for (k = 0; k < num_accounts; k++)
    {
        printf("%s b %d\n\n", accounts[k].name, accounts[k].balance);
    }
    return 1;
}
