#ifndef DSL_PARSER_H
#define DSL_PARSER_H

/*
    English DSL -> AST Parser
    Header-only version

    Usage:
        #define DSL_IMPLEMENTATION
        #include "dsl_parser.h"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

    /* =========================
       AST Types
       ========================= */

    typedef enum {
        AST_ENTITY,
        AST_PROPERTY,
        AST_EVENT,
        AST_ACTION
    } ASTNodeType;

    typedef struct ASTNode {
        ASTNodeType type;
        struct ASTNode* next;
    } ASTNode;

    /* =========================
       Entity
       ========================= */

    typedef struct {
        ASTNode base;
        char name[32];
        ASTNode* properties;
    } ASTEntity;

    /* =========================
       Property
       ========================= */

    typedef struct {
        ASTNode base;
        char name[32];
        int value;
    } ASTProperty;

    /* =========================
       Event
       ========================= */

    typedef struct {
        ASTNode base;
        char subject[32];
        char verb[32];
        char object[32];
        ASTNode* actions;
    } ASTEvent;

    /* =========================
       Action
       ========================= */

    typedef struct {
        ASTNode base;
        char target[32];
        char property[32];
        char op[4];
        int value;
    } ASTAction;

    /* =========================
       AST Container
       ========================= */

    typedef struct {
        ASTNode* head;
        ASTNode* tail;
    } AST;

    /* =========================
       Public API
       ========================= */

    void dsl_parse_file(const char* filename, AST* ast);
    void dsl_ast_free(AST* ast);

    /* =========================
       Debug Helpers
       ========================= */

    void dsl_ast_dump(AST* ast);

