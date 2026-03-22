#include "unity.h"
#include "puukirjasto.h"
#include <stdlib.h>
#include <string.h>

// Test 1
void varaaMuistifieldit(void)
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
void lisaaNodePuuhunTesti(void)
{
    NIMIPUU *root = NULL;
    NIMIPUU *node = varaaMuistiPuu();
    node->nimiLkm = 10;

    root = lisaaNodePuuhun(root, node);

    TEST_ASSERT_EQUAL_PTR(node, root);
}

// Test 3
void luoKokoPuu(void)
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
void binaariHakuEiLoydaTest(void)
{
    NIMIPUU *root = NULL;

    NIMIPUU *node = varaaMuistiPuu();
    node->nimiLkm = 10;

    root = lisaaNodePuuhun(root, node);

    NIMIPUU *found = binaariHaku(root, 20, "/dev/null");
    TEST_ASSERT_NULL(found);
    tyhjennaPuu(root);
}

//Test 5
void binaariHakuTest(void)
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

    char *tiedosto = "test.txt"; 
    NIMIPUU *found = binaariHaku(root, 15, tiedosto);

    // tarkistetaan tulokset
    TEST_ASSERT_NOT_NULL(found);
    TEST_ASSERT_EQUAL(15, found->nimiLkm);
    TEST_ASSERT_EQUAL_STRING("G", found->nimi);
}