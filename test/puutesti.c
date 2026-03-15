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

void tyhjennaPuuTesti() {
    NIMIPUU *root = NULL;

    // Luo seittemän solmua
    NIMIPUU *numero1 = varaaMuistiPuu();
    numero1->nimiLkm = 4;
    NIMIPUU *numero2 = varaaMuistiPuu();
    numero2->nimiLkm = 2;
    NIMIPUU *numero3 = varaaMuistiPuu();
    numero3->nimiLkm = 1;
    NIMIPUU *numero4 = varaaMuistiPuu();
    numero4->nimiLkm = 9;
    NIMIPUU *numero5 = varaaMuistiPuu();
    numero5->nimiLkm = 3;
    NIMIPUU *numero6 = varaaMuistiPuu();
    numero6->nimiLkm = 2;
    NIMIPUU *numero7 = varaaMuistiPuu();
    numero7->nimiLkm = 12;

    //luo puu
    root = lisaaNodePuuhun(root, numero1);
    lisaaNodePuuhun(root, numero2);
    lisaaNodePuuhun(root, numero3);
    lisaaNodePuuhun(root, numero4);
    lisaaNodePuuhun(root, numero5);
    lisaaNodePuuhun(root, numero6);
    lisaaNodePuuhun(root, numero7);

    tyhjennaPuu(root);
    root = NULL;
    TEST_ASSERT_NULL(root);
}

