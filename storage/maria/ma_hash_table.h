#include"../../mysys/my_malloc.c"
#include"../../include/my_global.h"
typedef struct ma_hash_table_element{
	unsigned int hash_code;
	unsigned int  record_offset;
	struct ma_hash_table * next; //we will use single link list because no delete operations
} ma_hash_table_element;

typedef struct ma_hash_table{
	unsigned int size;
	ma_hash_table_element * h_t_e;
}ma_hash_table;
ma_hash_table * ma_create_hash_table(int size){
	ma_hash_table_element * _ht = (ma_hash_table *)my_malloc(sizeof(ma_hash_table)*size,MYF(MY_WME));
	ma_hash_table_element * temp=_ht;
	for(int i=0;i<size;i++){
		temp->next=NULL;
		temp++;
	}
	ma_hash_table *temp_hash_table = (ma_hash_table *)my_malloc(sizeof(ma_hash_table),MYF(MY_WME));
	temp_hash_table->size =size;
	temp_hash_table->h_t_e = _ht;
	return temp_hash_table;
}

int add_key_to_hash_table(ma_hash_table *_ht,unsigned int key , unsigned int offset){
	int hash_position = key % _ht->size; //just a simple logic thinking of upgrading it may we whatever
	ma_hash_table_element *tmp= _ht->h_t_e;
	tmp = tmp+hash_position;
	ma_hash_table_element *parent;
	//transverse the whole list
	while(tmp!=NULL){
		if(tmp->hash_code==key)
			return 1;
		parent=tmp;
		tmp=tmp->next;
	}
	ma_hash_table_element *temp_hash = (ma_hash_table_element *)my_malloc(sizeof(ma_hash_table_element),MYF(MY_WME));
	temp_hash->hash_code=key;
	temp_hash->record_offset=offset;
	temp_hash->next=NULL;
	parent->next=temp_hash;
	return 0;
}

