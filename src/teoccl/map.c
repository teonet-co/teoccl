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
 *
 * \file   map.c
 * \author Kirill Scherba <kirill@scherba.ru>
 *
 * Created on June 6, 2016, 12:26 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "teoccl/map.h"
#include "teoccl/hash.h"
#include "teoccl/memory.h"

// Local functions
static
teoMapElementData *_teoMapGet(teoMap *map, const uint8_t *key,
        size_t key_length, uint32_t hash);

static
uint32_t _teopMapHash(const uint8_t *key, size_t key_length);

static
teoMap *_teoMapResize(teoMap *map, size_t size);

static
teoQueueData *_teoMapValueDataToQueueData(teoMapElementData *mvd);


size_t teoMapSize(teoMap *map) {
    return map ? map->length : -1;
}

/**
 * Create new map
 *
 * @param size Size of hash map (hash map resized automatically)
 * @param auto_resize_f Auto resize hash map
 * @return Pointer to teoMapData
 */
teoMap *teoMapNew(size_t size, int auto_resize_f) {
    teoMap *map = (teoMap *)ccl_malloc(sizeof(teoMap));

    // Fill parameters
    map->q = (teoQueue **)ccl_malloc(size * sizeof(teoQueue*));
    map->auto_resize_f = auto_resize_f;
    map->hash_map_size = size;
    map->collisions = 0;
    map->length = 0;

    // Create Hash table
    for(size_t i = 0; i < size; i++) {
        map->q[i] = teoQueueNew();
    }

    return map;
}

/**
 * Resize hash table
 *
 * @param map Pointer to teoMapData
 * @param size New hash map size
 * @return Pointer to the same teoMapData
 */
static teoMap *_teoMapResize(teoMap *map, size_t size) {
    // Show mime of resize for testing
    // #define _SHOW_FUNCTION_MSG_ 1
    #if _SHOW_FUNCTION_MSG_
    printf("resize map from %d to %d, time: ", (int)map->hash_map_size, (int)size);
    uint64_t t_stop, t_beg = teoGetTimestampFull();
    #endif

    size_t i = 0;
    teoMap *map_new = teoMapNew(size, map->auto_resize_f);

    // Loop through existing map and add it elements to new map
    teoMapIterator it;
    teoMapIteratorReset(&it, map);

    while(teoMapIteratorNext(&it)) {
        teoMapElementData *el = teoMapIteratorElement(&it);

        #define _SHOW_RESIZED_MSG_ 0
        #if _SHOW_RESIZED_MSG_
        printf("\n #%u hash: %010u, key: %s, value: %s ",
                (uint32_t)i, el->hash, (char*)el->data, (char*)el->data + el->key_length);
        #endif


        #define _USE_PUT_ 1
        #if _USE_PUT_
        int idx = el->hash % map_new->hash_map_size;
        teoQueueData *qd_new, *qd = _teoMapValueDataToQueueData(el);
        qd_new = teoQueueNewData(qd->data, qd->data_length);
        qd_new->prev = qd->prev;
        qd_new->next = qd->next;
        teoQueuePut(map_new->q[idx], qd_new);
        map_new->length++;
        #else
        size_t key_length;
        void *key = teoMapIteratorElementKey(el, &key_length);
        size_t data_length;
        void *data = teoMapIteratorElementData(el, &data_length);
        teoMapAdd(map_new, key, key_length, data, data_length);
        #endif

        i++;
    }

    // Free existing queues and move queues pointer of new map to existing
    for (i = 0; i < map->hash_map_size; i++) {
        teoQueueFree(map->q[i]);
        free(map->q[i]);
    }

    free(map->q);
    map->q = map_new->q;
    map->hash_map_size = size;
    map->length = map_new->length;
    map->collisions = 0;
    free(map_new);

    #if _SHOW_FUNCTION_MSG_
    t_stop = (teoGetTimestampFull() - t_beg);
    printf("%.3f ms\n", t_stop / 1000.0);
    #endif

    return map;
}

/**
 * Destroy map
 *
 * @param map Pointer to teoMapData
 */
void teoMapDestroy(teoMap *map) {
    if(map) {
        for(size_t i = 0; i < map->hash_map_size; i++) {
            teoQueueDestroy(map->q[i]);
        }
        free(map->q);
        free(map);
    }
}

void teoMapClear(teoMap *map) {
  if (map) {
    for (size_t i = 0; i < map->hash_map_size; i++) {
      teoQueueFree(map->q[i]);
    }
    _teoMapResize(map, HASH_TABLE_SIZE);
  }
}

/**
 * Calculate hash for selected key
 *
 * @param key Pointer to key
 * @param key_length Key length
 * @return
 */
static inline uint32_t _teopMapHash(const uint8_t *key, size_t key_length) {

    // Select one of several hash functions
    #define _USE_HASH_ 0
    #if _USE_HASH_ == 0
    uint32_t hash = teoHashFast(key, key_length, HASH_TABLE_INITVAL);
    #elif _USE_HASH_ == 1
    uint32_t hash = teoHashSuperFast(key, key_length);
    #endif

    return hash;
}

