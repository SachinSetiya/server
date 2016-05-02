#include"../../mysys/my_malloc.c"
#include"../../include/my_global.h"
typedef struct ma_hash_table{
	unsigned int hash_code;
	unsigned int  record_offset;
	struct ma_hash_table * next; //we will use single link list because no delete operations
} ma_hash_table;

ma_hash_table * ma_create_hash_table(int size){
	ma_hash_table * temp = (ma_hash_table *)my_malloc(sizeof(ma_hash_table)*size,MYF(MY_WME));
	ma_hash_table * _ht=temp;
	for(int i=0;i<100000;i++){
		temp->next=NULL;
		temp++;
	}
	return _ht;
}

int add_key_to_hash_table(ma_hash_table *_ht,unsigned int key , unsigned int offset){
	int temp = key % 100000;
	_ht=_ht+temp;
	ma_hash_table *parent;
	//transverse the whole list
	while(_ht!=NULL){
		if(_ht->hash_code==key)
			return 1;
		parent=_ht;
		_ht=_ht->next;
	}
	ma_hash_table *temp_hash = (ma_hash_table *)my_malloc(sizeof(ma_hash_table),MYF(MY_WME));
	temp_hash->hash_code=key;
	temp_hash->record_offset=offset;
	temp_hash->next=NULL;
	parent->next=temp_hash;
	return 0;
}

