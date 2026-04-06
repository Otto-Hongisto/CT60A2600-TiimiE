#include <stdio.h>
#include <stdlib.h>
#include "yleinen.h"
#include "lista.h"
#include "puu.h"

/// @brief linkitetyn listan toimintavalikko
void listaValikko()
{
    NIMILISTA *pAlku = NULL; // for linked list
    int toimintoValinta = 0;
    do
    {
        toimintoValinta = toimintoValikkoLista();

        switch (toimintoValinta)
        {
        case 1:
        {
            char *tiedostonNimi = tiedostoNimi();
            pAlku = lueTiedotLista(tiedostonNimi);
            free(tiedostonNimi);
            tiedostonNimi = NULL;
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
        case 5:
            bubbleSortNouseva(pAlku);
            break;
        case 6:
            pAlku = insertionSortLaskeva(pAlku);
            break;
        case 7:
        {
            int indexUusi = 0;
            int nimiLkmUusi = 0;
            char uusiNimi[30];
            printf("Mihin indexiin lisätään: ");
            scanf("%d", &indexUusi);
            printf("Anna lisättävä nimi: ");
            scanf("%s", uusiNimi);
            printf("Anna lisättävä lukumäärä: ");
            scanf("%d", &nimiLkmUusi);
            lisaaAlkioListaan(&pAlku, indexUusi, uusiNimi, nimiLkmUusi);
            break;
        }
        case 8:
        {
            char syote[50];
            printf("Anna poistettava nimi tai numero: "); // Kysytään käyttäjältä nimi tai numero
            scanf("%s", syote);
            pAlku = poistaLinkitetystaListasta(pAlku, syote);
            break;
        }
        case 0:
            break;
        default:
            printf("Tuntematon valinta, yritä uudestaan.\n");
            break;
        }
    } while (toimintoValinta != 0);

    pAlku = tyhjennaMuisti(pAlku);
    pAlku = NULL;
    printf("Muisti vapautettu.");

    return;
}

/// @brief Binääripuun toimintavalikko
void puuValikko()
{
    int toimintoValinta = 0;
    NIMIPUU *pJuuri = NULL; // for binary tree
    do
    {
        toimintoValinta = toimintoValikkoPuu();

        switch (toimintoValinta)
        {
        case 1:
            pJuuri = lueTiedotPuu();
            break;
        case 2:
        {
            char *tulostaTiedosto = tiedostoNimi();
            tulostaPuu(pJuuri, tulostaTiedosto);
            free(tulostaTiedosto);
            break;
        }
        case 3:
        {
            int numero = kysyNumero();
            char *syvyysTiedosto = tiedostoNimi();
            syvyysHakuPuu(numero, pJuuri, syvyysTiedosto);
            free(syvyysTiedosto);
            break;
        }
        case 4:
        {
            char haettavaNimi[30];
            kysyNimi(haettavaNimi);
            char *nimi = tiedostoNimi();
            leveysHaku(pJuuri, nimi, haettavaNimi);
            free(nimi);
        }
        break;
        case 5:
        {
            char *binaariHakuTiedosto = tiedostoNimi();
            int binaariHakuNumero = kysyNumero();
            binaariHaku(pJuuri, binaariHakuNumero, binaariHakuTiedosto);
            free(binaariHakuTiedosto);
            break;
        }
        case 6:
        {
            char syote[30];
            int numero;

            kysyNimi(syote);
            int tulos = onkoNumero(syote);
            if (tulos == 1)
            {
                numero = atoi(syote);
                pJuuri = poistaNodePuustaNumerolla(pJuuri, numero);
                break;
            }
            else
            {
                pJuuri = poistaNodePuustaNimella(pJuuri, syote);
            }
            break;
        }

        case 0:
            tyhjennaPuu(pJuuri);
            pJuuri = NULL;
            printf("Muisti vapautettu.");
            break;
        default:
            printf("Tuntematon toiminto, yritä uudestaan.\n");
            break;
        }
    } while (toimintoValinta != 0);
    return;
}

/// @brief päävalikkorakenne
/// @return 
int main()
{
    int struktuurivalinta = 0; // 1 = linkitetty lista, 2 = binääripuu

    do
    {
        struktuurivalinta = struktuuriValikko();
        if (struktuurivalinta == 1) { //Linkitetty lista
            listaValikko();
        } else if (struktuurivalinta == 2) { //binääripuu
            puuValikko();
        } else if (struktuurivalinta == 0) {
            break;
        } else {
            printf("Tuntematon Valinta, yritä uudestaan.\n");
        }
    } while (struktuurivalinta != 0);

    printf("\n");
    printf("Kiitos ohjelman käytöstä.");

    return (0);
}