#ifdef DSL_IMPLEMENTATION

    /* ============================================================
       Internal Helpers
       ============================================================ */

    static int dsl_count_indent(const char* line) {
        int c = 0;
        while (*line == ' ') {
            ++c;
            ++line;
        }
        return c;
    }

    static int dsl_split(char* line, char* tokens[], int max) {
        int n = 0;
        char* tok = strtok(line, " \t\r\n");
        while (tok && n < max) {
            tokens[n++] = tok;
            tok = strtok(NULL, " \t\r\n");
        }
        return n;
    }

    static void ast_add(AST* ast, ASTNode* node) {
        node->next = NULL;
        if (!ast->head) {
            ast->head = ast->tail = node;
        }
        else {
            ast->tail->next = node;
            ast->tail = node;
        }
    }

    /* ============================================================
       Node Creation
       ============================================================ */

    static ASTEntity* ast_entity_new(const char* name) {
        ASTEntity* e = (ASTEntity*)calloc(1, sizeof(ASTEntity));
        e->base.type = AST_ENTITY;
        strncpy(e->name, name, sizeof(e->name) - 1);
        return e;
    }

    static ASTProperty* ast_property_new(const char* name, int value) {
        ASTProperty* p = (ASTProperty*)calloc(1, sizeof(ASTProperty));
        p->base.type = AST_PROPERTY;
        strncpy(p->name, name, sizeof(p->name) - 1);
        p->value = value;
        return p;
    }

    static ASTEvent* ast_event_new(const char* sub, const char* verb, const char* obj) {
        ASTEvent* e = (ASTEvent*)calloc(1, sizeof(ASTEvent));
        e->base.type = AST_EVENT;
        strncpy(e->subject, sub, sizeof(e->subject) - 1);
        strncpy(e->verb, verb, sizeof(e->verb) - 1);
        strncpy(e->object, obj, sizeof(e->object) - 1);
        return e;
    }

    static ASTAction* ast_action_new(
        const char* target,
        const char* prop,
        const char* op,
        int value
    ) {
        ASTAction* a = (ASTAction*)calloc(1, sizeof(ASTAction));
        a->base.type = AST_ACTION;
        strncpy(a->target, target, sizeof(a->target) - 1);
        strncpy(a->property, prop, sizeof(a->property) - 1);
        strncpy(a->op, op, sizeof(a->op) - 1);
        a->value = value;
        return a;
    }

    /* ============================================================
       Parser
       ============================================================ */

    void dsl_parse_file(const char* filename, AST* ast) {
        memset(ast, 0, sizeof(AST));

        FILE* f = fopen(filename, "r");
        if (!f) return;

        char line[256];

        ASTEntity* current_entity = NULL;
        ASTEvent* current_event = NULL;

        while (fgets(line, sizeof(line), f)) {
            int indent = dsl_count_indent(line);
            char* content = line + indent;

            if (*content == '\n' || *content == '\0')
                continue;

            char buf[256];
            strncpy(buf, content, sizeof(buf) - 1);
            buf[sizeof(buf) - 1] = 0;

            char* tokens[8];
            int n = dsl_split(buf, tokens, 8);
            if (n == 0) continue;

            /* entity Player */
            if (strcmp(tokens[0], "entity") == 0 && n >= 2) {
                current_entity = ast_entity_new(tokens[1]);
                ast_add(ast, (ASTNode*)current_entity);
                current_event = NULL;
            }

            /* has health 100 */
            else if (strcmp(tokens[0], "has") == 0 && current_entity && n >= 3) {
                ASTProperty* p = ast_property_new(tokens[1], atoi(tokens[2]));
                p->base.next = current_entity->properties;
                current_entity->properties = (ASTNode*)p;
            }

            /* when Player collides Enemy */
            else if (strcmp(tokens[0], "when") == 0 && n >= 4) {
                current_event = ast_event_new(tokens[1], tokens[2], tokens[3]);
                ast_add(ast, (ASTNode*)current_event);
                current_entity = NULL;
            }

            /* Enemy health -= 10 */
            else if (current_event && n == 4) {
                ASTAction* a = ast_action_new(
                    tokens[0],
                    tokens[1],
                    tokens[2],
                    atoi(tokens[3])
                );
                a->base.next = current_event->actions;
                current_event->actions = (ASTNode*)a;
            }
        }

        fclose(f);
    }

    /* ============================================================
       AST Free
       ============================================================ */

    void dsl_ast_free(AST* ast) {
        ASTNode* n = ast->head;
        while (n) {
            ASTNode* next = n->next;

            if (n->type == AST_ENTITY) {
                ASTEntity* e = (ASTEntity*)n;
                ASTNode* p = e->properties;
                while (p) {
                    ASTNode* pn = p->next;
                    free(p);
                    p = pn;
                }
            }
            else if (n->type == AST_EVENT) {
                ASTEvent* ev = (ASTEvent*)n;
                ASTNode* a = ev->actions;
                while (a) {
                    ASTNode* an = a->next;
                    free(a);
                    a = an;
                }
            }

            free(n);
            n = next;
        }
        ast->head = ast->tail = NULL;
    }

    /* ============================================================
       Debug Dump
       ============================================================ */

    void dsl_ast_dump(AST* ast) {
        for (ASTNode* n = ast->head; n; n = n->next) {
            if (n->type == AST_ENTITY) {
                ASTEntity* e = (ASTEntity*)n;
                printf("Entity %s\n", e->name);
                for (ASTNode* p = e->properties; p; p = p->next) {
                    ASTProperty* pr = (ASTProperty*)p;
                    printf("  has %s %d\n", pr->name, pr->value);
                }
            }
            else if (n->type == AST_EVENT) {
                ASTEvent* ev = (ASTEvent*)n;
                printf("When %s %s %s\n", ev->subject, ev->verb, ev->object);
                for (ASTNode* a = ev->actions; a; a = a->next) {
                    ASTAction* ac = (ASTAction*)a;
                    printf("  %s %s %s %d\n",
                        ac->target, ac->property, ac->op, ac->value);
                }
            }
        }
    }

#endif /* DSL_IMPLEMENTATION */

#ifdef __cplusplus
}
#endif

#endif /* DSL_PARSER_H */