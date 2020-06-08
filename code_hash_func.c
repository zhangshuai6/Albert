
/* 字符串 hash 函数 */
#define  MULT  31
#define  HASH_NUM  520520

unsigned int StrHash(char *str)
{
    unsigned int hashVal = 0;

    for (; *str != '\0'; str++) {
        hashVal = hashVal * MULT + *str;
    }

    return hashVal % HASH_NUM;
}