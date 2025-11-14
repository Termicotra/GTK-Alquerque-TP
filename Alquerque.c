////////////////////////////////////////////////////////
//             LIBRERIAS y CONSTANTES                 //
////////////////////////////////////////////////////////
#include <gtk/gtk.h>    //Incluir la libreria de gtk
#include <stdlib.h>     //Incluir la libreria estandar
#define FIL 5           //Definicion de la fila maxima para la tabla auxiliar
#define COL 5           //Definicion de la columna maxima para la tabla auxiliar
////////////////////////////////////////////////////////
//           VARIABLES GLOBALES   GTK                 //
////////////////////////////////////////////////////////
    GtkWidget *window_main;                 // Window main, es el widget de la ventana principal en glade
    GtkWidget *window_ganador;              // Window ganador, es el widget a la ventana de ganador en glade
    GtkWidget *F_Mano;                      // Ficha en mano, widget para cambiar la imagen de la ficha en mano
    GtkWidget *L_Winner;                    // Label Winner, es el widget del label de la seccion de ganador, para cambiar el nombre del ganador
    GtkWidget *I_Winner;                    // Imagen Winner, widget para cambiar la imagen de la ficha utilizada por el ganador
    GtkWidget *window_about;                // Window about, widget para la ventana de acerca de los autores en glade
    GtkWidget *window_reglas;               // Window reglas, widget para la ventana de reglas en glade
    GtkButton* button_rules;                // Button rules, widget para el boton en el menu principal, para desplegar las reglas
    GtkButton* button_play;                 // Button play, widget de boton en el menu principal para poder jugar
    GtkButton* button_exit;                 // Button exit, widget de boton en el menu prinicipal para salir
    GtkWidget *window_play;                 // Window play, widget para la ventana de jugar en glade
    GtkWidget *eventbox;                    // Event box, para detectar clicks en el tablero de juego
    GtkWidget *label_turno;                 // Label turno, widget para cambiar el turno en pantalla
    GtkWidget *label_estado;                // Label estado, widget para cambiar el estado en pantalla
    GtkWidget *tablero;                     // Tablero, widget del grid del tablero en glade
    GtkWidget *m_reglas;                    // Menu reglas, widget para el sub menu de reglas
    GtkWidget *m_acerca;                    // Menu acerca, widget para el sub menu de acerca
    GtkWidget *window_nombre;               // Window nombres, widget para la ventana de ingreso de nombre de usuario en glade
    GtkWidget *entry_user;                  // label de tipo entry, para poder detectar lo que inserta el usuario
    GtkWidget *button_user;                 // button user, widget para aceptar y cargar lo que introdujo el usuario en el entry
    GtkWidget *l_user1;                     // label user, widget para cambiar el label cuando se ingreso el nombre del usuario 1
    GtkWidget *C_Blancas;                   // Captura Blancas, widget para cambiar de label de cuantas blancas fueron capturadas
    GtkWidget *C_Negras;                    // Captura Negras, widget para cambiar el label de cuantas negras fueron capturadas
    guint ret;
    GtkBuilder *builder;                    // Widget para cargar el builder
    GError *error = NULL;                   // Widget para detectar errores
////////////////////////////////////////////////////////
//           VARIABLES GLOBALES   C                   //
////////////////////////////////////////////////////////
    const gchar *user1;     //Constante de tipo gtkchar para guardar el nombre del user1
    const gchar *user2;     //Constante de tipo gtkchar para guardar el nombre del user2
    const gchar *turno1;    //Constante de tipo gtkchar para guardar el turno1
    const gchar *turno2;    //Constante de tipo gtkchar para guardar el turno2
    guint i,j;              // entero sin signo de tipo gtk, para guardar los clicks
    int trn,click;          // Enteros para controlar el turno y la cantidad de clicks
    char tabla [FIL][COL]= {{'N','N','N','N','N'},{'N','N','N','N','N'},{'N','N',' ','B','B'},{'B','B','B','B','B'},{'B','B','B','B','B'}}; //Definicion manual de un tablero auxiliar
