#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>

#define SMALL_TEST_NUM 5

static int smallTestIntArr[] = {
    1, 2, 3, 4, 5
};

    // For function pointers

void freeItem(void* pItem) {
    free(pItem);
    pItem = NULL;
}

// Doesn't actually free anything; to be used on tests
// where the client-code will free the heap memory 
void freeItemVoid(void * pItem) {
    pItem = NULL;
}

bool isItemEqual(void* pItem, void* pComparisonArg) {
    if (pItem == NULL || pComparisonArg == NULL){
        return false;
    }
    return (*(int*)pItem == *(int*)pComparisonArg);
}
    
    // Helper functions for testing
int * createSmallTestArr() {
    int * pIntArr = (int*)malloc(SMALL_TEST_NUM * sizeof(int));
    if(pIntArr == NULL) {
        printf("list_first_test FAILED!\n");
        return NULL;
    }
    for (unsigned int i = 0; i < SMALL_TEST_NUM; i++) {
        pIntArr[i] = smallTestIntArr[i];
    }
    return pIntArr;
}

void printList(List * pList) {
    pList->pCurrentItemNode = pList->pHead;
    printf("{ ");
    while (pList->pCurrentItemNode != NULL) {
        int item = *(int*)pList->pCurrentItemNode->pItem;
        printf("%d, ", item);
        pList->pCurrentItemNode = pList->pCurrentItemNode->pNext;
    }
    printf("}\n");
    printf("List size = %d\n", pList->size);
}

    // Tests
void list_create_test() {
    List * pList = List_create();
    assert(pList != NULL);
    assert(pList->pHead == LIST_OOB_START);
    assert(pList->size == 0);
    assert(pList->pCurrentItemNode == NULL);

    printf("\tlist_create_test() \tPASSED!\n");
    List_free(pList, freeItem);
    printf("\ttest list has been freed\n");
}

void list_count_test() {
    List * pList = List_create();
    assert(pList != NULL);
    
    int currentListSize = pList->size;
    assert(currentListSize == 0);
    // Test to see if size can be increased and decreased
    pList->size++;
    assert(pList->size == currentListSize + 1);
    pList->size--;
    assert(pList->size == currentListSize);

    printf("\tlist_count_test() \tPASSED!\n");
    List_free(pList, freeItem);
    printf("\ttest list has been freed\n");
}

void list_first_test() {
    int * pIntArr = createSmallTestArr();
    List * pList = List_create();
    unsigned int i = 0;
    assert(pIntArr != NULL);
    assert(pList != NULL);

    // CASE: Only 1 item in list
    int firstItem = pIntArr[0];
    List_append(pList, (void*)&pIntArr[i++]);
    assert( *(int*)List_first(pList) == firstItem );
     
    // CASE: Test for mutiple items in list
    for (; i < SMALL_TEST_NUM; i++) {
        List_prepend(pList, (void*)&pIntArr[i]);
    }
    int lastItem = pIntArr[SMALL_TEST_NUM - 1];
    assert( *(int*)List_first(pList) == lastItem );
   
    printf("\tlist_first_test() \tPASSED!\n");
    List_free(pList, freeItemVoid);
    free(pIntArr);
    printf("\ttest list has been freed\n");
}

void list_last_test() {
    int * pIntArr = createSmallTestArr();
    List * pList = List_create();
    unsigned int i = 0;
    assert(pIntArr != NULL);
    assert(pList != NULL);

    // CASE: Only 1 item in list
    int firstItem = pIntArr[0];
    List_append(pList, (void*)&pIntArr[i++]);
    assert( *(int*)List_last(pList) == firstItem );
     
    //CASE: Test for mutiple items in list
    for (; i < SMALL_TEST_NUM; i++) {
        List_append(pList, (void*)&pIntArr[i]);
    }
    int lastItem = pIntArr[SMALL_TEST_NUM - 1];
    assert( *(int*)List_last(pList) == lastItem );
   
    printf("\tlist_last_test() \tPASSED!\n");
    List_free(pList, freeItemVoid);
    free(pIntArr);
    printf("\ttest list has been freed\n");
}

