#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "git.h"

/**
 * @file main.c
 * @brief Desarrollo de funciones de uGit
 * 
 * Autores:
 * - Constanza Araya
 * - Mario Calbuyahue
 * 
 * Este archivo contiene la implementación de las funciones del sistema de control
 * de versiones uGit.
 */

// Apunta a NULL porque no se han agregado mas nodos
static nodo *file_list = NULL;
// Como el repositorio no se ha creado aun es igual a 0
static int is_repo_initialized = 0;
// Almacena el commit actual
static CommitNode *current_commit = NULL;
// ID del siguiente commit
static int next_commit_id = 1;

/**
 * @brief Inicializa el repositorio.
 * 
 * Simula la creacion del directorio .ugit y marca el repositorio como inicializado.
 * @return int 0 si el repositorio ya esta inicializado, 0 si se inicializo correctamente.
 */
int init_repo() 
{
    if (is_repo_initialized) 
    {
        printf("Repositorio inicializado.\n");
        return 0;
    }
    // Simula la creacion del directorio .ugit
    is_repo_initialized = 1;
    return 0; 
}

/**
 * @brief Verifica si el repositorio esta inicializado.
 * 
 * Si el repositorio no esta inicializado, imprime un mensaje de error.
 * @return int 1 si el repositorio esta inicializado, 0 si no lo esta.
 */
int check_repo_initialized() 
{
    if (!is_repo_initialized) 
    {
        printf("ERROR: El repositorio no ha sido inicializado. Use 'git--init'.\n");
        return 0;
    }
    return 1;
}

/**
 * @brief Muestra la ayuda de comandos disponibles.
 */
void ayuda() 
{
    printf("Comandos disponibles:\n");
    printf("ugit--init          - Inicializa un nuevo repositorio uGit\n");
    printf("ugit--add           - Agrega un archivo\n");
    printf("ugit--commit        - Crea un nuevo commit con los archivos\n");
    printf("ugit--log           - Muestra el historial de commits\n");
    printf("ugit--checkout      - Cambia a un commit especifico por su ID\n");
    printf("ugit--ls            - Lista de archivos en el repositorio\n");
    printf("ugit--exit          - Salir de uGit\n");
    printf("ugit--help          - Muestra esta ayuda\n");
}

/**
 * @brief Agrega un archivo al area de preparacion.
 * 
 * Crea un nodo que representa un archivo y lo agrega a la lista de archivos.
 * @param filename Nombre del archivo a agregar.
 * @return int 0 si el archivo fue agregado, -1 en caso de error.
 */
int add_file(const char *filename) 
{
    if (!check_repo_initialized())
    {
        return -1;
    } 
    // Crea un nuevo nodo para un nuevo archivo
    nodo *new_node = (nodo *)malloc(sizeof(nodo));
    if (!new_node) 
    {
        perror("Error al asignar memoria");
        return -1;
    }
    strncpy(new_node->filename, filename, MAX_ARG);
    new_node->filename[MAX_ARG - 1] = '\0'; // Asegurar terminacion de cadena
    new_node->next = file_list;
    file_list = new_node;
    printf("Archivo %s agregado al area de preparacion.\n", filename);
    return 0;
}

/**
 * @brief Elimina un archivo del area de preparacion.
 * 
 * @param filename Nombre del archivo a eliminar.
 * @return int 0 si el archivo fue eliminado, -1 si no se encuentra o hay un error.
 */
int remove_file(const char *filename) 
{
    if (!check_repo_initialized())
    {
        return -1;
    } 
    nodo *current = file_list;
    nodo *previous = NULL;

    // Buscar el archivo en la lista
    while (current != NULL && strcmp(current->filename, filename) != 0) 
    {
        previous = current;        
        current = current->next;
    }

    // Si el archivo no se encuentra
    if (current == NULL) 
    {
        printf("Archivo no encontrado: %s\n", filename);
        return -1;
    }

    // Eliminar el archivo de la lista
    if (previous == NULL) 
    {
        // El archivo a eliminar es el primer nodo
        file_list = current->next;
    } 
    else 
    {
        previous->next = current->next;
    }
    free(current);
    printf("Archivo %s eliminado.\n", filename);
    return 0;
}

/**
 * @brief Crea un nuevo commit con los archivos en el area de preparacion.
 * 
 * @param mensaje Mensaje del commit.
 * @return int 0 si el commit fue exitoso, -1 en caso de error.
 */
int commit(const char *mensaje) 
{
    if (!check_repo_initialized()) return -1;

    // Crear un nuevo nodo para el commit
    CommitNode *new_commit = (CommitNode *)malloc(sizeof(CommitNode));
    if (!new_commit) 
    {
        perror("Error al asignar memoria");
        return -1;
    }
    
    // Copiar el mensaje del commit
    strncpy(new_commit->mensaje, mensaje, MAX_ARG);
    new_commit->mensaje[MAX_ARG - 1] = '\0'; // Asegurar la terminacion de la cadena
    
    // Asignar un ID unico
    new_commit->id = next_commit_id;
    next_commit_id++;  // Incrementar para el siguiente commit

    // Insertar el nuevo commit al principio de la lista
    new_commit->next = commit_list;
    commit_list = new_commit;

    printf("Commit creado: %s [ID: %d]\n", mensaje, new_commit->id); // Mostrar el ID
    return 0;
}

/**
 * @brief Muestra el historial de commits.
 * 
 * @return int 0 si no hay commits, -1 en caso de error.
 */
int log_commits() 
{
    if (!check_repo_initialized()) return -1;

    if (commit_list == NULL) 
    {
        printf("No hay commits en el historial.\n");
        return 0;
    }

    CommitNode *current = commit_list;
    printf("Historial de commits:\n");
    while (current != NULL) 
    {
        printf("- ID: %d, Mensaje: %s\n", current->id, current->mensaje); // Mostrar ID y mensaje
        current = current->next;
    }
    return 0;
}

/**
 * @brief Cambia a una version anterior de los commits (simulado).
 * 
 * @param commit_id_str ID del commit al que se desea cambiar.
 * @return int 0 si el cambio fue exitoso, -1 si no se encuentra el commit.
 */
int checkout_commit(const char *commit_id_str) 
{
    if (!check_repo_initialized()) 
    {
        return -1;
    }
    
    // Convertir el ID del commit de cadena a entero
    int commit_id = atoi(commit_id_str);

    // Simular la busqueda del commit por su ID
    CommitNode *current = commit_list;
    while (current != NULL) 
    {
        // Verifica si el ID del commit coincide con el commit_id
        if (current->id == commit_id) 
        {
            current_commit = current;

            printf("Cambio exitoso al commit ID: %d\n", current_commit->id);
            printf("Commit actual: %s\n", current_commit->mensaje);
            return 0;
        }
        current = current->next;
    }
    
    printf("ERROR: No se encontro el commit con ID: %d\n", commit_id);
    return -1;
}

/**
 * @brief Lista los archivos en el area de preparacion.
 * 
 * @return int 0 si no hay archivos, -1 en caso de error.
 */
int list_files() 
{
    if (!check_repo_initialized())
    {
        return -1;
    } 
    nodo *current = file_list;
    if (!current) 
    {
        printf("No hay archivos en el area de preparacion.\n");
        return 0;
    }
    printf("Archivos en el area de preparacion:\n");
    while (current) 
    {
        printf("%s\n", current->filename);
        current = current->next;
    }
    return 0;
}
