#ifndef GIT_H
#define GIT_H

#define MAX_ARG 50
#define MAX_COMANDO 100

/**
 * @file git.h
 * @brief Encabezado del sistema de control de versiones µGit.
 *
 * Este archivo define las estructuras y las funciones utilizadas en 
 * la implementación de µGit.
 *
 * Autores:
 * - Constanza Araya
 * - Mario Calbuayhue
 */

/**
 * @struct nodo
 * @brief Estructura para representar un archivo en el area de preparacion.
 */
typedef struct nodo {
    char filename[MAX_ARG];  ///< Nombre del archivo.
    struct nodo *next;       ///< Puntero al siguiente archivo.
} nodo;

/**
 * @struct CommitNode
 * @brief Estructura para representar un commit en el sistema.
 */
typedef struct CommitNode {
    char mensaje[MAX_ARG];   ///< Mensaje del commit.
    int id;                  ///< ID unico del commit.
    struct CommitNode *next; ///< Puntero al siguiente commit.
} CommitNode;

static CommitNode *commit_list = NULL; ///< Puntero al inicio de la lista de commits.

/**
 * @brief Inicializa el repositorio.
 * @return int 0 si el repositorio fue inicializado correctamente.
 */
int init_repo();

/**
 * @brief Agrega un archivo al area de preparacion.
 * @param filename Nombre del archivo a agregar.
 * @return int 0 si el archivo fue agregado correctamente.
 */
int add_file(const char *filename);

/**
 * @brief Crea un nuevo commit con los archivos en el area de preparacion.
 * @param mensaje Mensaje del commit.
 * @return int 0 si el commit fue exitoso.
 */
int commit(const char *mensaje);

/**
 * @brief Muestra el historial de commits.
 * @return int 0 si se muestran los commits correctamente.
 */
int log_commits();

/**
 * @brief Cambia a un commit especifico.
 * @param commit_id ID del commit al que se desea cambiar.
 * @return int 0 si el cambio fue exitoso.
 */
int checkout_commit(const char *commit_id);

/**
 * @brief Lista los archivos en el area de preparacion.
 * @return int 0 si no hay archivos o si se listan correctamente.
 */
int list_files();

/**
 * @brief Elimina un archivo del area de preparacion.
 * @param filename Nombre del archivo a eliminar.
 * @return int 0 si el archivo fue eliminado correctamente.
 */
int remove_file(const char *filename);

/**
 * @brief Muestra la ayuda de los comandos disponibles.
 */
void ayuda();

#endif // GIT_H
