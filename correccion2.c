#include <stdio.h>
#include <stdlib.h>

#define MAX_PRODUCTO 100

typedef struct {
    int id;
    char nombre[30];
    int cantidad;
    float precio;
} Producto;

void Agregar_Producto(Producto* inventario[], int* num_producto);
void Mostrar_todos_los_productos(Producto* inventario[], int num_producto);
void Actualizar_Productos(Producto* inventario[], int num_producto);
void Eliminar_Productos(Producto* inventario[], int* num_producto);
void Salir_del_Programa(Producto* inventario[], int num_producto);
void Guardar_Productos(Producto* inventario[], int num_producto);
void Cargar_Productos(Producto* inventario[], int* num_producto);

int main()
{
    int opcion;
    int num_producto = 0;
    Producto* inventario[MAX_PRODUCTO] = { NULL };

    Cargar_Productos(inventario, &num_producto);

    do
    {
        printf("\n\n=== Menu Principal ===\n\n");
        printf("1- Ver Productos\n");
        printf("2- Ingresar Producto\n");
        printf("3- Modificar producto por ID\n");
        printf("4- Eliminar Producto\n");
        printf("5- Salir\n\n");

        printf("Ingrese su eleccion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 1:
                Mostrar_todos_los_productos(inventario, num_producto);
                break;
            case 2:
                Agregar_Producto(inventario, &num_producto);
                break;
            case 3:
                Actualizar_Productos(inventario, num_producto);
                break;
            case 4:
                Eliminar_Productos(inventario, &num_producto);
                break;
            case 5:
                Guardar_Productos(inventario, num_producto);
                Salir_del_Programa(inventario, num_producto);
                break;
            default:
                printf("Opcion invalida\n");
                break;
        }
    } while (opcion != 5);

    return 0;
}

void Agregar_Producto(Producto* inventario[], int* num_producto)
{
    if (*num_producto < MAX_PRODUCTO)
    {
        Producto* agregar_producto = malloc(sizeof(Producto));

        printf("\nIngrese el ID del producto: ");
        scanf("%d", &(agregar_producto->id));
        getchar();
        printf("Ingrese el nombre del producto: ");
        fgets(agregar_producto->nombre, 30, stdin);
        printf("Ingrese la cantidad del producto: ");
        scanf("%d", &(agregar_producto->cantidad));
        printf("Ingrese el precio del producto: ");
        scanf("%f", &(agregar_producto->precio));

        inventario[*num_producto] = agregar_producto;
        (*num_producto)++;

        printf("\n\nEl producto se agrego correctamente.");
    }
    else
    {
        printf("No hay espacio en el inventario");
    }
}

void Mostrar_todos_los_productos(Producto* inventario[], int num_producto)
{
    if (num_producto > 0)
    {
        printf("\nLista de productos\n");

        for (int i = 0; i < num_producto; i++)
        {
            Producto* producto = inventario[i];

            printf("\nProducto %d: \n", i + 1);
            printf("ID: %d\n", producto->id);
            printf("Nombre: %s", producto->nombre);
            printf("Cantidad: %d\n", producto->cantidad);
            printf("Precio: %.2f\n", producto->precio);
        }
    }
    else
    {
        printf("\nNo hay ningun producto en el inventario.");
    }
}

void Actualizar_Productos(Producto* inventario[], int num_producto)
{
    int ID;
    int encontrar = -1;

    printf("\nIngrese el ID del producto: ");
    scanf("%d", &ID);

    for (int i = 0; i < num_producto; i++)
    {
        Producto* producto = inventario[i];

        if (producto->id == ID)
        {
            encontrar = i;
            break;
        }
    }

    if (encontrar != -1)
    {
        Producto* actualizar_producto = inventario[encontrar];
        getchar();
        printf("\nIngrese el nuevo nombre del producto: ");
        fgets(actualizar_producto->nombre, 30, stdin);
        printf("Ingrese la nueva cantidad del producto: ");
        scanf("%d", &(actualizar_producto->cantidad));
        printf("Ingrese el nuevo precio del producto: ");
        scanf("%f", &(actualizar_producto->precio));

        printf("\nProducto actualizado correctamente.");
    }
    else
    {
        printf("\nNo existe un producto con ese ID.");
    }
}

void Eliminar_Productos(Producto* inventario[], int* num_producto)
{
    int ID;
    int encontrar = -1;

    printf("Ingrese el ID del producto que desea eliminar: ");
    scanf("%d", &ID);

    for (int i = 0; i < *num_producto; i++)
    {
        Producto* producto = inventario[i];

        if (producto->id == ID)
        {
            encontrar = i;
            break;
        }
    }

    if (encontrar != -1)
    {
        free(inventario[encontrar]);

        for (int i = encontrar; i < *num_producto - 1; i++)
        {
            inventario[i] = inventario[i + 1];
        }

        (*num_producto)--;

        printf("\nProducto eliminado correctamente.");
    }
    else
    {
        printf("\nNo existe un producto con ese ID.");
    }
}

void Salir_del_Programa(Producto* inventario[], int num_producto)
{
    printf("Gracias por usar el sistema de inventario.");

    for (int i = 0; i < num_producto; i++)
    {
        free(inventario[i]);
    }
}

void Guardar_Productos(Producto* inventario[], int num_producto)
{
    FILE* archivo = fopen("productos.txt", "w+");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo para guardar los productos.\n");
        return;
    }

    fwrite(&num_producto, sizeof(int), 1, archivo); 

    for (int i = 0; i < num_producto; i++)
    {
        fwrite(inventario[i], sizeof(Producto), 1, archivo); 
    }

    fclose(archivo);
    printf("\nProductos guardados correctamente.\n");
}

void Cargar_Productos(Producto* inventario[], int* num_producto)
{
    FILE* archivo = fopen("productos.txt", "r+");
    if (archivo == NULL)
    {
        printf("No se encontró el archivo de productos existente.\n");
        return;
    }

    fread(num_producto, sizeof(int), 1, archivo); 

    for (int i = 0; i < *num_producto; i++)
    {
        Producto* producto = malloc(sizeof(Producto));
        fread(producto, sizeof(Producto), 1, archivo); 
        inventario[i] = producto;
    }

    fclose(archivo);
    printf("\nProductos cargados correctamente.\n");
}
