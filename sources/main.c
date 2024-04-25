#include <stdio.h> // Menús + interacció per terminal.
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "estructures.h"
#include "back_functions.h"
#include "interface_functions.h"

// Calen definir correctament les capceleres i paràmetres.
int main(int argc, char *argv[])
{
    if (argc != 2) // No s'ha passat com a paràmetre l'identificador de l'usuari.
        falta_identificador();
    else
    {
        char o;                                               // Opció seleccionada per l'usuari.
        persona_t *usuaris;                                   // Punter a taula d'usuaris.
        short n_elem = carregar_usuaris(&usuaris);            // Nombre d'usuaris registrats al sistema.
        if (n_elem == -1)
            missatge_error_arxiu_usuaris();
        else
        {
            short usuari = obtenir_usuari(argv, n_elem);          // Id de l'usuari que ha iniciat el programa.
            if (usuari == -1)
                usuari_inexistent();
            else
            {
                ini_llavor();
                char *amistats;                                           // Punter a taula d'amistats.
                bool usuaris_editats = false, amistats_editades = false; // Booleans per controlar l'edició de les dades.
                if (!carregar_amistats(&amistats))
                    missatge_error_arxiu_amistats();
                else
                {
                    missatge_benvinguda();
                    do
                    {
                        mostrar_menu_principal();
                        o = (char)demanar_opcio(AFEGIR_USUARI, EXIT);
                        switch (o)
                        {
                        case MOSTRAR_PERFIL_USUARI:
                            mostrar_perfil(usuari, usuaris);
                            sortir_menu();
                            break;
                        case MOSTRAR_AMISTATS:
                            // mostrar_amistats();
                            printf("mostrar_amistats()");
                            sortir_menu(); // Implementar en mostrar amistats.
                            break;
                        case AFEGIR_AMISTAT:
                            afegir_amistat(usuaris, &amistats, n_elem, usuari);
                            amistats_editades = true;
                            sortir_menu();
                            break;
                        case ELIMINAR_AMISTAT:
                            eliminar_amistat(&amistats, n_elem, usuari);
                            amistats_editades = true;
                            sortir_menu();
                            break;
                        case AFEGIR_USUARI:
                            n_elem = afegir_usuaris(&usuaris, &amistats, n_elem);
                            usuaris_editats = mirar_errors(n_elem);
                            sortir_menu();
                            break;
                        netejar_terminal(); // Es neteja la terminal per facilitar la lectura del programa.
                        } // Es podria afegir cas DEFAULT, però com el rang de o està controlat (per funció demanar_opcio) no cal.
                    } while (o != EXIT);
                    if ((amistats_editades || usuaris_editats) && !guardar_dades(usuaris, amistats, n_elem, usuaris_editats, amistats_editades))
                        error_guardat_dades();
                    alliberacio_memoria(usuaris, amistats, n_elem);
                    missatge_acomiadament();
                }
            } 
        }
        
    }

    return 0;
}