/**
 * Get element from hash table
 *
 * @param map Pointer to teoHashTdata
 * @param key Key
 * @param key_length Key length
 * @param hash Hash of key
 *
 * @return Pointer to teoMapValueData of selected key or NULL if not found
 */
static teoMapElementData *_teoMapGet(teoMap *map, const uint8_t *key, size_t key_length,
        uint32_t hash) {
    teoMapElementData *element = NULL;

    int idx = hash % map->hash_map_size;

    teoQueueIterator it;
    teoQueueIteratorReset(&it, map->q[idx]);

    teoQueueData *tqd;
    while((tqd = teoQueueIteratorNext(&it))) {

        teoMapElementData* htd = (teoMapElementData *)tqd->data;
        if(htd->hash == hash) {

            if(key_length == htd->key_length &&
                !memcmp(htd->data, key, key_length)) {

                element = htd;
                break;
            }
            else map->collisions++;
        }
    }

    return element;
}

/**
 * Get first available element from hash table
 *
 * @param map Pointer to teoHashTdata
 * @param data_length [out] Pointer to returned data length (may be NULL)
 *
 * @return Pointer to Data of first available element or (void*)-1 if not found
 */
void *teoMapGetFirst(teoMap *map, size_t *data_length) {

    void *data = (void*)-1;
    if(data_length) *data_length = 0;

    teoMapIterator it;
    teoMapIteratorReset(&it, map);

    teoMapElementData *el;
    if((el = teoMapIteratorNext(&it))) {
        data = teoMapIteratorElementData(el, data_length);
    }

    return data;
}

/**
 * Get pointer to maps queue data from pointer to teoMapValueData
 *
 * @param mvd Pointer to teoMapValueData
 * @return Pointer to maps queue data
 */
static inline teoQueueData *_teoMapValueDataToQueueData(teoMapElementData *mvd) {
    return mvd ? (teoQueueData *)((char *)mvd - sizeof(teoQueueData)) : NULL;
}

/**
 * Add (or update) key data to the map
 *
 * @param map Pointer to teoMapData
 * @param key Pointer to key
 * @param key_length Key length
 * @param data Pointer to data
 * @param data_length Data length
 * @return Data of added key or (void*)-1 at error
 */
void *teoMapAdd(teoMap *map, void *key, size_t key_length, void *data,
        size_t data_length) {

    void *r_data = (void*)-1;

    if(!data) data_length = 0;

    // Create and fill Data structure
    size_t htd_length = sizeof(teoMapElementData) + key_length + data_length;
    teoMapElementData *htd = (teoMapElementData *) ccl_malloc(htd_length);
    htd->hash = _teopMapHash(key, key_length);
    htd->key_length = key_length;
    htd->data_length = data_length;
    memcpy(htd->data, key, key_length);
    if(data_length) memcpy(htd->data + htd->key_length, data, data_length);

    // Check that key exist and add data to map if not exists
    teoQueueData *tqd;
    teoMapElementData* htd_existing = _teoMapGet(map, key, key_length, htd->hash);
    // Add data to map
    if (htd_existing == NULL) {
        int idx = htd->hash % map->hash_map_size;
        tqd = teoQueueAdd(map->q[idx], (void*)htd, htd_length);
        if(tqd) {
            map->length++;

            // Resize if needed
            if(map->auto_resize_f && map->length > map->hash_map_size * 3)
                _teoMapResize(map, map->hash_map_size * 10);
        }
    }
    // Update existing key data
    else {
        tqd = _teoMapValueDataToQueueData(htd_existing);
        int idx = htd->hash % map->hash_map_size;
        tqd = teoQueueUpdate(map->q[idx], (void*)htd, htd_length, tqd);
    }

    // Free allocated data
    free(htd);

    // Set pointers to teoMapValueData and returned data
    if(tqd) {
        htd = (teoMapElementData *)tqd->data;
        r_data = htd->data_length ? htd->data + htd->key_length : NULL;
    }

    return r_data;
}

/**
 * Get key data from hash table
 *
 * @param map Pointer to teoMapData
 * @param key Pointer to key
 * @param key_length Key length
 * @param data_length [out] Pointer to data length
 *
 * @return Data of selected key (may be NULL) or (void*)-1 if not found
 */
void *teoMapGet(teoMap *map, void *key, size_t key_length,
        size_t *data_length) {
    uint8_t* data = (uint8_t*)-1;
    size_t element_data_length = 0;

    uint32_t hash = _teopMapHash(key, key_length);
    teoMapElementData* element = _teoMapGet(map, key, key_length, hash);

    if (element != NULL) {
        element_data_length = element->data_length;
        data = element_data_length > 0 ? element->data + element->key_length : NULL;
    }

    if (data_length != NULL) {
        *data_length = element_data_length;
    }

    return data;
}

/**
 * Delete keys element from map
 *
 * @param map Pointer to teoMapData
 * @param key Pointer to key
 * @param key_length Key length
 * @return Zero at success, or errors: -1 - keys element not found
 */
