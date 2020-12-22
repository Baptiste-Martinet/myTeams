/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** bvector
*/

#pragma once
#include "common.h"

//Implementation vaseuse des vecteurs C++

typedef enum BVEC_TYPES_S {
    CLIENT,
    TEAM,
    CHANNEL,
    THREAD,
    REPLY,
    MESSAGE
} BVEC_TYPES;

typedef struct bvector_s {
    BVEC_TYPES type;
    void *data;
    struct bvector_s *next;
} bvector_t;

typedef struct bvector_base_s {
    char name[MAX_NAME_LENGTH];
    char uuid[UUID_LENGHT];
} bvector_base_t;

bvector_t * bvector_create(void *data, BVEC_TYPES type);
bool bvector_push_back(bvector_t * vector, void *data, BVEC_TYPES type);
void *frm_uuid(bvector_t *vector, char uuid[UUID_LENGHT]);
void *frm_name(bvector_t *vector, char name[MAX_NAME_LENGTH]);
void bvector_destroy(bvector_t *vector_node);
bool bvector_erase_at_uuid(bvector_t **vector, char uuid[UUID_LENGHT]);
void bvector_erase_at_name(bvector_t **vector, char name[MAX_NAME_LENGTH]);
bool bvector_erase_at_pointer(bvector_t **vector, void *mystruct);
void bvector_display(bvector_t *vector);
void *frm_uuid_not_same(bvector_t *vector, char uuid[UUID_LENGHT],
    void *my_struct);