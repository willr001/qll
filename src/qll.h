#ifndef _QLL_H
#define _QLL_H

#include <stdlib.h>

/***********************************************************************************************//**
 * \brief Will return the final element in a linked lint if exists, else NULL
 *
 * \param qll_rval will be set to the return value
 * \param qll_head is the pointer to the starting element of a linked list to traverse
 * \param qll_next is the name of the member of that points to the next element
 *
 * \return Pointer to the final element in linked list, or none if list is empty or doesn't exist.
 **************************************************************************************************/
#define QLL_GET_TAIL(qll_rval,qll_head, qll_next) \
({  if (qll_head) { \
        (qll_rval) = (qll_head); \
        while ((qll_rval)->qll_next) { \
            (qll_rval) = (qll_rval)->qll_next; \
        } \
    } else { \
        (qll_rval) = NULL; \
    } \
    (qll_rval); \
})

/***********************************************************************************************//**
 * \brief Will return the element in a linked lint if exists, else NULL
 *
 * \param qll_rval will be set to qll_find if it is in list, else NULL
 * \param qll_find is the element to search for
 * \param qll_head is the pointer to the starting element of a linked list to traverse
 * \param qll_next is the name of the member of that points to the next element
 *
 * \return Pointer to the found element in linked list, or \c NULL
 **************************************************************************************************/
#define QLL_FIND(qll_rval,qll_find,qll_head,qll_next) \
({  if (qll_find) {   \
        (qll_rval) = (qll_head); \
        while ((qll_rval) && (qll_rval) != (qll_find)) { \
            (qll_rval) = (qll_rval)->qll_next; \
        } \
    } else { \
        (qll_rval) = NULL; \
    } \
    (qll_rval); \
})

/***********************************************************************************************//**
 * \brief Will add \p qll_add to the beginning of the list contained in pointer \p qll_head.
 *
 * \param qll_add will be added to the list.
 * \param qll_head is the pointer to the starting element of a linked list to traverse
 * \param qll_next is the name of the member of that points to the next element
 **************************************************************************************************/
#define QLL_ADD(qll_add, qll_head, qll_next) \
({  if ((qll_head) && (qll_add)) { \
        (qll_add)->qll_next = (qll_head); \
        (qll_head) = (qll_add); \
    } \
})

#define QLL_NEXT(qll_this,qll_next) ((qll_this)->qll_next)

#define QLL_PREV(qll_rval,qll_find,qll_head,qll_next) \
({  if ((qll_find) != (qll_head)) { \
        (qll_rval) = (qll_head); \
        while (qll_rval && (qll_rval)->qll_next != (qll_find)) { \
            (qll_rval) = (qll_rval)->qll_next; \
        } \
    } else { \
        (qll_rval) = NULL; \
    } \
    (qll_rval); \
})

/// \test \p qll_remove is NULL
/// \test \p qll_head is NULL
/// \test \p qll_remove is \p qll_head
/// \test \p qll_remove is in \p qll_head
/// \test \p qll_remove is not in \p qll_head
#define QLL_REMOVE(qll_temp, qll_remove, qll_head, qll_next) \
({  if (qll_remove) { \
        if ((qll_head) == (qll_remove)) { \
            (qll_head) = (qll_remove)->qll_next; \
            (qll_remove)->qll_next = NULL; \
        } else if (qll_head) { \
            QLL_PREV((qll_temp),(qll_remove),(qll_head),qll_next); \
            if (qll_temp) { \
                (qll_temp)->qll_next = (qll_remove)->qll_next; \
                (qll_remove)->qll_next = NULL; \
            } \
        } \
    } \
})

#endif // _QLL_H

