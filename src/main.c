#include <stdio.h>
#include "kirjasto.h"

int main()
{

    NIMILISTA *pAlku;
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
            break;
        case 3:
            break;
        case 4:
            break;
        case 0:
            break;
        default:
            printf("Tuntematon valinta, yritä uudestaan.\n");
            break;
        }

    } while (valinta != 0);

    //tyhjennaMuisti(pAlku);
    //pAlku = NULL;

    printf("\n");
    printf("Kiitos ohjelman käytöstä.");

    return (0);
}
