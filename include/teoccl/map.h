/*
 * The MIT License
 *
 * Copyright 2016-2018 Kirill Scherba <kirill@scherba.ru>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 * \file   map.h
 * \brief  Map module
 * \author Kirill Scherba <kirill@scherba.ru>
 *
 * Created on June 6, 2016, 12:26 PM
 */

#ifndef MAP_H
#define MAP_H

#include <string.h>
#include <stdint.h>

#include "teoccl/queue.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HASH_TABLE_SIZE 127
#define HASH_TABLE_INITVAL 77557755

typedef struct teoMap {

    size_t length;
    teoQueue **q;
    int auto_resize_f;
    uint32_t collisions;
    size_t hash_map_size;

} teoMap;

typedef struct teoMapElementData {

    uint32_t hash;
    size_t key_length;
    size_t data_length;
    uint8_t data[]; // Key + Data

} teoMapElementData;

typedef struct teoMapIterator {

    uint32_t idx;
    teoMap *map;
    teoQueueIterator it;
    teoMapElementData *tmv;

} teoMapIterator;


/**
 * @brief
 *
 * @param map
 * @param data_length
 *
 * @return
 */
uint8_t *teoMapGetFirst(teoMap *map, size_t *data_length);

/**
 * Get number of elements in TR-UPD map
 *
 * @param map Pointer to teoMapData
 * @return Number of elements in TR-UPD map
 */
size_t teoMapSize(teoMap *map);


/**
 * @brief
 *
 * @param size
 * @param auto_resize_f
 *
 * @return
 */
teoMap *teoMapNew(size_t size, int auto_resize_f);

/**
 * @brief
 *
 * @param map
 */
void teoMapDestroy(teoMap *map);


/**
 * @brief
 *
 * @param map
 */
void teoMapClear(teoMap *map);


/**
 * @brief
 *
 * @param map
 * @param key
 * @param key_length
 * @param data
 * @param data_length
 *
 * @return
 */
uint8_t *teoMapAdd(teoMap *map, const uint8_t *key, size_t key_length, const uint8_t *data,
  size_t data_length);


/**
 * Add (or update) key data to the map when key is cstring
 *
 * @param map Pointer to teoMapData
 * @param key Pointer to key cstring
 * @param data Pointer to data
 * @param data_length Data length
 * @return Data of added key or (void*)-1 at error
 */
static
inline uint8_t *teoMapAddStr(teoMap *map, const char *key, const uint8_t *data,
        size_t data_length) {
    return teoMapAdd(map, (const uint8_t*)key, strlen(key) + 1, data, data_length);
}

uint8_t *teoMapGet(teoMap *map, const uint8_t *key, size_t key_length,
  size_t *data_length);

/**
 * Get key data from hash table when key is cstring
 *
 * @param map Pointer to teoMapData
 * @param key Pointer to key cstring
 * @param data_length [out] Pointer to data length
 *
 * @return Data of selected key (may be NULL) or (void*)-1 if not found
 */
static
inline uint8_t *teoMapGetStr(teoMap *map, const char *key, size_t *data_length) {
    return teoMapGet(map, (const uint8_t*)key, strlen(key) + 1, data_length);
}

int teoMapDelete(teoMap *map, const uint8_t *key, size_t key_length);

/**
 * Delete keys element from map when key is cstring
 *
 * @param map Pointer to teoMapData
 * @param key Pointer to key cstring
 * @return Zero at success, or errors: -1 - keys element not found
 */
static
inline int teoMapDeleteStr(teoMap *map, const char *key) {
    return teoMapDelete(map, (const uint8_t*)key, strlen(key) + 1);
}

teoMapIterator *teoMapIteratorNew(teoMap *map);
void teoMapIteratorReset(teoMapIterator *map_it, teoMap *map);
teoMapIterator *teoMapIteratorReverseNew(teoMap *map);
void teoMapIteratorReverseReset(teoMapIterator *map_it, teoMap *map);
int teoMapIteratorFree(teoMapIterator *map_it);
teoMapElementData *teoMapIteratorNext(teoMapIterator *map_it);
teoMapElementData *teoMapIteratorPrev(teoMapIterator *map_it);

/**
 * Get element selected last map net or map previous iterator function
 *
 * @param map_it Pointer to teoMapIterator
 * @return Pointer to map element data teoMapValueData
 */
static
inline teoMapElementData *teoMapIteratorElement(teoMapIterator *map_it) {
    return map_it ? map_it->tmv : NULL;
}
/**
 * Get key from map element data
 *
 * @param el Pointer to teoMapElementData
 * @param key_length [out] Key length
 * @return Pointer to key
 */
static
inline uint8_t *teoMapIteratorElementKey(teoMapElementData *el,
        size_t *key_length) {
    if(key_length) *key_length = el->key_length;
    return el->data;
}
/**
 * Get data from map element data
 *
 * @param el Pointer to teoMapElementData
 * @param data_length [out] Data length
 * @return Pointer to data
 */
static
inline uint8_t *teoMapIteratorElementData(teoMapElementData *el,
        size_t *data_length) {
    if(data_length) *data_length = el->data_length;
    return el->data + el->key_length;
}

typedef int (*teoMapForeachFunction)(teoMap *m, int idx, teoMapElementData *d, void* user_data);
int teoMapForeach(teoMap *m, teoMapForeachFunction callback, void *user_data);

#ifdef __cplusplus
}
#endif

#endif /* MAP_H */