////////////////////////////////////////////////////////////////////////////////////////
//                  FUNCIONES GENERALES PARA EL FUNCIONAMIENTO                        //
////////////////////////////////////////////////////////////////////////////////////////
    gboolean on_widget_deleted(GtkWidget *widget)   //Funcion para hacer que un widget al ser "destroy", solo se oculte
    {
        gtk_widget_hide(widget);
        return TRUE;
    }

    void gtk_button_clicked_rules (GtkButton* button)   //Funcion que cuando detecta un click en el boton rules, muestra la ventana de reglas
    {
        gtk_widget_show (window_reglas);
    }

    void gtk_button_clicked_play (GtkButton* button)    //Funcion que cuando se clickea en el boton jugar, oculta el menu principal
    {                                                   // y despliega la ventana jugar y la ventana para ingresar nombres
        gtk_widget_show (window_nombre);
        gtk_widget_show (window_play);
        gtk_widget_hide (window_main);
    }
    void destroy(GtkWidget *widget)                     //Funcion para cuando se cierra una ventana importante, ya que detiene el programa
    {
        gtk_main_quit();
    }
    void Acerca(GtkMenuItem *m)     //Funcion para cuando se clickea en el submenu acerca
    {
        gtk_dialog_run(GTK_DIALOG(window_about));   //Hace funcionar la ventana de creditos
        on_widget_deleted (window_about);
    }
    void Reglas(GtkMenuItem *m)     //Funcion para cuando se clickea en el submenu reglas, muestra la ventana reglas
    {
        gtk_widget_show(window_reglas);
    }
    void on_btn_clicked_user (GtkWidget *widget)    //Funcion para cargar nombres de usuario
    {
        static int cont2=1,ran; //Declaracion de enteros estaticos para controlar el ingreso de user1 y luego user2.. Y ran para guardar un numero random para el turno aleatorio de inicio
        if (cont2==1)   //Si el contador es 1, es turno del usuario 1 de ingresar su nombre
        {

            gchar *tmp = gtk_editable_get_chars(GTK_EDITABLE (entry_user),0,-1);    //Se almacena temporalmente lo ingresado
            user1 = g_strdup_printf("%s", tmp);                                     //Se guarda lo ingresado en user1
            turno1 = g_strdup_printf("El turno es de %s con NEGRAS", tmp);          // Aqui se guarda un texto concatenado con lo ingresado
            gtk_label_set_text(GTK_LABEL(l_user1), "Introduzca el nombre del usuario 2");   //Se cambia el label para decirle que ingrese el user2 su nombre
            gtk_editable_delete_text (GTK_EDITABLE (entry_user),0,-1);                      //Elimina lo que estaba en los campos de entry
            g_free(tmp);                                                                    //Libera memoria de lo temporal
            cont2++;                                                                        //Aumenta el contador
        }
        else if (cont2==2)  //Contador con valor 2, significa turno del usuario 2
        {
            gchar *tmp = gtk_editable_get_chars(GTK_EDITABLE (entry_user),0,-1);
            user2 = g_strdup_printf("%s", tmp);
            turno2 = g_strdup_printf("El turno es de %s con BLANCAS", tmp);     //Mismo procedimiento que el usuario 1
            g_free(tmp);
            gtk_widget_hide (window_nombre);    // Una vez cargado, se oculta la ventana
            ran = rand() %  11;                 // Se encuentra un nro random
             if (ran >= 5)
             {
                gtk_label_set_text(GTK_LABEL(label_turno), turno1);     //Dependiendo del numero se asigna el turno a uno o a otro
                trn = 1;                                                //Se cambia el label del turno en pantalla para indicar quien comienza y con que
                click = 0;
             }
             else if (ran<5)
             {
                gtk_label_set_text(GTK_LABEL(label_turno), turno2);
                trn = 2;
                click = 2;
             }
        }
    }
