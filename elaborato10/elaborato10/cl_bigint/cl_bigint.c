#include "selector.h"
#ifdef CL_BIGINT
#include <stdlib.h>
#include "cl_bigint.h"


#define C2N(c) ((c)-'0')

static bigint* bigint_alloc(digit x) {
    bigint* tmp = (bigint*)malloc(sizeof(bigint));

    if (tmp != NULL) {
        tmp->x = x;
        tmp->next = tmp;
        tmp->prev = tmp;
    }
    return tmp;
}

static int bigint_delete(bigint* N) {
    if (N == NULL) {
        return 1;
    }
    else {
        bigint* prv = N->prev, * nxt = N->next;
        nxt->prev = prv;
        prv->next = nxt;
        free(N);
        return 0;
    }
}

static int bigint_insert(bigint* N, digit x) {
    if (N == NULL) {
        return 1;
    }
    else {
        bigint* tmp = bigint_alloc(x), * nxt = N->next, * prv = N;
        if (tmp != NULL) {
            tmp->prev = prv;
            tmp->next = nxt;
            prv->next = tmp;
            nxt->prev = tmp;
        }
        return tmp == NULL;
    }
}

static int head_insert(bigint** N, digit x) {
    if (N == NULL)
        return 1;
    else if (*N == NULL)
        return (*N = bigint_alloc(x)) == NULL;
    else if (bigint_insert((*N)->prev, x) == 1)
        return 1;
    else
        return (*N = (*N)->prev) == NULL;
}

static int head_delete(bigint** N) {
    if (N == NULL || *N == NULL) {
        return 1;
    }
    else if (*N == (*N)->next) {
        free(*N);
        *N = NULL;
        return 0;
    }
    else {
        *N = (*N)->next;
        return bigint_delete((*N)->prev);
    }
}

static void remove_leading_zeros(bigint** N) {
    if (N != NULL && *N != NULL) {
        while ((*N)->x == 0 && *N != (*N)->next)
            head_delete(N);
    }
}


static int well_formed_str(char* s) {
    if (s == NULL || *s == '\0') {
        return 0;
    }
    else {
        if (*s == '-') s++;
        if (*s == '\0')
            return 0;
        while (*s != '\0') {
            if (!isdigit(*s))
                return 0;
            s++;
        }
        return 1;
    }
}

static bigint* str2bigint_rec(char* s) {
    bigint* N = NULL;

    if (*s != '\0') {
        N = str2bigint_rec(s + 1);
        head_insert(&N, C2N(*s));
    }
    return N;
}

static bigint* str2bigint(char* s) {
    bigint* N = NULL;

    if (well_formed_str(s)) {
        int sgn = 1;

        if (s[0] == '-') {
            sgn = -1;
            s++;
        }
        N = str2bigint_rec(s);
        remove_leading_zeros(&N);
        if (N != NULL && sgn == -1)
            N->x = -N->x;
    }

    return N;
}


static void free_bigint(bigint* N) {
    while (N != NULL) {
        head_delete(&N);
    }
}



static bigint* sum_abs(bigint* N1, bigint* N2) {
    bigint* res = NULL;
    bigint* p1, * p2;
    int carry = 0;
    int done1, done2;
    int v1, v2, sum;

    if (N1 == NULL && N2 == NULL) return NULL;

    p1 = (N1 != NULL) ? N1->prev : NULL;
    p2 = (N2 != NULL) ? N2->prev : NULL;
    done1 = (N1 == NULL);
    done2 = (N2 == NULL);

    while (!done1 || !done2 || carry) {
        v1 = 0;
        v2 = 0;

        if (!done1) {
            v1 = (p1 == N1) ? abs(p1->x) : p1->x;
            if (p1 == N1) done1 = 1;
            else p1 = p1->prev;
        }

        if (!done2) {
            v2 = (p2 == N2) ? abs(p2->x) : p2->x;
            if (p2 == N2) done2 = 1;
            else p2 = p2->prev;
        }

        sum = v1 + v2 + carry;
        head_insert(&res, sum % 10);
        carry = sum / 10;
    }

    if (res == NULL) return str2bigint("0");
    return res;
}


bigint* mul(bigint* N1, bigint* N2) {
    bigint* total, * p2, * partial, * p1, * new_total;
    int sign, shift, done2, digit2, k;
    int carry, done1, digit1, val;

    if (N1 == NULL || N2 == NULL) return NULL;

    if ((N1->x == 0 && N1->next == N1) || (N2->x == 0 && N2->next == N2))
        return str2bigint("0");

    sign = (N1->x * N2->x) > 0 ? 1 : -1;

    total = str2bigint("0");
    p2 = N2->prev;
    shift = 0;
    done2 = 0;

    while (!done2) {
        digit2 = (p2 == N2) ? abs(p2->x) : p2->x;

        if (digit2 != 0) {
            partial = NULL;
            p1 = N1->prev;
            carry = 0;
            done1 = 0;

            while (!done1 || carry) {
                digit1 = 0;
                if (!done1) {
                    digit1 = (p1 == N1) ? abs(p1->x) : p1->x;
                    if (p1 == N1) done1 = 1;
                    else p1 = p1->prev;
                }

                val = (digit1 * digit2) + carry;
                head_insert(&partial, val % 10);
                carry = val / 10;
            }

            for (k = 0; k < shift; k++) {
                if (partial == NULL) head_insert(&partial, 0);
                else bigint_insert(partial->prev, 0);
            }

            new_total = sum_abs(total, partial);

            free_bigint(total);
            free_bigint(partial);

            total = new_total;
        }

        if (p2 == N2) done2 = 1;
        else {
            p2 = p2->prev;
            shift++;
        }
    }

    remove_leading_zeros(&total);

    if (total != NULL) {
        if (sign == -1 && total->x != 0)
            total->x = -abs(total->x);
        else
            total->x = abs(total->x);
    }

    return total;
}
#endif
