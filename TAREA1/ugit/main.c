#include <stdio.h>
#include <string.h>
#include "git.c"

/**
 * @file main.c
 * @brief Función principal de la aplicación µGit.
 *
 * Esta función inicializa la consola de comandos para µGit y maneja
 * la entrada del usuario en un bucle continuo hasta que se ingresa
 * el comando "git--exit".
 *
 * Autores:
 * - Constanza Araya
 * - Mario Calbuayhue
 *
 * @return 0 si la ejecución fue exitosa.
 */
int main() {
    char comando[MAX_COMANDO]; ///< Buffer para almacenar el comando ingresado.
    char *result; ///< Variable para almacenar el resultado de fgets.

    printf("Bienvenido a µGit\n");

    // Bucle prompt de la consola
    while (1) 
    {
        printf("ugit> "); 
        
        // Leer el comando y verificar si se ha leido correctamente
        result = fgets(comando, MAX_COMANDO, stdin);
        if(result != NULL)
        {
            printf("\n");
        }
        else
        {
            printf("Error al leer el comando.\n");
            continue;
        }

        // Remover el salto de linea al final de la entrada
        comando[strcspn(comando, "\n")] = 0;

        // Dividir una parte en el comando y la otra para tomar el mensaje al poner commit -m
        char *token = strtok(comando, " ");
        if (token == NULL)
        {
            continue;
        } 

        // Verificar comandos y en caso de no cumplir la condicion, enviar mensaje de error
        if (strcmp(token, "ugit--init") == 0) 
        {
            if (init_repo() == 0) 
            {
                printf("Repositorio inicializado.\n");
            } 
            else 
            {
                printf("Error al inicializar el repositorio.\n");
            }
        } 
        else if (strcmp(token, "ugit--add") == 0) 
        { 
            char *filename = strtok(NULL, " ");
            if (filename != NULL) 
            {
                add_file(filename);
            }
            else 
            {
                printf("ERROR: Debe indicar nombre del archivo.\n");
            }
        } 
        else if (strcmp(token, "ugit--rm") == 0)
        {
            char *filename = strtok(NULL, " "); // para que se pueda poner espacio
            if (filename != NULL) 
            {
                remove_file(filename);
            } 
            else 
            {
                printf("ERROR: Debe proporcionar el nombre del archivo a remover.\n");
            }
        } 
        else if (strcmp(token, "ugit--commit") == 0) 
        {
            char *mensaje_commit = strtok(NULL, "");
            if (mensaje_commit != NULL) 
            {
                commit(mensaje_commit);
            } 
            else 
            {
                printf("ERROR: Debe agregar un mensaje al commit.\n");
            }
        } 
        else if (strcmp(token, "ugit--log") == 0) 
        {
            log_commits();
        } 
        else if(strcmp(token, "ugit--help") == 0)
        {
            ayuda();
        } 
        else if (strcmp(token, "ugit--checkout") == 0) 
        {
            char *commit_id = strtok(NULL, " ");
            if (commit_id != NULL) 
            {
                checkout_commit(commit_id);
            } 
            else 
            {
                printf("ERROR: Debe agregar el ID del commit.\n");
            }
        } 
        else if (strcmp(token, "ugit--ls") == 0) 
        {
            list_files();
        } 
        else if (strcmp(token, "ugit--exit") == 0) 
        {
            printf("Saliendo de uGit.\n");
            break; // Salir del bucle
        } 
        else 
        {
            printf("Comando: %s, no reconocido, git--help para mas informacion\n", comando);
        }
    }
    return 0;
}