//////////////////////////////////////////////////////////////////////////////////////////////
//                              FUNCION PARA JUGABILIDAD                                    //
//////////////////////////////////////////////////////////////////////////////////////////////
    void ganador () //Funcion para buscar un ganador
    {
        int i,j,negras=0,blancas=0,aux1=0,aux2; //Variables para recorrer la matriz y contar las fichas
        for (i=0;i<FIL;i++)
        {
            for (j=0;j<COL;j++)
            {
                if (tabla [i][j] == 'N')    //Se recorre la matriz contando las fichas Negras y Blancas
                    negras++;
                if (tabla [i][j] == 'B')
                    blancas++;
            }
        }
        if (negras == 0 || negras>=1)   //Dependiendo de si hay fichas negras se da una u otra cosa
        {
            if (negras >= 1)    //Si hay mas de 1 ficha negra
            {
                aux2=0;
                i=4;
                for (j=0;j<COL;j++)
                {
                    if (tabla[i][j] == 'N') //Se recorre en la ultima fila, donde ya la negra no puede hacer nada
                    {
                        aux2++;
                        if (aux2 == negras) //Si la cantidad de fichas en la ultima fila concuerda con la cantidad de negras en el tablero
                            aux1 = 1;       // Se declara un empate, ya que la negra y no puede hacer nada
                    }
                    if (tabla [i][j] == 'B')    //En cambio si todas las fichas negras estan en la ultima fila
                        aux1 = 2;               // y se detecta una fichas blanca en la ultima, el juego continua
                }
            }
            if (aux1 == 1)  //Si aux1 tiene valor 1, se declara el empate
            {
                gtk_widget_show(window_ganador);        //Se muestra la ventada de ganador
                gtk_image_set_from_file(GTK_IMAGE(I_Winner), "IMG/Empate.png"); //Se cambia la imagen de la ficha ganadora a un apreton de manos
                gtk_label_set_text(GTK_LABEL(L_Winner), "EMPATE");  //Se cambia el label del ganador a empate
            }
            if (negras==0)  //Sin embrago si no quedan fichas negras en el tablero se le da victoria a las fichas blancas
            {
                gtk_widget_show(window_ganador);    //Se muestra la ventana de ganador
                gtk_image_set_from_file(GTK_IMAGE(I_Winner), "IMG/Blancas.png");    //Se cambia la imagen de ficha, a la ficha del ganador
                gtk_label_set_text(GTK_LABEL(L_Winner), user2);  //Se cambia el label del ganador al nombre del user 2 que jugaba con blancas
            }
        }
        if (blancas == 0 || blancas>=1) //Mismo procedimiento que con negras
        {
            if (blancas >= 1)
            {
                aux2=0;
                i=0;
                for (j=0;j<COL;j++)
                {
                    if (tabla[i][j] == 'B') //Mismo procedimiento, solo que ahora en vez de la ultima fila, se comprueba la primera
                    {                       // donde las blancas no pueden hacer nada
                        aux2++;
                        if (aux2 == blancas)
                            aux1 = 4;
                    }
                    if (tabla [i][j] == 'N')
                        aux1 = 5;
                }
            }
            if (aux1 == 4)
            {
                gtk_widget_show(window_ganador);
                gtk_image_set_from_file(GTK_IMAGE(I_Winner), "IMG/Empate.png");
                gtk_label_set_text(GTK_LABEL(L_Winner), "EMPATE");
            }
            if (blancas == 0)
            {
                gtk_widget_show(window_ganador);
                gtk_image_set_from_file(GTK_IMAGE(I_Winner), "IMG/Negras.png");
                gtk_label_set_text(GTK_LABEL(L_Winner), user1);
            }
        }
    }
    int val_mov (int f,int c,int x,int y,int trn)   //Funcion para validar movimientos, que recibe variables de coordenadas y el turno
    {
        int aux1 = 0;  //Variable de retorno para indicar si el movimiento es valido
        if (trn==1) //Si es turno 1 se comprueba movimientos de fichas negras
        {
            if ((c==0 && f==1) || (c==0 && f==3) || (c==1 && f==4) || (c==2 && f==1) || (c==1 && f==0) || (c==1 && f==2) || (c==2 && f==3) || (c==3 && f==2) || (c==3 && f==4)
                 || (c==3 && f==0) || (c==4 && f==1) || (c==4 && f==3)) //Dependiendo de estas posiciones los movimientos no podran ser diagonales, y menos atras
            {
                if (f==x)   //Se comprueba que la fila de la ficha a mover sea la misma que donde se quiere mover
                {
                    aux1 +=3;       //Si esto es asi, se suma parcialmente un valor a aux
                    if ((c == y) ||     //Si el movimiento se quiere realizar en la misma columna o una adyacente pero en la misma fila
                    (c == (y+1)) ||
                    (c == (y-1)))
                        aux1 += 2;  //Si es asi se aumenta aux, y se tiene el valor de 5, que determina que si se puede hacer el movimiento
                }
                else if (f == (x-1)) //Si el mov. se quiere hacer una fila mas abajo
                {
                    aux1 +=3;
                    if (c == y)     //Esta debe ser estrictamente la misma columna para no permitir movimientos en diagonal
                        aux1 += 2;
                }
            }
            else if ((c==0 && f==0) || (c==1 && f==1)  || (c==0 && f==4) || (c==1 && f==3) || (c==2 && f==2) || (c==3 && f==1) || (c==3 && f==3) || (c==2 && f==0) || (c==2 && f==4)
                      || (c==4 && f==4) || (c==4 && f==0) || (c==4 && f==2) || (c==0 && f==2))  //Estas posiciones si tiene la validez de moverse en todas las direcciones menos atras
            {
                if ((f == (x-1)) ||
                    (f == (x) ))
                    aux1 += 3;		// Aqui se van verificando, que el mov. solo puede ser en cuadricula y no atras
                if ((c == y) ||
                    (c == (y+1)) ||
                    (c == (y-1)))
                    aux1 += 2;
            }
            if ((c == x)&&(f == y))
                aux1 = 0;
            return aux1;		// Returna un valor 5 si es valido el mov., y si es otro valor, no es valido el mov.
        }
        else if (trn==2)    //Validacion de movimientos para las fichas blancas
        {
            if ((c==0 && f==1) || (c==0 && f==3) || (c==1 && f==4) || (c==2 && f==1) || (c==1 && f==0) || (c==1 && f==2) || (c==2 && f==3) || (c==3 && f==2) || (c==3 && f==4)
                 || (c==3 && f==0) || (c==4 && f==1) || (c==4 && f==3))
            {
                if (f==x)
                {
                    aux1 +=3;
                    if ((c == y) ||
                    (c == (y+1)) ||
                    (c == (y-1)))
                        aux1 += 2;
                }                           //Exactamente lo mismo que las fichas negras solo que ahora
                else if (f == (x+1))        // Tiene que ser una fila arriba, no abajo como las negras
                {
                    aux1 +=3;
                    if (c == y)
                        aux1 += 2;
                }
            }
            else if ((c==0 && f==0) || (c==1 && f==1)  || (c==0 && f==4) || (c==1 && f==3) || (c==2 && f==2) || (c==3 && f==1) || (c==3 && f==3) || (c==2 && f==0) || (c==2 && f==4)
                      || (c==4 && f==4) || (c==4 && f==0) || (c==4 && f==2) || (c==0 && f==2))
            {
                if ((f == (x+1)) ||    //Y a diferencia de las negras, tiene que ser una fila arriba
                    (f == (x) ))
                    aux1 += 3;		// Aqui se van verificando que el mov. solo puede ser en cuadricula, y no atras
                if ((c == y) ||
                    (c == (y+1)) ||
                    (c == (y-1)))
                    aux1 += 2;
            }
            if ((c == x)&&(f == y))
                aux1 = 0;
            return aux1;		// Returna un valor si es valido o no, el mov.
        }
    }

    int val_sal (int z, int k ,int c,int f,int x,int y,int trn)		//Funcion para validar los saltos, recibe variables de coordenadas y turnos
    {
        int aux3=0;  //Variable de retorno para validar el salto
        if (trn == 1)   //Si la fichas es negra
        {
            if ((c==0 && f==1) || (c==0 && f==3) || (c==1 && f==4) || (c==2 && f==1) || (c==1 && f==0) || (c==1 && f==2) || (c==2 && f==3) || (c==3 && f==2) || (c==3 && f==4)
                 || (c==3 && f==0) || (c==4 && f==1) || (c==4 && f==3)) //Misma logica que la de validar mov., para decir que el salto no puede ser en diagonal
            {
                if (f == (z-1))             //Si es negra se pide una fila menos
                {
                    if (c == k)             //Se comprueba que el que quiere saltar este en la misma columna del que va a ser saltado ya que no se puede diagonalmente
                    {
                        if (x == (z+1))      //Misma logica que en validar mov. solo que ahora tambien se comprueba un par de coordenada mas
                        {                    // F y C son para la ficha que quiere saltar
                            if (y == k)      // X e Y son para donde se va a saltar
                                aux3 = 5;    // Z y K son de la ficha contraria, que se quiere saltar y capturar
                        }
                    }
                }
                if (f==z)
                {
                    if (x==z)
                    {
                        if (y==(k-1))
                            aux3=5;
                        else if (y==(k+1))
                            aux3=5;
                    }
                    else if (x!=z)
                        aux3=0;
                }
            }
            else if ((c==0 && f==0) || (c==1 && f==1)  || (c==0 && f==4) || (c==1 && f==3) || (c==2 && f==2) || (c==3 && f==1) || (c==3 && f==3) || (c==2 && f==0) || (c==2 && f==4)
                      || (c==4 && f==4) || (c==4 && f==0) || (c==4 && f==2) || (c==0 && f==2)) //Misma logica que validar mov., para decir que los saltos son en todas las direcciones
            {
                if (f == (z-1))
                {
                    if (c == (k-1))             //Ahora si se puede comprobar con saltos diagonales
                    {
                        if ( x == (z+1))
                        {
                            if (y == (k+1))
                                aux3 = 5;
                        }
                    }
                    else if (c == (k+1))
                    {
                        if (x==(z+1))			// Mismo sistema que en val_mov, solo que se solicita una coordenada mas...
                        {

                            if (y == (k-1))
                                aux3 = 5;
                        }
                    }
                    else if (c == k)
                    {
                        if (x == (z+1))
                        {
                            if (y == k)
                                aux3 = 5;
                        }
                    }
                }
                if (f==z)
                {
                    if (x==z)
                    {
                        if (y==(k-1))
                            aux3=5;
                        else if (y==(k+1))
                            aux3=5;
                    }
                    else if (x!=z)
                        aux3=0;
                }
            }
            else if (f==(z+1))
                aux3=0;
        }
        if (trn == 2)   //Aqui se validan saltos para las fichas blancas
        {
            if ((c==0 && f==1) || (c==0 && f==3) || (c==1 && f==4) || (c==2 && f==1) || (c==1 && f==0) || (c==1 && f==2) || (c==2 && f==3) || (c==3 && f==2) || (c==3 && f==4)
                 || (c==3 && f==0) || (c==4 && f==1) || (c==4 && f==3)) //Misma logica que la de validar mov., para decir que el salto no puede ser en diagonal
            {
                if (f == (z+1)) //En este caso por ser ficha blanca se pide una fila arriba no una fila abajo como las negras
                {
                    if (c == k)
                    {
                        if (x == (z-1))
                        {
                            if (y == k)
                                aux3 = 5;
                        }
                    }
                }
                if (f==z)                   //Misma logica que en validar mov. solo que ahora tambien se comprueba un par de coordenada mas
                {
                    if (x==z)
                    {
                        if (y==(k-1))
                            aux3=5;
                        else if (y==(k+1))
                            aux3=5;
                    }
                    else if (x!=z)
                        aux3=0;
                }
            }
            else if ((c==0 && f==0) || (c==1 && f==1)  || (c==0 && f==4) || (c==1 && f==3) || (c==2 && f==2) || (c==3 && f==1) || (c==3 && f==3) || (c==2 && f==0) || (c==2 && f==4)
                      || (c==4 && f==4) || (c==4 && f==0) || (c==4 && f==2) || (c==0 && f==2))  //Misma logica que validar mov., para decir que los saltos son en todas las direcciones
            {
                if (f == (z+1))
                {
                    if (c == (k-1))         //Se comprueba que si se puede saltar diagonalmente
                    {
                        if ( x == (z-1))
                        {
                            if (y == (k+1))
                                aux3 = 5;
                        }
                    }
                    else if (c == (k+1))
                    {
                        if (x==(z-1))			// Mismo sistema que en val_mov, solo que se solicita una coordenada mas...
                        {

                            if (y == (k-1))
                                aux3 = 5;
                        }
                    }
                    else if (c == k)
                    {
                        if (x == (z-1))
                        {
                            if (y == k)
                                aux3 = 5;
                        }
                    }
                }
                if (f==z)
                {
                    if (x==z)
                    {
                        if (y==(k-1))
                            aux3=5;
                        else if (y==(k+1))
                            aux3=5;
                    }
                    else if (x!=z)
                        aux3=0;
                }
            }
            else if (f==(z-1))
                aux3=0;
        }
        return aux3;		// Retorna valor 5 si se valida el salto, y otro valor si es que no se valida
    }
    void imprimir ()    //Funcion para imprimir la tabla auxiliar en consola, no en pantalla
    {
        int i,j;
        printf ("\n");
        for (i=0;i<FIL;i++)
        {
            for (j=0;j<COL;j++)
            {
                printf (" %c ",tabla[i][j]);
            }
            printf ("\n");
        }
        printf ("\n");
        ganador (); //Tambien aqui se llama a la funcion para comprobar ganador
    }
    void interfaz()  //Funcion para el funcionamiento del juego
    {
        static int aux,aux2,f,c,x,y,z,k,salirS=0,contB=0,contN=0; //Variables estaticas para controlar coordenadas, clicks, fichas capturadas, y cancelacion de salto
        if (trn == 1) //Si trn es 1, es turno de negras
        {
            if (click==0)   //Si no se clickeo
            {
                f=i;            //Toma los valores del click de la ficha que quiere moverse
                c=j;
                if ((c>5) || (f>5))		                // Aqui se valida que no se puede salir de la tableta
                    aux = 0;
                else if ((c<5) && (f<5))	            //Aqui se comprueba que esta coordenada contenga la ficha del usuario
                    if (tabla [f][c] == 'N')
                    {
                        aux = 5;
                        gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),j,i)), "IMG/indice.png"); //Se cambia la imagen en el tablero para indicar cual se esta moviendo
                        gtk_image_set_from_file(GTK_IMAGE(F_Mano), "IMG/Negras.png");   //Cambia la immagen de la ficha en mano para mostrale al usuario que tiene tal color de ficha en la mano
                        click = 1;      //Si el click tiene la ficha del usuario se cambia a otro click para mover la ficha
                    }
            }
            if (aux==5) //Si se valido que la ficha a mover es valida
            {
                x=i;    //Se almacena el click de a donde se quiere mover
                y=j;
                click++;
                if ((x>5)||(y>5))
                    gtk_label_set_text(GTK_LABEL(label_turno), "Fuera de los limites ");
                else if ((x<5)||(y<5))
                {
                        if (tabla [x][y] == 'B')    //Aca se comprueba si selecciono un lugar donde ya habia ficha
                        {
                            gtk_label_set_text(GTK_LABEL(label_turno), " -- Clickee la ficha la ficha contraria a saltar -- "); //Se le indica en pantalla al usuario que clickee la ficha contraria que quiere saltar
                            if (click == 3) //Cuando se detecta un click sobre la ficha contraria
                            {
                                z = x;  //Se carga la coordenada de la ficha contraria
                                k = y;
                                aux2=3; //Se cambia el valor para indicar un salto
                                gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),k,z)), "IMG/B_Marcada.png"); //Se marca en el tablero la ficha a saltar
                            }
                        }
                        else if (tabla [x][y] == ' ') //Si hay un espacio se mueve, o se salta
                        {
                            if (aux2==3) //Se indica que es un salto
                            {
                                if (val_sal (z,k,c,f,x,y,trn) == 5) // Si se valida el salto
                                {
                                    if (tabla [x][y] == ' ')
                                    {
                                        tabla [f][c] = ' ';     //Se deja vacia el lugar de la ficha a mover
                                        tabla [z][k] = ' ';     //Se deja vacia el lugar de la ficha contraria
                                        tabla [x][y] = 'N';     //Se cambia el lugar de la ficha donde se movio
                                        contB++;                //Se cuenta que se capturo una ficha blanca
                                        gchar *tempB = g_strdup_printf("%d", contB); //Se almacena la cantidad de fichas blancas capturadas
                                        gtk_label_set_text(GTK_LABEL(C_Blancas), tempB);    //Se cambia el label de cuantas fichas blancas fueron capturadas
                                        imprimir();             //Se imprime la nueva tabla auxiliar en consola                             //Mismo procedimiento que en la tabla auxiliar solo que ahora en pantalla
                                        gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),c,f)), "IMG/Nada.png");   //Se cambia la ficha de donde se movio a una imagen vacia
                                        gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),y,x)), "IMG/Negras.png"); //Se cambia la imagen donde estaba vacia a una de la ficha correspondiente
                                        gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),k,z)), "IMG/Nada.png");   //Se cambia la imagen de la ficha contraria capturada
                                        gtk_label_set_text(GTK_LABEL(label_turno), turno2); //Se indica que el turno ahora es del user2 con blancas
                                        gtk_image_set_from_file(GTK_IMAGE(F_Mano), "IMG/Puntos.png"); //Se cambia la ficha en la mano por un imagen de puntos para indicar que no se tiene nada
                                        click=2;    //Se cambia para controlar que el click ahora es del user 2
                                        aux2=0;     //Se limpia el valor para salto
                                        aux=0;      //Se limpia el valor para la ficha seleccionada
                                        trn=2;      //Se cambia de valor para cambiar de turno
                                    }
                                }
                                else if (val_sal (z,k,c,f,x,y,trn) != 5) //Aqui sic omprueba si no se valida el salto
                                {
                                    salirS++;   //A medida que el usuario clickea se aumenta la variable para salir del salto
                                    if (salirS == 5) //Una vez que se clickea 5 veces
                                    {
                                        aux2 = 0;       //Se cancela el salto
                                        salirS = 0;
                                        gtk_label_set_text(GTK_LABEL(label_estado), "Se cancela el salto"); //Se le indica en pantalla que se cancelo el salto
                                        gtk_label_set_text(GTK_LABEL(label_turno), turno1);                 //Se le indica en pantalla que sigue su turno
                                        gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),k,z)), "IMG/Blancas.png");  //Se pone la ficha marcada para salto, como una ficha normal
                                    }
                                }
                            }
                            else  //Este else es dependiente de si hay salto o no, en este caso si entra aqui no hay salto
                            {
                                if (val_mov(f,c,x,y,trn)==5)   // Se comprueba que la casilla vacia a donde se quiere mover la ficha sea de movimiento valido
                                {
                                    tabla [f][c] = ' ';     //Si es valido en la tabla auxiliar se deja vacia la ficha a mover
                                    tabla [x][y] = 'N';     //Y se cambia a el espacio donde se movio
                                    aux=0;                  //Se declara de que termino la seleccion de ficha
                                    gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),c,f)), "IMG/Nada.png");   //Se hace lo mismo que en la tabla auxiliar
                                    gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),j,i)), "IMG/Negras.png");
                                    gtk_label_set_text(GTK_LABEL(label_turno), turno2); //Se indica el turno del usuario 2
                                    gtk_image_set_from_file(GTK_IMAGE(F_Mano), "IMG/Puntos.png");
                                    click = 2;  //Se declara que el click le toca al usuario 2
                                    c = 0;
                                    f = 0;		// Se resetean los valores de coordenadas
                                    x = 0;
                                    y = 0;
                                    imprimir ();    //Se imprime en consola la tabla auxiliar
                                    trn=2;          //Se dice que el turno ahora es del user2
                                }
                                else if (val_mov(f,c,x,y,trn)!=5)   //Si el movimiento no es valido
                                {
                                    gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),c,f)), "IMG/Negras.png"); //Se cambia la imagen del indice a la de la ficha seleccionada
                                    gtk_image_set_from_file(GTK_IMAGE(F_Mano), "IMG/Puntos.png");   //Se cambia a que el usuario no tiene nada en la mano
                                    gtk_label_set_text(GTK_LABEL(label_estado), "Movimiento no Valido"); //Se muestra en pantalla que no es valido
                                    aux = 0;    //Empieza de nuevo la seleccion de ficha
                                    click = 0;  //Empieza de nuevo los clicks
                                }
                            }
                        }
                }
            }

        }
        if (trn == 2)   //Turno 2 correspondiente al usuario 2... En este if se realiza exactamente lo mismo que en trn 1
        {
            if (click==2)
            {
                f=i;
                c=j;
                if ((c>5) || (f>5))		                // Aqui se valida que no se puede salir de la tableta
                    aux = 0;
                else if ((c<5) && (f<5))	            //Aqui se comprueba que esta coordenada contenga la ficha del usuario
                    if (tabla [f][c] == 'B')
                    {
                        aux = 6;
                        gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),j,i)), "IMG/indice.png");
                        gtk_image_set_from_file(GTK_IMAGE(F_Mano), "IMG/Blancas.png");
                        click = 3;
                    }
            }
            if (aux==6)
            {
                x=i;
                y=j;
                click++;
                if ((x>5)||(y>5))
                    gtk_label_set_text(GTK_LABEL(label_turno), "Fuera de los limites ");
                else if ((x<5)||(y<5))
                {
                    if (tabla [x][y] == 'N')
                    {
                        gtk_label_set_text(GTK_LABEL(label_turno), " -- Clickee la ficha la ficha contraria a saltar -- ");
                        if (click == 5)
                        {
                            z = x;
                            k = y;
                            aux2=3;
                            gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),k,z)), "IMG/N_Marcada.png");
                        }
                    }
                    else if (tabla [x][y] == ' ')
                    {
                        if (aux2==3)
                        {
                            if (val_sal (z,k,c,f,x,y,trn) == 5)
                            {
                                if (tabla [x][y] == ' ')
                                {
                                    tabla [f][c] = ' ';
                                    tabla [z][k] = ' ';
                                    tabla [x][y] = 'B';
                                    contN++;
                                    gchar *tempN = g_strdup_printf("%d", contN); //Se almacena la cantidad de fichas negras capturadas
                                    gtk_label_set_text(GTK_LABEL(C_Negras), tempN); //Se cambia el label de cuantas fichas negras fueron capturadas
                                    imprimir();
                                    gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),c,f)), "IMG/Nada.png");
                                    gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),y,x)), "IMG/Blancas.png");
                                    gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),k,z)), "IMG/Nada.png");
                                    gtk_label_set_text(GTK_LABEL(label_turno), turno1);
                                    gtk_image_set_from_file(GTK_IMAGE(F_Mano), "IMG/Puntos.png");
                                    click=0;
                                    aux2=0;
                                    aux=0;
                                    trn=1;
                                }
                            }
                                else if (val_sal (z,k,c,f,x,y,trn) != 5)
                                {
                                    salirS++;
                                    if (salirS == 5)
                                    {
                                        aux2 = 0;
                                        salirS = 0;
                                        gtk_label_set_text(GTK_LABEL(label_estado), "Se cancela el salto");
                                        gtk_label_set_text(GTK_LABEL(label_turno), turno2);
                                        gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),k,z)), "IMG/Negras.png");
                                    }
                                }
                        }
                        else
                        {
                            if (val_mov(f,c,x,y,trn)==5)
                            {
                                tabla [f][c] = ' ';
                                tabla [x][y] = 'B';
                                aux=0;
                                gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),c,f)), "IMG/Nada.png");
                                gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),j,i)), "IMG/Blancas.png");
                                gtk_label_set_text(GTK_LABEL(label_turno), turno1);
                                gtk_image_set_from_file(GTK_IMAGE(F_Mano), "IMG/Puntos.png");
                                click = 0;
                                c = 0;
                                f = 0;		// Se asigna si la ficha hizo un mov. valido
                                x = 0;
                                y = 0;
                                imprimir ();
                                trn=1;

                            }
                            else if (val_mov(f,c,x,y,trn)!=5)
                            {
                                gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),c,f)), "IMG/Blancas.png");
                                gtk_image_set_from_file(GTK_IMAGE(F_Mano), "IMG/Puntos.png");
                                gtk_label_set_text(GTK_LABEL(label_estado), "Movimiento no Valido");
                                aux = 0;
                                click=2;
                            }
                        }
                    }
                }
            }

        }
    }
    void evento (GtkWidget *event_box, GdkEventButton *event, gpointer data) //Funcion para detectar un evento en el eventbox
    {
        i = (GUINT_FROM_LE(event->y) / 50); //Se sabe que las imagenes del grid son de 50x50pixeles
        j = (GUINT_FROM_LE(event->x) / 50);
        gchar *temp = g_strdup_printf("Presiono la imagen coordenada [%d,%d]", i,j); //Se almacena un texto concatenado a los datos de coordenadas
        gtk_label_set_text(GTK_LABEL(label_estado), temp);  //Se muestra en pantalla lo almacenado
        g_free(temp);       //Se libera memoria
        interfaz ();        //Se llama a la funcion mas importante
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                  INICIALIZACION DEL BUILDER Y EJECUCION DE CODIGO MAIN                                         //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 int main (int argc, char *argv[])
 {
     gtk_init (&argc, &argv); //Se inicia gtk
     builder = gtk_builder_new(); //Se carga el builder
     ret = gtk_builder_add_from_file(builder, "Alquerque_Glade.glade", &error);//Se carga glade
     if (ret == 0)  //Si hay un error se muestra en pantalla
     {
         g_print("Error en la funcion gtk_builder_add_from_file:\n%s", error->message);
         return 1;
     }
    ///////////////////////////////////////////////////////////////////////////////////////////
    //                                ASIGNACIONES RESPECTIVAS                               //
    ///////////////////////////////////////////////////////////////////////////////////////////
     window_main = GTK_WIDGET(gtk_builder_get_object(builder, "V_Principal"));      //Window main, asignado a Ventana Principal en glade
     window_ganador = GTK_WIDGET(gtk_builder_get_object(builder, "V_Ganador"));     //Window ganador, asignado a la ventana de ganador en glade
     window_about = GTK_WIDGET(gtk_builder_get_object(builder, "V_Acerca"));        //Window about, asignado a la ventana de acerca de los autores en glade
     tablero = GTK_WIDGET(gtk_builder_get_object(builder, "tablero"));              //tablero, asignado al grid tablero en glade
     window_reglas = GTK_WIDGET(gtk_builder_get_object(builder, "V_Reglas"));       //Window reglas, asignado a la ventana de reglas en glade
     window_play = GTK_WIDGET(gtk_builder_get_object(builder, "V_Jugar"));          //Window play, asignado a la ventana de jugar en glade
     button_rules = GTK_BUTTON(gtk_builder_get_object(builder, "b_Reglas"));        //Button reglas, asignado al boton de reglas en el menu principal en glade
     button_play = GTK_BUTTON(gtk_builder_get_object(builder, "b_Jugar"));          //Button jugar, asignado al boton jugar del menu principal en glade
     button_exit = GTK_BUTTON(gtk_builder_get_object(builder, "b_Salir"));          //Button salir, asignado al boton salir en el menu prinicpal en glade
     eventbox = GTK_WIDGET(gtk_builder_get_object(builder, "eventbox"));            //Eventbox, asignado al eventbox del tablero de glade
     label_estado = GTK_WIDGET(gtk_builder_get_object(builder, "label_estado"));    //Label estado, asignado al label del estado de partida en glade
     label_turno = GTK_WIDGET(gtk_builder_get_object(builder, "label_turno"));      //Label turno, asignado al label del turno en glade
     m_acerca = GTK_WIDGET(gtk_builder_get_object(builder, "acerca"));              //Menu acerca, asignado al submenu de acerca en glade
     m_reglas = GTK_WIDGET(gtk_builder_get_object(builder, "reglas"));              //Menu reglas, asignado al submenu de reglas en glade
     F_Mano = GTK_WIDGET(gtk_builder_get_object(builder, "F_Mano"));                //Ficha en mano, asignado a la imagen de ficha en mano de glade
     L_Winner = GTK_WIDGET(gtk_builder_get_object(builder, "L_Winner"));            //Label winner, asignado al label de la ventana ganador en glade
     I_Winner = GTK_WIDGET(gtk_builder_get_object(builder, "I_Winner"));            //Image winner, asignado a la imagen en la ventana ganador en glade
     window_nombre = GTK_WIDGET(gtk_builder_get_object(builder, "V_Nombre"));       //Ventana nombre, asignado a la ventana para ingreso de nombre de usuario en glade
     entry_user = GTK_WIDGET(gtk_builder_get_object(builder, "Entry_User"));        //Entry user, asignado al label de tipo entry en glade
     button_user = GTK_WIDGET(gtk_builder_get_object(builder, "Button_User"));      //Button user, asignado al boton de la ventana de nombre en glade
     l_user1 = GTK_WIDGET(gtk_builder_get_object(builder, "L_User"));               //Label user, asignado al label de la ventana de nombre en glade
     C_Negras = GTK_WIDGET(gtk_builder_get_object(builder, "C_Negras"));            //Captura negras, asignado al label de la ventana jugar en glade
     C_Blancas = GTK_WIDGET(gtk_builder_get_object(builder, "C_Blancas"));          //Captura blancas, asignado al label de la ventana jugar en glade
    /////////////////////////////////////////////////////////////////////////////////////////////
    //                                          SEÑALES                                        //
    /////////////////////////////////////////////////////////////////////////////////////////////

     g_signal_connect_swapped (button_rules, "clicked", G_CALLBACK (gtk_button_clicked_rules), NULL);   //Señal de que el boton de reglas fue "clickeado", y llama a la funcion respectiva
     g_signal_connect_swapped (button_exit, "clicked", G_CALLBACK (gtk_main_quit), NULL);               //Señal de que el boton de salir fue "clickeado", y llama a la funcion respectiva
     g_signal_connect_swapped (button_play, "clicked", G_CALLBACK (gtk_button_clicked_play), NULL);     //Señal de que el boton de play fue "clickeado", y llama a la funcion respectiva
     g_signal_connect (window_main, "destroy", G_CALLBACK (destroy), NULL);                 //Señal de que la ventana principal fue destruida o cerrada
     g_signal_connect (window_ganador, "destroy", G_CALLBACK (destroy), NULL);              //Señal de que la ventana ganador fue destruida
     g_signal_connect (window_play, "destroy", G_CALLBACK (destroy), NULL);                 //Señal de que la ventana play fue destruida
     g_signal_connect (eventbox, "button-press-event", G_CALLBACK(evento), tablero);        //Señal de que hubo un "button press event", en el eventbox, y llama a la funcion respectiva
     g_signal_connect (m_acerca, "activate", G_CALLBACK (Acerca), NULL);                    //Señal de que el submenu de acerca fue "activado", y llama a la funcion respectiva
     g_signal_connect (m_reglas, "activate", G_CALLBACK (Reglas), NULL);                    //Señal de que el submenu de reglas fue "activado", y llama a la funcion resprectiva
     g_signal_connect(G_OBJECT(window_reglas),"delete-event", G_CALLBACK(on_widget_deleted), NULL);     //Señal de que la ventana de reglas fue "eliminada", y llama a la funcion respectiva para ocultarla
     g_signal_connect_swapped (G_OBJECT(button_user),"clicked", G_CALLBACK(on_btn_clicked_user), NULL); //Señal de que se "clickeo" el boton en la ventana de ingreso de nombre de usuario, y llama a la funcion respectivamente
    //////////////////////////////////////////////////////////////////////////////////////////////
    //                               EJECUCION DEL CODIGO CONSTANTEMENTE                        //
    //////////////////////////////////////////////////////////////////////////////////////////////
     srand (time(NULL)); //Utilizado para la semilla de nros. random
     gtk_main();        //Se inicia el programa GTK
     return 0;          //Retorno de 0 si no hay errores
 }
