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
 * \file   map.h
 * \author Kirill Scherba <kirill@scherba.ru>
 *
 * Created on June 6, 2016, 12:26 PM
 */

#ifndef MAP_H
#define MAP_H

#include <stdint.h>

#include "queue.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#define HASH_TABLE_SIZE 100
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
    char data[]; // Key + Data
    
} teoMapElementData;

typedef struct teoMapIterator {
    
    uint32_t idx;
    teoMap *map;
    teoQueueIterator *it;
    teoMapElementData *tmv;
    
} teoMapIterator;

//TRUDP_API 
void *teoMapGetFirst(teoMap *map, size_t *data_length); 
/**
 * Get number of elements in TR-UPD map
 *
 * @param map Pointer to teoMapData
 * @return Number of elements in TR-UPD map
 */
size_t teoMapSize(teoMap *map);

teoMap *teoMapNew(size_t size, int auto_resize_f);
void teoMapDestroy(teoMap *map);
void teoMapClear(teoMap *map);

void *teoMapAdd(teoMap *map, void *key, size_t key_length, void *data, 
  size_t data_length);
void *teoMapGet(teoMap *map, void *key, size_t key_length, 
  size_t *data_length);
int teoMapDelete(teoMap *map, void *key, size_t key_length);

teoMapIterator *teoMapIteratorNew(teoMap *map);
teoMapIterator *teoMapIteratorReverseNew(teoMap *map);
int teoMapIteratorFree(teoMapIterator *map_it);
teoMapElementData *teoMapIteratorNext(teoMapIterator *map_it);
teoMapElementData *teoMapIteratorPrev(teoMapIterator *map_it);

/**
 * Get element selected last map net or map previous iterator function
 * 
 * @param map_it Pointer to teoMapIterator
 * @return Pointer to map element data teoMapValueData
 */
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
inline void *teoMapIteratorElementKey(teoMapElementData *el, 
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
inline void *teoMapIteratorElementData(teoMapElementData *el, 
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

