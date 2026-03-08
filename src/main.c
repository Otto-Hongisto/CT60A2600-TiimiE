#include <stdio.h>
#include "kirjasto.h"

int main()
{

    NIMILISTA *pAlku = NULL;
    int valinta = 0;

    do
    {
        valinta = valikko();
        printf("\n");

        switch (valinta)
        {
        case 1:
            pAlku = lueTiedot();
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
            printf("Lopetetaan...");
            break;
        default:
            printf("Tuntematon valinta, yritä uudestaan.\n");
            break;
        }

    } while (valinta != 0);

    pAlku = tyhjennaMuisti(pAlku);
    pAlku = NULL;

    printf("\n");
    printf("Kiitos ohjelman käytöstä.");

    return (0);
}
