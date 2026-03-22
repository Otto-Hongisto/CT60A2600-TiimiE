#include "unity.h"

// Declare test functions from other files
void varaaMuistifieldit(void);
void lisaaNodePuuhunTesti(void);
void luoKokoPuu(void);
void binaariHakuEiLoydaTest(void);
void binaariHakuTest(void);
void poistaLeafNode(void);

void test_varaaMuistiLista(void);
void test_lueTiedotLista(void);
void test_lueTiedotLista_links_nodes_correctly(void);

void setUp(void) {}
void tearDown(void) {}

int main(void)
{
    UNITY_BEGIN();

    // puutesti.c tests
    RUN_TEST(varaaMuistifieldit);
    RUN_TEST(lisaaNodePuuhunTesti);
    RUN_TEST(luoKokoPuu);
    RUN_TEST(binaariHakuEiLoydaTest);
    RUN_TEST(binaariHakuTest);
    RUN_TEST(poistaLeafNode);   

    // listatesti.c tests
    RUN_TEST(test_varaaMuistiLista);
    RUN_TEST(test_lueTiedotLista);
    RUN_TEST(test_lueTiedotLista_links_nodes_correctly);

    return UNITY_END();
}
