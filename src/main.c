#include <stdio.h>
#include <stdlib.h>
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
                    NIMIPUU *hakuTulos = NULL;
                    char *binaariHakuTiedosto = tiedostoNimi();
                    int binaariHakuNumero = kysyNumero();
                    hakuTulos = binaariHaku(pJuuri, binaariHakuNumero, binaariHakuTiedosto);
                    free(binaariHakuTiedosto);
                    break;
                }
                case 6:
                {
                    char syote[30];
                    int numero;

                    kysyNimi(syote);
                    int tulos = onkoNumero(syote);
                    if (tulos == 1) {
                        numero = atoi(syote);
                        pJuuri = poistaNodePuustaNumerolla(pJuuri, numero);
                        break;
                    }
                    else {
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