void list_next_prev_test() {
    int * pInt1 = malloc(sizeof(int));
    int * pInt2 = malloc(sizeof(int));
    *(int*)pInt1 = 11;
    *(int*)pInt2 = 22;
    assert(pInt1 != NULL);
    assert(pInt2 != NULL);
    List * pList = List_create();
    assert(pList != NULL);


    // CASE: Only 1 item in list
    List_append(pList, pInt1);
    assert( *(int*)List_curr(pList) == *pInt1);
    assert(pList->currentPtrStatus == LIST_OOB_START);
    void * pPrev = List_prev(pList);
    assert(pPrev == NULL);
    assert(pList->currentPtrStatus == LIST_OOB_START);

    List_next(pList);
    void * pNext = List_next(pList);
    assert(pNext == NULL);
    assert(pList->currentPtrStatus == LIST_OOB_END);

    // CASE: More than 1 item
    List_append(pList, pInt2);
    pPrev = List_prev(pList);
    assert(*(int*)pPrev == *(int*)pInt1);

    pNext = List_next(pList);
    assert(*(int*)pNext == *(int*)pInt2);

    // Clean up
    printf("\tlist_next_prev_test() \tPASSED!\n");
    List_free(pList, freeItem);
    printf("\ttest list has been freed\n");
}

void list_insert_after_test() {
    int * pInt1 = malloc(sizeof(int));
    int * pInt2 = malloc(sizeof(int));
    *(int*)pInt1 = 11;
    *(int*)pInt2 = 22;
    assert(pInt1 != NULL);
    assert(pInt2 != NULL);
    List * pList = List_create();
    assert(pList != NULL);

    // CASE: empty list
    int first_result = List_insert_after(pList, pInt1);
    assert(first_result == 0);
    assert(*(int*)List_curr(pList) == *(int*)pInt1);
    assert(List_count(pList) == 1);
    
    // CASE: normal case
    int second_result = List_insert_after(pList, pInt2);
    assert(second_result == 0);
    assert(*(int*)List_curr(pList) == *(int*)pInt2);
    assert(List_count(pList) == 2);

    // Clean up
    printf("\tlist_insert_after_test() \tPASSED!\n");
    List_free(pList, freeItem);
    printf("\ttest list has been freed\n");
}

void list_insert_before_test() {
    int * pInt1 = malloc(sizeof(int));
    int * pInt2 = malloc(sizeof(int));
    *(int*)pInt1 = 11;
    *(int*)pInt2 = 22;
    assert(pInt1 != NULL);
    assert(pInt2 != NULL);
    List * pList = List_create();
    assert(pList != NULL);

    // CASE: empty list
    int first_result = List_insert_before(pList, pInt1);
    assert(first_result == 0);
    assert(*(int*)List_curr(pList) == *(int*)pInt1);
    assert(List_count(pList) == 1);
    
    // CASE: normal case
    int second_result = List_insert_before(pList, pInt2);
    assert(second_result == 0);
    assert(*(int*)List_first(pList) == *(int*)pInt2);
    assert(List_count(pList) == 2);

    // Clean up
    printf("\tlist_insert_before_test() \tPASSED!\n");
    List_free(pList, freeItem);
    printf("\ttest list has been freed\n");
}

void list_remove_test() {
    int * pInt1 = malloc(sizeof(int));
    int * pInt2 = malloc(sizeof(int));
    *(int*)pInt1 = 11;
    *(int*)pInt2 = 22;
    assert(pInt1 != NULL);
    assert(pInt2 != NULL);
    List * pList = List_create();
    assert(pList != NULL);

    List_append(pList, pInt1);
    List_append(pList, pInt2);
    // CASE: OOB END
    assert(List_count(pList) == 2);
    List_next(pList);
    List_remove(pList); 
    assert(List_count(pList) == 2);

    // CASE: OOB START
    List_prev(pList);
    List_prev(pList);
    List_prev(pList);
    assert(List_count(pList) == 2);

    // CASE: general
    List_next(pList);
    void * pFirstItem = List_remove(pList);
    assert(*(int*)pFirstItem == *(int*)pInt1);
    assert(List_count(pList) == 1);
    free(pFirstItem);

    // CASE: 1 element
    void * pSecondItem = List_remove(pList);
    assert(*(int*)pSecondItem == *(int*)pInt2);
    assert(List_count(pList) == 0);
    assert(pList->currentPtrStatus == LIST_OOB_END);
    free(pSecondItem);
    
    printf("\tlist_remove_test() \tPASSED!\n");
    List_free(pList, freeItemVoid);
    printf("\ttest list has been freed\n");
}

// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void list_trim_test() {
    int * pIntArr = createSmallTestArr();
    List * pList = List_create();
    assert(pIntArr != NULL);
    assert(pList != NULL);
    
    for (unsigned int i = 0; i < SMALL_TEST_NUM; i++) {
        List_append(pList, (void*)&pIntArr[i]);
    }
    assert(List_count(pList) == SMALL_TEST_NUM);

    // CASE: Full list
    int lastItem = *(int*)List_trim(pList);
    assert( lastItem == pIntArr[SMALL_TEST_NUM - 1]);
    assert(List_count(pList) == SMALL_TEST_NUM - 1);
    
    // CASE: 1 item
    for (int i = List_count(pList); i > 1; i--) {
        List_trim(pList);
    }
    int firstItem = *(int*)List_trim(pList);
    assert( firstItem == pIntArr[0]);
    assert(List_count(pList) == 0);

    // CASE: empty list
    assert(List_trim(pList) == NULL);

    // clean up
    printf("\tlist_trim_test() \tPASSED!\n");
    List_free(pList, freeItemVoid);
    free(pIntArr);
    printf("\ttest list has been freed\n");
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void list_concat_test() {
    int * pIntArr1 = createSmallTestArr();
    int * pIntArr2 = createSmallTestArr();
    List * pList1 = List_create();
    List * pList2 = List_create();
    assert(pIntArr1 != NULL);
    assert(pIntArr2 != NULL);
    assert(pList1 != NULL);
    assert(pList2 != NULL);

    // CASE: plist 1 is empty and 2 has elements
    for (unsigned int i = 0; i < SMALL_TEST_NUM; i++) {
        List_append(pList2, (void*)&pIntArr1[i]);
    }
    assert(List_count(pList1) == 0 && List_count(pList2) == SMALL_TEST_NUM);
    List_concat(pList1, pList2);
    assert(pList2->pHead == NULL); // plist2 is gone
    assert(List_count(pList1) == SMALL_TEST_NUM);

    pList2 = List_create();
    for (unsigned int i = 0; i < SMALL_TEST_NUM; i++) {
        List_append(pList2, (void*)&pIntArr2[i]);
    }
    assert(List_count(pList1) == SMALL_TEST_NUM && List_count(pList2) == SMALL_TEST_NUM);
    List_concat(pList1, pList2);
    assert(pList2->pHead == NULL); // plist2 is gone
    assert(List_count(pList1) == 2 * SMALL_TEST_NUM);

    // clean up
    printf("\tlist_concat_test() \tPASSED!\n");
    List_free(pList1, freeItemVoid);
    free(pIntArr1);
    free(pIntArr2);
    printf("\ttest list has been freed\n");
}

void list_search_test() {
    int * pIntArr = createSmallTestArr();
    List * pList = List_create();
    assert(pIntArr != NULL);
    assert(pList != NULL);
    
    void * pTarget = (void*)&pIntArr[SMALL_TEST_NUM - 1];

    // CASE: empty list
    void * emptySearchResult = List_search(pList, isItemEqual, pTarget);
    assert(emptySearchResult == NULL);
    assert(pList->pCurrentItemNode == NULL);
    assert(pList->currentPtrStatus == LIST_OOB_END);

    // CASE: full list from start
    for (unsigned int i = 0; i < SMALL_TEST_NUM; i++) {
        List_prepend(pList, (void*)&pIntArr[i]);
    }
    void * generalSearchResult = List_search(pList, isItemEqual, pTarget);
    assert(*(int*)generalSearchResult == *(int*)pTarget);

    // clean up
    printf("\tlist_search_test() \tPASSED!\n");
    List_free(pList, freeItemVoid);
    free(pIntArr);
    printf("\ttest list has been freed\n");
}

int main (void) {
    list_create_test();
    list_count_test();
    list_first_test();
    list_last_test();
    list_next_prev_test();
    list_insert_after_test();
    list_insert_before_test();
    list_remove_test();
    list_trim_test();
    list_concat_test();
    list_search_test();

    return 0;
}