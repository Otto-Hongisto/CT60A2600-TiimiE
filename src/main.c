#include <stdio.h>
#include "kirjasto.h"

int main()
{

    NIMILISTA *pAlku = NULL;
    int toimintoValinta = 0;
    int struktuurivalinta = 0; // 1 = linkitetty lista, 2 = binääripuu

    do
    {
        struktuurivalinta = struktuuriValikko();
        if (struktuurivalinta == 1) { //Linkitetty lista
            do
            {
                toimintoValinta = toimintoValikko();
                printf("\n");

                switch (toimintoValinta)
                {
                case 1:
                    pAlku = lueTiedotLista();
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
                toimintoValinta = toimintoValikko();
                printf("\n");

                switch (toimintoValinta)
                {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 0:
                    break;
                default:
                    printf("Tuntematon toimintoValinta, yritä uudestaan.\n");
                    break;
                }
            } while (toimintoValinta != 0);

        } else if (struktuurivalinta == 0) {
            break;
        } else {
            printf("Tuntematon toimintoValinta, yritä uudestaan.\n");
        }
    }
    while (struktuurivalinta);

    pAlku = tyhjennaMuisti(pAlku);
    pAlku = NULL;

    printf("\n");
    printf("Kiitos ohjelman käytöstä.");

    return (0);
}
