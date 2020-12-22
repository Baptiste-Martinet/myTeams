/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** bvector2
*/

#include "server.h"

void bvector_destroy(bvector_t *vector_node)
{
    if (!vector_node)
        return;
    switch (vector_node->type) {
    case CLIENT : destroy_client(vector_node->data);
        break;
    case TEAM: destroy_team(vector_node->data);
        break;
    case CHANNEL: destroy_channel(vector_node->data);
        break;
    case THREAD: destroy_thread(vector_node->data);
        break;
    case REPLY: destroy_reply(vector_node->data);
        break;
    case MESSAGE: destroy_message(vector_node->data);
    default:
        break;
    }
}

bool bvector_erase_at_uuid(bvector_t **vector, char uuid[UUID_LENGHT])
{
    bvector_t *tmp = *vector;
    bvector_t *to_be_free = NULL;

    if (!vector)
        return (false);
    if (strcmp(((bvector_base_t *)((*vector)->data))->uuid, uuid) == 0) {
        *vector = (*vector)->next;
        bvector_destroy(tmp);
        return (true);
    }
    for (; tmp->next; tmp = tmp->next) {
        if (strcmp(((bvector_base_t *)tmp->next->data)->uuid, uuid) == 0) {
            to_be_free = tmp->next;
            tmp->next = tmp->next->next;
            bvector_destroy(to_be_free);
            return (true);
        }
    }
    return (false);
}

void bvector_erase_at_name(bvector_t **vector, char name[MAX_NAME_LENGTH])
{
    bvector_t *tmp = *vector;
    bvector_t *to_be_free = NULL;

    if (!vector)
        return;
    if (strcmp(((bvector_base_t *)((*vector)->data))->name, name) == 0) {
        *vector = (*vector)->next;
        bvector_destroy(tmp);
        return;
    }
    for (; tmp->next; tmp = tmp->next) {
        if (strcmp(((bvector_base_t *)tmp->next->data)->name, name) == 0) {
            to_be_free = tmp->next;
            tmp->next = tmp->next->next;
            bvector_destroy(to_be_free);
            break;
        }
    }
}

bool bvector_erase_at_pointer(bvector_t **vector, void *mystruct)
{
    bvector_t *tmp = *vector;
    bvector_t *to_be_free = NULL;

    if (!vector)
        return (false);
    if ((*vector)->data == mystruct) {
        *vector = (*vector)->next;
        bvector_destroy(tmp);
        return (true);
    }
    for (; tmp->next; tmp = tmp->next) {
        if (tmp->next->data == mystruct) {
            to_be_free = tmp->next;
            tmp->next = tmp->next->next;
            bvector_destroy(to_be_free);
            return (true);
        }
    }
    return (false);
}

void *frm_uuid_not_same(bvector_t *vector, \
char uuid[UUID_LENGHT], void *my_struct)
{
    bvector_t *tmp = vector;

    if (!vector)
        return (NULL);
    for (; tmp; tmp = tmp->next) {
        if (strcmp(((bvector_base_t *)tmp->data)->uuid, uuid) == 0
            && tmp->data != my_struct)
            return (tmp->data);
    }
    return (NULL);
}