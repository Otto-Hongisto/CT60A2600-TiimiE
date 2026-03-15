#include <stdio.h>
#include "yleinenkirjasto.h"
#include "listakirjasto.h"
#include "puukirjasto.h"

int main()
{
    int numero = 0; //for binary tree searches
    NIMILISTA *pAlku = NULL; // for linked list
    NIMIPUU *pJuuri = NULL; // for binary tree
    int struktuurivalinta = 0; // 1 = linkitetty lista, 2 = binääripuu
    int toimintoValinta = 0;

    do
    {
        struktuurivalinta = struktuuriValikko();
        if (struktuurivalinta == 1) { //Linkitetty lista
            do
            {
                toimintoValinta = toimintoValikkoLista();

                switch (toimintoValinta)
                {
                case 1:
                    {
                        char *tiedostonNimi = tiedostoNimi();
                        pAlku = lueTiedotLista(tiedostonNimi);
                    }
                    break;
                case 2:
                    kirjoitaTiedosto(pAlku);
                    break;
                case 3:
                    kirjoitaTiedostoTakaperin(pAlku);
                    break;
                case 4:
                    pAlku = tyhjennaMuisti(pAlku);
                    break;
                case 0:
                    break;
                default:
                    printf("Tuntematon toimintoValinta, yritä uudestaan.\n");
                    break;
                }
            } while (toimintoValinta != 0);

        } else if (struktuurivalinta == 2) { //binääripuu
            do
            {    
                toimintoValinta = toimintoValikkoPuu();

                switch (toimintoValinta)
                {
                case 1:
                    pJuuri = lueTiedotPuu();
                    break;
                case 2:
                    tulostaPuu(pJuuri);
                    break;
                case 3:
                    numero = kysyNumero();
                    syvyysHakuPuu(numero, pJuuri);
                    break;
                case 4:
                    break;
                case 5:
                    tulostaPuu(pJuuri);
                    break;
                case 0:
                    break;
                default:
                    printf("Tuntematon toiminto, yritä uudestaan.\n");
                    break;
                }
            } while (toimintoValinta != 0);

        } else if (struktuurivalinta == 0) {
            break;
        } else {
            printf("Tuntematon Valinta, yritä uudestaan.\n");
        }
    } while (struktuurivalinta != 0);

    pAlku = tyhjennaMuisti(pAlku);
    pAlku = NULL;

    printf("\n");
    printf("Kiitos ohjelman käytöstä.");

    return (0);
}
