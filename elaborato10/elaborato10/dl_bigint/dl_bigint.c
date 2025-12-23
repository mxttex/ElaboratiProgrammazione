#include"selector.h"
#include <stdlib.h>
#include "dl_bigint.h"
#ifdef DL_BIGINT
#define C2N(c) ((c)-'0')

static bigint* bigint_alloc(digit x) {
	bigint* tmp = (bigint*)malloc(sizeof(bigint));

	if (tmp != NULL) {
		tmp->x = x;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	return tmp;
}

static int bigint_delete(bigint* N) {
	if (N == NULL) {
		return 1;
	}
	else {
		if (N->next != NULL)
			N->next->prev = N->prev;
		if (N->prev != NULL)
			N->prev->next = N->next;
		free(N);
		return 0;
	}
}

static int head_insert(bigint** N, digit x) {
	if (N == NULL) {
		return 1;
	}
	else if (*N == NULL) {
		return (*N = bigint_alloc(x)) == NULL;
	}
	else {
		bigint* tmp = bigint_alloc(x);

		if (tmp != NULL) {
			tmp->next = *N;
			(*N)->prev = tmp;
			*N = tmp;
		}
		return tmp == NULL;
	}
}

static int head_delete(bigint** N) {
	if (N == NULL || *N == NULL) {
		return 1;
	}
	else {
		bigint* tmp = *N;

		*N = (*N)->next;
		return bigint_delete(tmp);
	}
}

static void remove_leading_zeros(bigint** N) {
	if (N != NULL) {
		while (*N != NULL && (*N)->x == 0 && (*N)->next != NULL)
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

static void print(bigint* N) {
	if (N == NULL) {
		printf("NaN");
	}
	else {
		while (N != NULL) {
			printf("%d", N->x);
			N = N->next;
		}
	}
}




static void sprint(char* s, bigint* N) {
	if (N == NULL) {
		sprintf(s, "NaN");
	}
	else {
		int cont = 0;
		while (N != NULL) {
			sprintf(s + cont, "%d", N->x);
			if (N->x < 0) cont++;
			N = N->next;
			cont++;
		}
		sprintf(s + cont, "%c", '\0');
	}
}

static void bigint_free_all(bigint* head) {
	bigint* temp_node;
	while (head != NULL) {
		temp_node = head;
		head = head->next;
		free(temp_node);
	}
}

static bigint* bigint_deep_copy(bigint* source) {
	bigint* copy_head = NULL;
	bigint* copy_current;
	bigint* source_current;
	bigint* new_node;

	if (source == NULL) return NULL;

	copy_head = bigint_alloc(source->x);
	copy_current = copy_head;
	source_current = source->next;

	while (source_current != NULL) {
		new_node = bigint_alloc(source_current->x);
		copy_current->next = new_node;
		new_node->prev = copy_current;
		copy_current = new_node;
		source_current = source_current->next;
	}
	return copy_head;
}

static bigint* bigint_sum_magnitude(bigint* operand1, bigint* operand2) {
	bigint* result_head = NULL;
	bigint* cursor1 = operand1;
	bigint* cursor2 = operand2;
	int carry = 0;
	int current_sum = 0;
	int digit1, digit2;

	while (cursor1 != NULL && cursor1->next != NULL) cursor1 = cursor1->next;
	while (cursor2 != NULL && cursor2->next != NULL) cursor2 = cursor2->next;

	while (cursor1 != NULL || cursor2 != NULL || carry != 0) {
		digit1 = (cursor1 != NULL) ? ((cursor1->x < 0) ? -cursor1->x : cursor1->x) : 0;
		digit2 = (cursor2 != NULL) ? ((cursor2->x < 0) ? -cursor2->x : cursor2->x) : 0;

		current_sum = digit1 + digit2 + carry;
		carry = current_sum / 10;
		head_insert(&result_head, current_sum % 10);

		if (cursor1 != NULL) cursor1 = cursor1->prev;
		if (cursor2 != NULL) cursor2 = cursor2->prev;
	}

	if (result_head == NULL) head_insert(&result_head, 0);

	return result_head;
}

static void bigint_append_zeros(bigint* number, int zero_count) {
	bigint* tail;
	bigint* zero_node;
	int i;

	if (number == NULL) return;

	tail = number;
	while (tail->next != NULL) tail = tail->next;

	if (tail == number && tail->x == 0) return;

	for (i = 0; i < zero_count; i++) {
		zero_node = bigint_alloc(0);
		tail->next = zero_node;
		zero_node->prev = tail;
		tail = zero_node;
	}
}

bigint* mul(bigint* N1, bigint* N2) {
	bigint* total_product;
	bigint* multiplicand_abs;
	bigint* multiplier_cursor;
	bigint* partial_product;
	bigint* temp_sum;
	int sign1, sign2, result_sign;
	int decimal_position = 0;
	int current_digit;
	int i;

	if (N1 == NULL || N2 == NULL) return NULL;

	if (N1->x == 0 || N2->x == 0) {
		return bigint_alloc(0);
	}

	result_sign = (N1->x * N2->x) > 0 ? 1 : -1;

	total_product = bigint_alloc(0);

	multiplicand_abs = bigint_deep_copy(N1);
	if (multiplicand_abs->x < 0) multiplicand_abs->x = -multiplicand_abs->x;

	multiplier_cursor = N2;
	while (multiplier_cursor->next != NULL) multiplier_cursor = multiplier_cursor->next;

	while (multiplier_cursor != NULL) {
		current_digit = (multiplier_cursor->x < 0) ? -multiplier_cursor->x : multiplier_cursor->x;

		if (current_digit > 0) {
			partial_product = bigint_alloc(0);

			for (i = 0; i < current_digit; i++) {
				temp_sum = bigint_sum_magnitude(partial_product, multiplicand_abs);
				bigint_free_all(partial_product);
				partial_product = temp_sum;
			}

			bigint_append_zeros(partial_product, decimal_position);

			temp_sum = bigint_sum_magnitude(total_product, partial_product);
			bigint_free_all(total_product);
			bigint_free_all(partial_product);
			total_product = temp_sum;
		}

		decimal_position++;
		multiplier_cursor = multiplier_cursor->prev;
	}

	bigint_free_all(multiplicand_abs);
	remove_leading_zeros(&total_product);

	if (result_sign == -1 && total_product != NULL) {
		total_product->x = -total_product->x;
	}

	return total_product;
}


#endif