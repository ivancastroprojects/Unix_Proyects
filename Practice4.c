#include <stdio.h>
#include <string.h>

void printMenu(void) {
   printf("\nPor favor, seleccione una opción de la lista:\n");
     
   printf("1.  Numero de archivos\n");
   printf("2.  Numero de subdirectorios\n");
   printf("3.  Fichero más grande\n");
   printf("4.  Fichero más pequeño\n");
   printf("5.  Espacio total ocupado\n");
   printf("6.  Número de ficheros con permiso de lectura\n");
   printf("7.  Número de ficheros con permiso de escritura\n");
   printf("8.  Número de ficheros con permiso de ejecución\n");
   printf("9.  Ficheros con permiso de ejecución para todos los usuarios\n");
   printf("10. Salir\n");
}

int main(int argc, char *argv[]) {
   // Si recibimos dos o más parámetros finalizamos el programa
   // argc incluye el nombre del programa, por eso pongo argc>2 en lugar de argc>=2
   if (argc > 2) {
       printf("Número de argumentos erróneo\n");
       printf("Sintaxis: practica4 [PATH]\n");
       return 0; // Podemos usar return para salir de main en lugar de exit
   }
   
   // Guardaré en dir el directorio de trabajo, por defecto '.'
   char *dir = ".";
   if (argc == 2) dir=argv[1]; // Si argc=2 significa que tengo un parámetro y debo actualizar dir

   char cmd[1000];
   sprintf(cmd, "test -d %s", dir); // Debo comprobar que el directorio existe
   int i = system(cmd);
   // Si la llamada a system devuelve un valor distinto de 0 significa que el comando test ha fallado y por tanto el directorio no existe.
   if (i != 0) {
       printf("Directorio no válido\n");
       return 0;
   }
   
   printf("\nEstadísticas del directorio %s\n", dir);

   int opcion;
   // Repetimos mientras que no se seleccione la opción 'salir'
   do {
      printMenu(); // Mostramos el menú
      scanf("%d", &opcion); // Leemos la opción deseada por el usuario
    
      char *command = NULL;

      // En función de la opción elegida por el usuario seleccionamos un comando u otro
      switch (opcion) {
         case 1:
            sprintf(cmd, "ls -l %s|grep ^-|wc -l", dir);
            command = &cmd[0];
            printf("\nNúmero de archivos:\n");
            break;
         case 2:
            sprintf(cmd, "ls -l %s|grep ^d|wc -l", dir);
            command = &cmd[0];
            printf("\nNúmero de subdirectorios:\n");
            break;

         case 3:
            sprintf(cmd, "ls -lS %s | grep ^- | awk '{print $8}' | head -1", dir);
            command = &cmd[0];
            printf("\nEl archivo más grande:\n");
            break;
         case 4:
            sprintf(cmd, "ls -lS %s | grep ^- | awk '{print $8}' | tail -1", dir);
            command = &cmd[0];
            printf("\nEl archivo más pequeño:\n");
            break;
         case 5:
            sprintf(cmd, "du -sh %s|cut -f1", dir);
            command = &cmd[0];
            printf("\nEspacio total ocupado:\n");
            break;
         case 6:
            sprintf(cmd, "ls -l %s|grep ^-r|awk '{print $3,$8}'|grep $USER|awk '{print $2}' > tmp.txt && ls -l %s|grep ^-.{3}r|awk '{print $4,$8}'|grep `cat /etc/group|grep $GROUPS|cut -d: -f1`|awk '{print $2}' >> tmp.txt && ls -l %s|egrep '^-.{6}r'|awk '{print $8}' >> tmp.txt && expr `sort -u tmp.txt | wc -l` - 1 && rm tmp.txt", dir, dir, dir);
            command = &cmd[0];
            printf("\nNúmero de ficheros con permiso de lectura:\n");
            break;
         case 7:
            sprintf(cmd, "ls -l %s|grep ^-.w|awk '{print $3,$8}'|grep $USER|awk '{print $2}' > tmp.txt && ls -l %s|grep ^-.{4}w|awk '{print $4,$8}'|grep `cat /etc/group|grep $GROUPS|cut -d: -f1`|awk '{print $2}' >> tmp.txt && ls -l %s|egrep '^-.{7}w'|awk '{print $8}' >> tmp.txt && expr `sort -u tmp.txt | wc -l` - 1 && rm tmp.txt", dir, dir, dir);
            command = &cmd[0];
            printf("\nNúmero de ficheros con permiso de escritura:\n");
            break;
         case 8:
            sprintf(cmd, "ls -l %s|grep ^-..x|awk '{print $3,$8}'|grep $USER|awk '{print $2}' > tmp.txt && ls -l %s|grep ^-.{5}x|awk '{print $4,$8}'|grep `cat /etc/group|grep $GROUPS|cut -d: -f1`|awk '{print $2}' >> tmp.txt && ls -l %s|egrep '^-.{8}x'|awk '{print $8}' >> tmp.txt && sort -u tmp.txt | wc -l && rm tmp.txt", dir, dir, dir);
            command = &cmd[0];
            printf("\nNúmero de ficheros con permiso de ejecución:\n");
            break;
         case 9:
            sprintf(cmd, "ls -l %s|grep ^-..x..x..x|awk '{print $8}'", dir);
            command = &cmd[0];
            printf("\nFicheros con permiso de ejecución para todos los usuarios:\n");
            break;
         case 10:
            break;
         default:
            printf("\nOpción no válida\n");
      }
      
      // Ejecutamos el comando
      if (command != NULL) system(command);
      
   } while (opcion != 10);
   
   return 0;
}