#include <stdlib.h>
#include <stdio.h>
#include "deck.h"

int compare_cards(const card_t *a, const card_t *b) {
    static const char *values[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    int value_a, value_b;

    for (value_a = 0; value_a < 13 && values[value_a] != a->value; ++value_a);
    for (value_b = 0; value_b < 13 && values[value_b] != b->value; ++value_b);

    if (value_a == value_b) {
        return a->kind - b->kind;
    } else {
        return value_a - value_b;
    }
}

void sort_deck(deck_node_t **deck) {
    deck_node_t *current = *deck;
    deck_node_t *next;
    deck_node_t *sorted = NULL;
    deck_node_t *temp;

    while (current != NULL) {
        next = current->next;
        if (sorted == NULL || compare_cards(current->card, sorted->card) < 0) {
            current->next = sorted;
            if (sorted != NULL) {
                sorted->prev = current;
            }
            sorted = current;
        } else {
            temp = sorted;
            while (temp->next != NULL && compare_cards(current->card, temp->next->card) > 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            if (temp->next != NULL) {
                temp->next->prev = current;
            }
            temp->next = current;
            current->prev = temp;
        }
        current = next;
    }

    *deck = sorted;
}
