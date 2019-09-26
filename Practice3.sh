#!/bin/bash

# ------------------- #
# Sistemas operativos #
# Práctica 3          #
# ------------------- #

###
##  Funciones auxiliares
#

# Espacio utilizado en disco
function diskUsed()
{
  du -sh|cut -f1
}

# Cuenta del número de subdirectorios
function numDir()
{
  ls -l|grep ^d|wc -l
}

# Cuenta del número de archivos
function numFiles()
{
  ls -l|grep ^-|wc -l
}

# El archivo más grande
function biggestFile()
{
  ls -lS | grep ^- | awk '{print $8}' | head -1
}

# El archivo más pequeño
function smallestFile()
{
  ls -lS | grep ^- | awk '{print $8}' | tail -1
}

# Cuenta del número de archivos con permiso de lectura para $USER
function numReadFilesUser()
{
  #ls -l|grep ^-r|wc -l
  ls -l|grep ^-r|awk '{print $3,$8}'|grep $USER|awk '{print $2}' > tmp.txt && ls -l|grep ^-.{3}r|awk '{print $4,$8}'|grep `cat /etc/group|grep $GROUPS|cut -d: -f1`|awk '{print $2}' >> tmp.txt && ls -l|egrep '^-.{6}r'|awk '{print $8}' >> tmp.txt && expr `sort -u tmp.txt | wc -l` - 1 && rm tmp.txt
}

# Cuenta del número de archivos con permiso de escritura para $USER
function numWriteFilesUser()
{
  #ls -l|grep ^-.w|wc -l
  ls -l|grep ^-.w|awk '{print $3,$8}'|grep $USER|awk '{print $2}' > tmp.txt && ls -l|grep ^-.{4}w|awk '{print $4,$8}'|grep `cat /etc/group|grep $GROUPS|cut -d: -f1`|awk '{print $2}' >> tmp.txt && ls -l|egrep '^-.{7}w'|awk '{print $8}' >> tmp.txt && expr `sort -u tmp.txt | wc -l` - 1 && rm tmp.txt
}

# Cuenta del número de archivos con permiso de ejecución para $USER
function numRunFilesUser()
{
  #ls -l|grep ^-..x|wc -l
  ls -l|grep ^-..x|awk '{print $3,$8}'|grep $USER|awk '{print $2}' > tmp.txt && ls -l|grep ^-.{5}x|awk '{print $4,$8}'|grep `cat /etc/group|grep $GROUPS|cut -d: -f1`|awk '{print $2}' >> tmp.txt && ls -l|egrep '^-.{8}x'|awk '{print $8}' >> tmp.txt && sort -u tmp.txt | wc -l && rm tmp.txt
}

# Cuenta del número de archivos ejecutables para cualquier usuario
function listRunFiles()
{
  ls -l|grep ^-..x..x..x|awk '{print $8}'
}

###
##  Inicio del script
#

# Caracteres de escape para colorear la salida estándar en bash.
# Se pueden quitar, basta con eliminar las variables ${red}, ${blue} y ${endColor} de las llamadas a 'echo'
red='\e[0;31m'
blue='\e[0;34m'
endColor='\e[0m'

# Si no recibimos ningún argumento trabajermos en el directorio actual
if test $# -eq 0
then
  dir=.
fi

# Si recibimos un parámetro trabajaremos en el directorio que se indique
if test $# -eq 1
then
  dir=$1
fi

# Si recibimos más de un parámetro abortamos la ejecución
if test $# -gt 1
then
  echo -e "${blue}Numero de argumentos incorrecto${endColor}"
  exit 0
fi

# Accedemos al directorio de trabajo
cd $dir > /dev/null # /dev/null es la salida nula, con esto evitamos que escriba mensajes por pantalla, prueba a quitarlo
if test $? -ne 0
then
  echo -e "${blue}No existe el directorio $dir${endColor}"
  exit 0
fi

# Visualizamos el directorio de trabajo
echo -e "\n${blue}Estadísticas del directorio `pwd`${endColor}\n"

while true # Bucle infinito
do
  # Visualizamos el menú
  echo -e "${blue}Por favor, seleccione una opción de la lista:${endColor}"
  echo -e "\t${blue}1.  Espacio total ocupado${endColor}"
  echo -e "\t${blue}2.  Numero de subdirectorios${endColor}"
  echo -e "\t${blue}3.  Numero de archivos${endColor}"
  echo -e "\t${blue}4.  Fichero más grande${endColor}"
  echo -e "\t${blue}5.  Fichero más pequeño${endColor}"
  echo -e "\t${blue}6.  Número de ficheros con permiso de lectura para $USER${endColor}"
  echo -e "\t${blue}7.  Número de ficheros con permiso de escritura para $USER${endColor}"
  echo -e "\t${blue}8.  Número de ficheros con permiso de ejecución para $USER${endColor}"
  echo -e "\t${blue}9.  Ficheros con permiso de ejecución para todos los usuarios${endColor}"
  echo -e "\t${blue}10. Salir${endColor}"
  
  read option
  case $option in
    1) dUsed=`diskUsed`
       echo -e "\n${red}Espacio total ocupado: $dUsed${endColor}\n"
       ;;
    2) nDir=`numDir`
       echo -e "\n${red}Numero de subdirectorios: $nDir${endColor}\n"
       ;;
    3) nFiles=`numFiles`
       echo -e "\n${red}Numero de archivos: $nFiles${endColor}\n"
       ;;
    4) bigFile=`biggestFile`
       echo -e "\n${red}El archivo más grande: $bigFile${endColor}\n"
       ;;
    5) smallFile=`smallestFile`
       echo -e "\n${red}El archivo más pequeño: $smallFile${endColor}\n"
       ;;
    6) nFiles=`numReadFilesUser`
       echo -e "\n${red}Número de ficheros con permiso de lectura para $USER: $nFiles${endColor}\n"
       ;;
    7) nFiles=`numWriteFilesUser`
       echo -e "\n${red}Número de ficheros con permiso de escritura para $USER: $nFiles${endColor}\n"
       ;;
    8) nFiles=`numRunFilesUser`
       echo -e "\n${red}Número de ficheros con permiso de ejecución para $USER: $nFiles${endColor}\n"
       ;;
    9) nFiles=`listRunFiles`
       echo -e "\n${red}Ficheros con permiso de ejecución para todos los usuarios:\n$nFiles${endColor}\n"
       ;;
    10) break
        ;; # Abortamos la ejecución del bucle while
    *) echo -e "\n${red}Opción no válida${endColor}\n"
       ;;
  esac
done
# Fin del script
 
