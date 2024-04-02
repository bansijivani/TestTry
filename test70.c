#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>

typedef enum {
    AST_EX_OFFSET,
    AST_EX_NUMBER,
    AST_EX_ID,
    AST_EX_PATH,
    AST_EX_STRING,
    AST_EX_ADDRESS,
    AST_EX_SUBSCRIPT,
    AST_EX_BLOCKSPEC,
    AST_EX_STRUCTSPEC,
    AST_EX_FIELDSPEC,
    AST_EX_TYPESPEC,
    AST_KW_STATE
} ast_node_t;

struct ast_node {
    ast_node_t type;
    int64_t ast_num;
    char* ast_str;
};

int ast_expr_init(struct ast_node* expr, ast_node_t type, const char* str) {
    int ret = 0;
    switch (type) {
        case AST_EX_OFFSET:
            str++; // Cut off the +
        case AST_EX_NUMBER:
            ret = sscanf(str, "%" SCNi64, &expr->ast_num);
            if (ret != 1) {
                return 1;
            }
            break;
        case AST_EX_ID:
        case AST_EX_PATH:
        case AST_EX_STRING:
            expr->ast_str = strdup(str);
            if (expr->ast_str == NULL) {
                return 1;
            }
            break;
        case AST_EX_ADDRESS:
        case AST_EX_SUBSCRIPT:
        case AST_EX_BLOCKSPEC:
        case AST_EX_STRUCTSPEC:
        case AST_EX_FIELDSPEC:
        case AST_EX_TYPESPEC:
        case AST_KW_STATE:
            break;
        default:
            errno = EINVAL;
            return 1;
    }
    return 0;
}

int main() {
    struct ast_node expr;
    ast_expr_init(&expr, AST_EX_NUMBER, "42");
    printf("ast_num: %" PRId64 "\n", expr.ast_num);
    return 0;
}
