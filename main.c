#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include<time.h>

void pruebas_abb_alumno(void);

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(int argc, char *argv[])
{
    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    int stime;
    long ltime;
    ltime = time(NULL);
    stime = (int)ltime/2;
    srand((unsigned)stime); 
    pruebas_abb_alumno();

    return failure_count() > 0;
}
