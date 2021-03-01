#ifndef __map_h
#define __map_h

#include <stdint.h>
#include <c/dbg.h>
#include <c/vector.h>

#define DEFAULT_BUCKET_NUM 100

typedef int (*Map_Compare)(void *a, void *b);
typedef uint32_t (*Map_Hash)(void *key);

typedef struct Map {
	Vector *buckets;
	Map_Compare compare;
	Map_Hash hash;
} Map;

typedef struct Map_Node{
	void *key;
	void *data;
	uint32_t hash;
}Map_Node;

typedef int (*Map_Travese_Func)(Map_Node *node);


static inline int default_compare(void *a, void *b){
	return strcmp((char *)a,(char*)b);
} 
 
static inline uint32_t default_hash(void *key){
	size_t len = strlen((char *)key);
	char *k = (char *)key;

	uint32_t hash = 0;
	uint32_t i = 0;

	for(hash=i=0;i<len;++i){
		hash += k[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

static inline void Map_Destroy(Map *m){
	int i = 0;
	int j = 0;
	if(m){
		if(m->buckets){
			for(i=0;i<Vector_End(m->buckets);i++){
				Vector *bucket = (Vector *)Vector_Get(m->buckets,i);
				if(bucket){
					for(j=0;j<Vector_End(bucket);j++){
						free(Vector_Get(bucket,j));
					}
					Vector_Destroy(bucket);
				}
			}
			Vector_Destroy(m->buckets);
		}
	free(m);
	}
}

static inline Map *Map_New(Map_Compare compare,Map_Hash hash){
	Map *map = (Map *)calloc(1,sizeof(Map));	
	check_memory(map);

	map->compare = compare==NULL?default_compare:compare;
	map->hash = compare==NULL?default_hash:hash;

	map->buckets = Vector_New(sizeof(Vector *),DEFAULT_BUCKET_NUM);
	check_memory(map->buckets);

	map->buckets->end = map->buckets->max;
	return map;	

error:
	if(map){Map_Destroy(map);}
	return NULL;
}


static inline Map_Node *Map_Node_New(int hash,void *key,void *data){
		Map_Node *node = (Map_Node *)calloc(1,sizeof(Map_Node));
		check_memory(node);

		node->key = key;
		node->data = data;
		node->hash = hash;
		
		return node;
error:
	return NULL;		
}

static inline Vector *Map_Find_Bucket(Map *m,void *key,int create,uint32_t *hash_out){
	uint32_t h = m->hash(key); 
	int bucket_n = h % DEFAULT_BUCKET_NUM;
	check(bucket_n >= 0,"Invalid bucket got %d",bucket_n);

	*hash_out = h;
	Vector *bucket = Vector_Get(m->buckets,bucket_n);

	if((bucket == NULL) && create){
			bucket = Vector_New(sizeof(void *),DEFAULT_BUCKET_NUM);
			check(bucket!=NULL,"Could not create Bucket");
			Vector_Set(m->buckets,bucket_n,bucket);
	}

	return bucket;
error:
	return NULL;
}

static inline int Map_Set(Map *m,void *key,void *data){
	uint32_t h = 0;

	Vector *bucket = Map_Find_Bucket(m,key,1,&h);
	check(bucket != NULL,"Did not find or Create Bucket");
	
	Map_Node *node = Map_Node_New(h,key,data);
	check(node != NULL,"Could not Create Node");

	Vector_Push(bucket,node);

	return 0;
error:
	return -1;
}

static inline int Map_Get_Node(Map *m,uint32_t hash,Vector *bucket,void *key){
	int i = 0;
	for(i=0;i< Vector_End(bucket); i++){
			Map_Node *node = (Map_Node *)Vector_Get(bucket,i);
			if(node->hash == hash && m->compare(node->key,key) == 0){
				return i;
			}

	}
	return -1;
}

static inline void *Map_Get(Map *m,void *key){
		uint32_t hash = 0;
		Vector *bucket = Map_Find_Bucket(m,key,0,&hash);
		if(bucket == NULL)
			return NULL;

		int i = Map_Get_Node(m,hash,bucket,key);
		if(i == -1)
			return NULL;

		Map_Node *node = (Map_Node *)Vector_Get(bucket,i);
		check(node != NULL,"Failed to get node from bucket.");

		return node->data;
error:
		return NULL;
}

static inline int Map_Travese(Map *m,Map_Travese_Func func){
		int i = 0;
		int j = 0;
		int rc = 0;

		for(i = 0; i < Vector_End(m->buckets); i++){
			Vector *bucket = (Vector *)Vector_Get(m->buckets,i);
			if(bucket){
				for(j = 0;j<Vector_End(bucket);j++){
					Map_Node *node = (Map_Node *)Vector_Get(bucket,j);
					rc = func(node);	
					if(rc != 0){
							return rc;
					}
				}
			}
		}
		return 0;
}

static inline void *Map_Delete(Map *m,void *key){
	uint32_t hash = 0;
	Vector *bucket = Map_Find_Bucket(m,key,0,&hash);
	if(!bucket)
		return NULL;

	int i = Map_Get_Node(m,hash,bucket,key);
	if(i==-1)
		return NULL;

	Map_Node *node = (Map_Node *)Vector_Get(bucket,i);
	void *data = node->data;
	free(node);

	Map_Node *ending = (Map_Node *)Vector_Pop(bucket);	
	if(ending != node){
		Vector_Set(bucket,i,ending);
	}

	return data;

error:
	return NULL;
}

#endif
