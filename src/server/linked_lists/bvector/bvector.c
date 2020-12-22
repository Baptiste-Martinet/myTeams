/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** bvector
*/

#include "server.h"

bvector_t * bvector_create(void *data, BVEC_TYPES type)
{
    bvector_t * vector = malloc(sizeof(bvector_t));

    if (!vector || !data)
        return (NULL);
    vector->type = type;
    vector->data = data;
    vector->next = NULL;
    return (vector);
}

bool bvector_push_back(bvector_t * vector, void *data, BVEC_TYPES type)
{
    bvector_t * temp = vector;
    bvector_t *new_node = bvector_create(data, type);

    if (!vector || !data || !new_node)
        return (false);
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;
    return (true);
}

void *frm_uuid(bvector_t *vector, char uuid[UUID_LENGHT])
{
    bvector_t *tmp = vector;

    if (!vector)
        return (NULL);
    for (; tmp; tmp = tmp->next) {
        if (strcmp(((bvector_base_t *)tmp->data)->uuid, uuid) == 0)
            return (tmp->data);
    }
    return (NULL);
}

void *frm_name(bvector_t *vector, char name[MAX_NAME_LENGTH])
{
    bvector_t *tmp = vector;

    if (!vector)
        return (NULL);
    for (; tmp; tmp = tmp->next) {
        if (strcmp(((bvector_base_t *)tmp->data)->name, name) == 0)
            return (tmp->data);
    }
    return (NULL);
}

void bvector_display(bvector_t *vector)
{
    bvector_t *tmp = vector;

    printf("<Server>: Displaying vector:\n [");
    for (; tmp; tmp = tmp->next) {
        switch (tmp->type) {
        case CLIENT: client_display(tmp->data);
            break;
        default: printf("{name: %s uuid: %s}, ", \
((bvector_base_t *)tmp->data)->name, ((bvector_base_t *)tmp->data)->uuid);
            break;
        }
    }
    printf("]\n");
}