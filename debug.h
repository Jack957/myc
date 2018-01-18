/*
#ifdef _DEBUG
#define DEBUG_PRINT(....)    fprintf (stderr, __VA_ARGS__)
#else
#define DEBUG_PRINT(...)    // Don't do anything in release builds 
#endif
*/
#ifdef _DEBUG
#define DEBUG_PRINT(x)    printf x
#else
#define DEBUG_PRINT(x)
#endif /* DEBUG */

/*
#ifdef _DEBUG
#define DEBUG(format, args...) printf("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
#define DEBUG(args...)
#endif
*/