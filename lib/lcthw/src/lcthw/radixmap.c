#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <lcthw/radixmap.h>
#include <lcthw/dbg.h>

RadixMap *RadixMap_create(size_t max){
    RadixMap *map = calloc(sizeof(RadixMap),1);
    check_mem(map);
    
    map->contents = calloc(sizeof(RMElement),max+1);
    check_mem(map->contents);

    map->temp = calloc(sizeof(RMElement),max+1);
    check_mem(map->temp);

    map->max = max;
    map->end = 0;

    return map;
error:
    return NULL;
}

void RadixMap_destroy(RadixMap *map){
    if(map){
        free(map->contents);
        free(map->temp);
        free(map);
    }
}

#define ByteOf(x,y) (((uint8_t *)x)[(y)])

static inline void radix_sort(short offset,uint64_t max,uint64_t *src,uint64_t *dst){
    uint64_t count[256] = {0};
    uint64_t *cp = NULL, *sp = NULL, *end = NULL; 
    uint64_t s, c = 0;
    
    for(sp = src,end=src + max; sp< end;sp++){
        count[ByteOf(sp,offset)]++;
    }

    for (s = 0,cp=count,end=count+256;cp<end;cp++){
        c=*cp;
        *cp=s;
        s+=c;
    }

    for(sp=src,end=src+max;sp<end;sp++){
        cp = count+ByteOf(sp,offset);
        dst[*cp] = *sp;
        ++(*cp);
    }
}

void RadixMap_sort(RadixMap *map){
    uint64_t *source = &map->contents[0].raw;
    uint64_t *temp = &map->temp[0].raw;

    radix_sort(0,map->end,source,temp);
    radix_sort(1,map->end,temp,source);
    radix_sort(2,map->end,source,temp);
    radix_sort(3,map->end,temp,source);
}

RMElement *RadixMap_find(RadixMap *map,uint32_t to_find){
    int low = 0;
    int high = map->end -1;
    RMElement *data = map->contents;

    while(low <= high){
        int middle = low + (high - low);
        uint32_t key = data[middle].data.key;
        if(to_find < key){
            high = middle-1;
        } else if(to_find > key){
            low = middle-1;
        } else{
            return &data[middle];
        } 
    }
    return NULL;
}

int RadixMap_add(RadixMap *map,uint32_t key,uint32_t value){
    check(key < UINT32_MAX, "key cant be to large!");

    RMElement element = {.data={.key=key,.value=value}};
    check(map->end + 1 < map->max,"RadixMap is full.");

    map->contents[map->end++] = element;
    RadixMap_sort(map);

    return 0;
error:
    return -1;
}

int RadixMap_delete(RadixMap *map, RMElement *val){
    check(map->end > 0,"There is nothing to delete!");
    check(val != NULL, "Cant delete a NULL element");

    val->data.key = UINT32_MAX;

    if(map->end > 1){
        RadixMap_sort(map);
    }

    map->end--;

    return 0;
error:
    return -1;
}