int teoMapDelete(teoMap *map, void *key, size_t key_length) {

    int rv = -1;

    uint32_t hash = _teopMapHash(key, key_length);
    teoMapElementData* map_element = _teoMapGet(map, key, key_length, hash);
    if (map_element != NULL) {
        teoQueueData *tqd = _teoMapValueDataToQueueData(map_element);
        int idx = map_element->hash % map->hash_map_size;
        rv = teoQueueDelete(map->q[idx], tqd);
        if(!rv) {
            map->length--;

            // Resize if needed
            if(map->auto_resize_f &&
               map->hash_map_size > 10 && map->length < (map->hash_map_size / 10) * 3)
                _teoMapResize(map, map->hash_map_size / 10);
        }
    }

    return rv;
}

/**
 * Create new map iterator
 *
 * @param map Pointer to teoMapData
 * @return Pointer to teoMapIterator or NULL at memory allocate error
 */
teoMapIterator *teoMapIteratorNew(teoMap *map) {

    teoMapIterator *map_it = (teoMapIterator*)ccl_malloc(sizeof(teoMapIterator));
    teoMapIteratorReset(map_it, map);

    return map_it;
}

/**
 * Reset map iterator. Binds iterator to map, set forward iteration direction.
 *
 * @param map_it Pointer to teoMapIterator
 * @param map Pointer to teoMapData
 */
void teoMapIteratorReset(teoMapIterator *map_it, teoMap *map) {

    if(map_it) {
        teoQueueIteratorReset(&map_it->it, map->q[0]);
        map_it->idx = 0;
        map_it->map = map;
        map_it->tmv = NULL;
    }
}

/**
 * Create new map reverse iterator
 *
 * @param map Pointer to teoMapData
 * @return Pointer to teoMapIterator or NULL at memory allocate error
 */
teoMapIterator *teoMapIteratorReverseNew(teoMap *map) {

    teoMapIterator *map_it = (teoMapIterator*)ccl_malloc(sizeof(teoMapIterator));
    teoMapIteratorReverseReset(map_it, map);

    return map_it;
}

/**
 * Reset map iterator. Binds iterator to map, set reverse iteration direction.
 *
 * @param map_it Pointer to teoMapIterator
 * @param map Pointer to teoMapData
 */
void teoMapIteratorReverseReset(teoMapIterator *map_it, teoMap *map) {

    if(map_it) {
        teoQueueIteratorReset(&map_it->it, map->q[map->hash_map_size - 1]);
        map_it->idx = map->hash_map_size - 1;
        map_it->map = map;
        map_it->tmv = NULL;
    }
}

/**
 * Destroy map iterator
 *
 * @param map_it Pointer to teoMapIterator
 * @return Zero at success
 */
int teoMapIteratorFree(teoMapIterator *map_it) {

    if(map_it) {
        free(map_it);
    }

    return 0;
}

/**
 * Get next maps element
 *
 * @param map_it Pointer to teoMapIterator
 * @return Pointer to map element data teoMapValueData
 */
teoMapElementData *teoMapIteratorNext(teoMapIterator *map_it) {

    if(!map_it) return NULL;

    teoQueueData *tqd;
    teoMapElementData *tmv = NULL;

    while(!(tqd = teoQueueIteratorNext(&map_it->it))) {
        if(++map_it->idx < map_it->map->hash_map_size) {
            teoQueueIteratorReset(&map_it->it, map_it->map->q[map_it->idx]);
        }
        else break;
    }

    if(tqd) {
        tmv = (teoMapElementData *)tqd->data;
        map_it->tmv = tmv;
    }

    return tmv;
}


/**
 * Get previous maps element
 *
 * @param map_it Pointer to teoMapIterator
 * @return Pointer to map element data teoMapValueData
 */
teoMapElementData *teoMapIteratorPrev(teoMapIterator *map_it) {

    if(!map_it) return NULL;

    teoQueueData *tqd;
    teoMapElementData *tmv = NULL;

    while(!(tqd = teoQueueIteratorPrev(&map_it->it))) {
        if(--map_it->idx != UINT32_MAX) {
            teoQueueIteratorReset(&map_it->it, map_it->map->q[map_it->idx]);
        }
        else break;
    }

    if(tqd) {
        tmv = (teoMapElementData *)tqd->data;
        map_it->tmv = tmv;
    }

    return tmv;
}


/**
 * Loop through map and call callback function with index and data in parameters
 *
 * @param m Pointer to teoMap
 * @param callback Pointer to callback function teoMapForeachFunction
 *
 * @return Number of elements processed
 */
int teoMapForeach(teoMap *map, teoMapForeachFunction callback,
        void *user_data) {

    int i = 0;
    teoMapIterator it;
    teoMapIteratorReset(&it, map);

    while(teoMapIteratorNext(&it)) {
        if(callback(map, i++, teoMapIteratorElement(&it), user_data)) break;
    }

    return i;
}
