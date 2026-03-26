#include "unity.h"
#include "listakirjasto.h"
#include <string.h>
#include <stdlib.h>

#define TEST_FILE "data/miehet_2025.txt"

// free list memory
// Test 1
static void freeList(NIMILISTA *p)
{
    while (p)
    {
        NIMILISTA *next = p->pNext;
        free(p->nimi);
        free(p);
        p = next;
    }
}

// Test 2
void test_varaaMuistiLista(void)
{
    NIMILISTA *p = varaaMuistiLista();
    TEST_ASSERT_NOT_NULL(p);
    free(p);
}


// Test 3
void test_lueTiedotLista(void)
{
    NIMILISTA *lista = lueTiedotLista(strdup(TEST_FILE));
    TEST_ASSERT_NOT_NULL(lista);

    const char *nimet[] = {"Juhani", "Olavi", "Tapani", "Antero", "Johannes"};
    const int odotetutLkm[] = {275071, 137393, 133098, 131502, 130996};

    NIMILISTA *ptr = lista;
    int indeksi = 0;

    // Tarkistaa 5 ensimmäistä listan elementtiä
    while (ptr && indeksi < 5)
    {
        TEST_ASSERT_EQUAL_STRING(nimet[indeksi], ptr->nimi);
        TEST_ASSERT_EQUAL(odotetutLkm[indeksi], ptr->nimiLkm);
        ptr = ptr->pNext;
        indeksi++;
    }

    TEST_ASSERT_EQUAL(5, indeksi); //tarkistaa, että viisi elementtiä on löydetty

    freeList(lista);
}

// Test 4
void test_lueTiedotLista_links_nodes_correctly(void)
{
    NIMILISTA *lista = lueTiedotLista(strdup(TEST_FILE));
    TEST_ASSERT_NOT_NULL(lista);

    NIMILISTA *ensimmainen = lista;
    NIMILISTA *toinen = lista->pNext;

    TEST_ASSERT_NOT_NULL(toinen);
    TEST_ASSERT_EQUAL_PTR(ensimmainen, toinen->pPrev);

    // Walk to last
    NIMILISTA *pointer = lista;
    while (pointer->pNext)
        pointer = pointer->pNext;

    TEST_ASSERT_NULL(pointer->pNext);
    TEST_ASSERT_NOT_NULL(pointer->pPrev);

    freeList(lista);
}


// Test 6
/// @brief Poistaa listasta solmun ja varmistaa että rakenne pysyy oikeena
void test_poistaLinkitetystaListasta(void)
{
    NIMILISTA *lista = lueTiedotLista(strdup(TEST_FILE));
    TEST_ASSERT_NOT_NULL(lista);

    // Poistaa listan ensimmäisen solmun
    lista = poistaLinkitetystaListasta(lista);
    TEST_ASSERT_NOT_NULL(lista);
    TEST_ASSERT_EQUAL_STRING("Olavi", lista->nimi);
    TEST_ASSERT_NULL(lista->pPrev);

    freeList(lista);
}

