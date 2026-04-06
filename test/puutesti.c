#include "unity.h"
#include "puu.h"
#include <stdlib.h>
#include <string.h>

// Test 1
void test_varaaMuistifieldit(void)
{
    NIMIPUU *node = varaaMuistiPuu();

    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_NULL(node->nimi);
    TEST_ASSERT_EQUAL(0, node->nimiLkm);
    TEST_ASSERT_NULL(node->pVasen);
    TEST_ASSERT_NULL(node->pOikea);

    free(node);
}

// Test 2
void test_lisaaNodePuuhun(void)
{
    NIMIPUU *root = NULL;
    NIMIPUU *node = varaaMuistiPuu();
    node->nimiLkm = 10;

    root = lisaaNodePuuhun(root, node);

    TEST_ASSERT_EQUAL_PTR(node, root);
}

// Test 3
void test_luoKokoPuu(void)
{
    NIMIPUU *root = NULL;

    // CLuo seittemän solmua
    NIMIPUU *numero1 = varaaMuistiPuu();
    numero1->nimiLkm = 5;
    NIMIPUU *numero2 = varaaMuistiPuu();
    numero2->nimiLkm = 3;
    NIMIPUU *numero3 = varaaMuistiPuu();
    numero3->nimiLkm = 7;
    NIMIPUU *numero4 = varaaMuistiPuu();
    numero4->nimiLkm = 2;
    NIMIPUU *numero5 = varaaMuistiPuu();
    numero5->nimiLkm = 4;
    NIMIPUU *numero6 = varaaMuistiPuu();
    numero6->nimiLkm = 6;
    NIMIPUU *numero7 = varaaMuistiPuu();
    numero7->nimiLkm = 8;

    /*
    Odotettu rakenne:

             5
            /  \
          3     7
         / \    / \
       2    4  6   8
    */

    root = lisaaNodePuuhun(root, numero1);
    lisaaNodePuuhun(root, numero2);
    lisaaNodePuuhun(root, numero3);
    lisaaNodePuuhun(root, numero4);
    lisaaNodePuuhun(root, numero5);
    lisaaNodePuuhun(root, numero6);
    lisaaNodePuuhun(root, numero7);

    // varmistaa rakenteen
    TEST_ASSERT_EQUAL_PTR(numero2, root->pVasen);
    TEST_ASSERT_EQUAL_PTR(numero3, root->pOikea);
    TEST_ASSERT_EQUAL_PTR(numero4, root->pVasen->pVasen);
    TEST_ASSERT_EQUAL_PTR(numero5, root->pVasen->pOikea);
    TEST_ASSERT_EQUAL_PTR(numero6, root->pOikea->pVasen);
    TEST_ASSERT_EQUAL_PTR(numero7, root->pOikea->pOikea);
}

//Test 4
void test_binaariHakuEiLoyda(void)
{
    NIMIPUU *root = NULL;

    NIMIPUU *node = varaaMuistiPuu();
    node->nimiLkm = 10;

    root = lisaaNodePuuhun(root, node);

    NIMIPUU *found = binaariHaku(root, 20, "bin/not_found");
    TEST_ASSERT_NULL(found);
    tyhjennaPuu(root);
}

//Test 5
void test_binaariHaku(void)
{
    NIMIPUU *root = NULL;

    // luodaan pieni puu
    NIMIPUU *node1 = varaaMuistiPuu();
    node1->nimiLkm = 10;
    node1->nimi = malloc(6); 
    strcpy(node1->nimi, "A");

    NIMIPUU *node2 = varaaMuistiPuu();
    node2->nimiLkm = 5;
    node2->nimi = malloc(5); 
    strcpy(node2->nimi, "B");

    NIMIPUU *node3 = varaaMuistiPuu();
    node3->nimiLkm = 15;
    node3->nimi = malloc(6); 
    strcpy(node3->nimi, "G");

    // lisätään solmut
    root = lisaaNodePuuhun(root, node1);
    lisaaNodePuuhun(root, node2);
    lisaaNodePuuhun(root, node3);

    char *tiedosto = "bin/test.txt"; 
    NIMIPUU *found = binaariHaku(root, 15, tiedosto);

    // tarkistetaan tulokset
    TEST_ASSERT_NOT_NULL(found);
    TEST_ASSERT_EQUAL(15, found->nimiLkm);
    TEST_ASSERT_EQUAL_STRING("G", found->nimi);
}

// Test 6
/// @brief Poistaa leaf node puusta ja varmistaa että rakenne säilyy
void test_poistaLeafNode(void)
{
    NIMIPUU *root = NULL;

    // Luo kolme nodea, joilla nimi ja luku
    NIMIPUU *n1 = varaaMuistiPuu();
    n1->nimi = strdup("A"); // strdup varaa muistia ja kopioi merkkijonon, kuten malloc + strcpy
    n1->nimiLkm = 12;
    NIMIPUU *n2 = varaaMuistiPuu();
    n2->nimi = strdup("B");
    n2->nimiLkm = 10;
    NIMIPUU *n3 = varaaMuistiPuu();
    n3->nimi = strdup("C");
    n3->nimiLkm = 15;

    // Lisää nodet puuhun
    root = lisaaNodePuuhun(root, n1);
    root = lisaaNodePuuhun(root, n2);
    root = lisaaNodePuuhun(root, n3);

    // Poistaa leaf noden n2
    root = poistaNodePuustaNumerolla(root, 10);

    // varmistaa rakenteen
    TEST_ASSERT_NULL(root->pVasen);
    TEST_ASSERT_EQUAL_PTR(n3, root->pOikea);

    // Vapauttaa muistia
    free(n1->nimi); free(n1);
    free(n3->nimi); free(n3);
}

// test 7
void test_rotaatiot(void)
{
    // LL-tilanne eli oikea rotaatio vasemman ylijuoksun takia
    NIMIPUU *root = NULL;

    NIMIPUU *n3 = varaaMuistiPuu();
    n3->nimiLkm = 30;
    NIMIPUU *n2 = varaaMuistiPuu();
    n2->nimiLkm = 20;
    NIMIPUU *n1 = varaaMuistiPuu();
    n1->nimiLkm = 10;

    root = lisaaNodePuuhun(root, n3);
    root = lisaaNodePuuhun(root, n2);
    root = lisaaNodePuuhun(root, n1);

    TEST_ASSERT_EQUAL_PTR(n2, root);
    TEST_ASSERT_EQUAL_PTR(n1, root->pVasen);
    TEST_ASSERT_EQUAL_PTR(n3, root->pOikea);

    // RR-tilanne eli vasen rotaatio oikean overflown takia
    root = NULL;

    NIMIPUU *n1b = varaaMuistiPuu();
    n1b->nimiLkm = 10;
    NIMIPUU *n2b = varaaMuistiPuu();
    n2b->nimiLkm = 20;
    NIMIPUU *n3b = varaaMuistiPuu();
    n3b->nimiLkm = 30;

    root = lisaaNodePuuhun(root, n1b);
    root = lisaaNodePuuhun(root, n2b);
    root = lisaaNodePuuhun(root, n3b); 

    TEST_ASSERT_EQUAL_PTR(n2b, root);
    TEST_ASSERT_EQUAL_PTR(n1b, root->pVasen);
    TEST_ASSERT_EQUAL_PTR(n3b, root->pOikea);
}
