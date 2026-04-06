#include "unity.h"

// Declare test functions from other files
void test_varaaMuistifieldit(void);
void test_lisaaNodePuuhun(void);
void test_luoKokoPuu(void);
void test_binaariHakuEiLoyda(void);
void test_binaariHaku(void);
void test_poistaLeafNode(void);
void test_rotaatiot(void);

void test_varaaMuistiLista(void);
void test_lueTiedotLista(void);
void test_lueTiedotListaLinksNodesCorrectly(void);
void test_poistaLinkitetystaListasta(void);
void test_poistaLinkitetystaListastaVaaraInput(void);
void test_VirheellinenIndex(void);
void test_LisaaListanAlkuun(void);
void test_LisaaListanKeskelle(void);
void test_bubbleSortNouseva(void);
void test_insertionSortLaskeva(void);

void setUp(void) {}
void tearDown(void) {}

int main(void)
{
    UNITY_BEGIN();

    // puutesti.c tests
    RUN_TEST(test_varaaMuistifieldit);
    RUN_TEST(test_lisaaNodePuuhun);
    RUN_TEST(test_luoKokoPuu);
    RUN_TEST(test_binaariHakuEiLoyda);
    RUN_TEST(test_binaariHaku);
    RUN_TEST(test_poistaLeafNode);
    RUN_TEST(test_rotaatiot);

    // listatesti.c tests
    RUN_TEST(test_varaaMuistiLista);
    RUN_TEST(test_lueTiedotLista);
    RUN_TEST(test_lueTiedotListaLinksNodesCorrectly);
    RUN_TEST(test_poistaLinkitetystaListasta);
    RUN_TEST(test_poistaLinkitetystaListastaVaaraInput);
    RUN_TEST(test_VirheellinenIndex);
    RUN_TEST(test_LisaaListanAlkuun);
    RUN_TEST(test_LisaaListanKeskelle);
    RUN_TEST(test_bubbleSortNouseva);
    RUN_TEST(test_insertionSortLaskeva);

    return UNITY_END();
}
