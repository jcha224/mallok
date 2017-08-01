// John Chang
// test program for mallok.c

#include "mallok.h"

/**
 * Tests a pool of 1000 bytes:
 * returns the number of blocks size 10.
 */
int test1000() {
    create_pool(1000);
    int count = 0;
    while(my_malloc(10)) {
        count++;
    }
    free_pool();
    return count;
}

/**
 * Helper fuction for free test.
 */
void testFreeHelp() {
    void *test1 = my_malloc(200);
    void *test2 = my_malloc(200);
    void *test3 = my_malloc(200);
    void *test4 = my_malloc(200);
    void *test5 = my_malloc(200);
    
    
    my_free(test1);
    my_free(test2);
    my_free(test3);
    my_free(test4);
    my_free(test5);
}
 

/**
 * Tests a pool of 1000 bytes:
 * 5 blocks of 200, free all 5 blocks, 
 * repeat several times.
 */
 void testFree() {
    create_pool(1000);
    testFreeHelp();
    testFreeHelp();
    testFreeHelp();
    free_pool();
    
 }
 
/**
 * Test pool of 100 bytes:
 * 5 blocks of 200, free middle block,
 * request block of 210 (fail), 
 * request block of 150(succeed),
 * request block of 60 (fail)
 * request block of 50 (succeed).
 */
 void testFreeMiddle() {
    create_pool(1000);
    void *test = NULL;
    void *test1 = my_malloc(200);
    void *test2 = my_malloc(200);
    void *test3 = my_malloc(200);
    void *test4 = my_malloc(200);
    void *test5 = my_malloc(200);
    
    my_free(test3);
    test3 = my_malloc(210);
       
    test3 = my_malloc(150);
    test = my_malloc(60);
    test = my_malloc(50);
    
    
    free_pool();
 }
 
 /**
  * Test pool of 1000 bytes:
  * request 5 blocks of 200,
  * first block with 'A',
  * second block with 'B', etc.
  */
void testLetters() {
    create_pool(1000);
    
    char *test1 = my_malloc(200);
    char *test2 = my_malloc(200);
    char *test3 = my_malloc(200);
    char *test4 = my_malloc(200);
    char *test5 = my_malloc(200);
    
    *test1 = 'A';
    *test2 = 'B';
    *test3 = 'C';
    *test4 = 'D';
    *test5 = 'E';
    
    printf("%s", test1);
    printf("%s", test2);
    printf("%s", test3);
    printf("%s", test4);
    printf("%s\n", test5);
    
    free_pool();
    
}
 
 /**
  * Helper function for testReturn.
  */
void *return1000() {
    return my_malloc(100);
}

 /**
  * Helper function for testReturn.
  */
void *return250() {
    void *test = my_malloc(250);
    return test;
}

 /**
  * Helper function for testReturn.
  */
void *return100() {
    return my_malloc(100);
    
}

/**
 * Test pool of 1000:
 * request and return block of 1000,
 * request and return 4 blocks of 250,
 * request and return 10 blocks of 100.
 */
 void testReturn() {
    create_pool(1000);
    return1000();
    free_pool();
    
    create_pool(1000);
    void* test1 = return250();
    void* test2 = return250();
    void* test3 = return250();
    void* test4 = return250();
    free_pool();
    
    create_pool(1000);
    void* test1a = return100();
    void* test2a = return100();
    void* test3a = return100();
    void* test4a = return100();
    void* test5a = return100();
    void* test6a = return100();
    void* test7a = return100();
    void* test8a = return100();
    void* test9a = return100();
    void* test10a = return100();
    free_pool();
    
 }
 
// main function  runs tests
int main() {
    int count1000 = 0;
    count1000 = test1000();
    printf("%d\n", count1000);
    testFree();
    testFreeMiddle();
    testLetters();
    testReturn();
    
    return 0;
}
    