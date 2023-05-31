#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define MAX_CHAR 256
#define TABLE_SIZE 20


typedef struct Person{
	char *name;
	int age;
}Person;



int hash_fuction(char* name){
	int lenght = strlen(name), sum = 0;

	for(int i = 0; i<lenght; i++){
		sum=name[i]*name[i];
		sum=sum*name[i];
	}

	return sum%TABLE_SIZE;
}


Person** init_hash(){
	Person** hash_table = malloc(TABLE_SIZE*sizeof(Person));
	for(size_t i=0; i<TABLE_SIZE; i++){
		hash_table[i] = NULL;
	}
	return hash_table;
}

void print_hash_tabel(Person** hash_table){
	for(size_t i=0; i<TABLE_SIZE; i++){
		if(!hash_table[i]) printf("\t%d ---- \t\n", i);
		else{printf("\t%d %s\t\n",i, hash_table[i]->name);}
	}
	printf("\n");
}


Person** insert(Person* info, Person** hash_table){
	
	int colisions = 0, invalid_positions = 0;
	if(!info) {printf("invalid value");return 0;}

	int index = hash_fuction(info->name);

	if(hash_table[index]) 
		{
			for(size_t i=0; i<TABLE_SIZE; i++){
				int position = (i+index)%TABLE_SIZE;
				if(!hash_table[position]){ hash_table[position]=info; printf("\nperson %s was successfully inserted\n", info->name);return 0;}
				else invalid_positions++;
				if(invalid_positions>=TABLE_SIZE) {printf("\ncan`t insert new person!\n"); return 0;}
			}
		}
	else {hash_table[index] = info; printf("\nperson %s was successfully inserted\n", info->name);}
	return hash_table;
}

int find_person(char* name, Person** hash_table){
	if(!name) {printf("invalid value");return 0;}

	int index = hash_fuction(name), invalid_positions = 0;
	// printf("\nindex1 = %d\n", index);
	// printf("\n%d||%s\n", hash_table[index], name);
	if(!hash_table[index]){//if statement when the element on the position index is NULL 
		for(size_t i=0; i<TABLE_SIZE; i++){
	 		int position = (i+index)%TABLE_SIZE;
	 		// printf("i = %d ", i);
	 		if(hash_table[position])
	 			{
	 				if(!strcmp(hash_table[position]->name, name)&&hash_table[index]){ printf("Person %s was found!\n", name); return index;}
	 				else{invalid_positions++;}				
	 			}
	 		else {invalid_positions++; }
	 		if(invalid_positions>=TABLE_SIZE||i>=TABLE_SIZE-1) {printf("\n%s was not found\n", name); return -1;}
	 	}
	}
	else{//if statement when the element on the position index is not NULL 
		// printf("%d", strcmp(hash_table[index]->name, name));
		if(!strcmp(hash_table[index]->name, name)&&hash_table[index]){ printf("Person %s was found!\n", name); return index;}
		else {
			for(size_t i=0; i<TABLE_SIZE; i++){
		 		int position = (i+index)%TABLE_SIZE;
		 		// printf("i = %d ", i);
		 		if(hash_table[position]&&!strcmp(hash_table[position]->name, name)){ printf("\n%s was found!\n", name);  return position;}
		 		else {invalid_positions++; 
		 		if(invalid_positions>=TABLE_SIZE||i>=TABLE_SIZE-1) {printf("\n%s was not found\n", name); return -1;}
		 		}
		}
	}
}
}

void erase_person(char* name, Person** hash_table){
	if(!name){ printf("invalid value"); return;}
	int index = find_person(name, hash_table);
	// printf("\nindex = %d\n", index);
	if(index>-1) {hash_table[index]=NULL; printf("%s was succesfully erased!\n", name); return;}
	else {printf("invalid person!\n"); return;}
}

void erase_all_positions(Person** hash_table){
	int count = 0;
	for(size_t i=0; i<TABLE_SIZE;i++){
		if(hash_table[i])hash_table[i] = NULL;
		else count++;
	}
	printf("\ncount = %d\n", count);
	if(count==TABLE_SIZE)
	{
		printf("\nHash_table is alredy empty\n");
		return;

	}
	printf("\nAll persons has been succesfully eraced\n");

}


void init_name(Person *person_name){
	person_name->name = malloc(MAX_CHAR);
}


void input_function(char* name, Person** hash_table){
	Person *person = malloc(sizeof(Person));
	init_name(person);
	strcpy(person->name, name);
	insert(person, hash_table);

}

Person** free_hash_table(Person** hash_table){
	for(size_t i=0; i<TABLE_SIZE; i++)
		free(hash_table[i]);
	hash_table = NULL;

	return hash_table;
}

int main(int argc, char const *argv[])
{	
	Person **hash_table;
	char name[100];
	int t = 1, alegere;

	hash_table = init_hash();

	while(t){	
		printf("Type option : \n1.Enter person\n2.Print all people\n3.Erace person\n4.Find person\n5.Erace all people\n0. Exit\n");
		
		if(scanf("%d", &alegere)>0){
			switch(alegere){
			case 1:{printf("Enter person: ");scanf("%s",name);input_function(name, hash_table);break;}
			case 2:{print_hash_tabel(hash_table); break;}
			case 3:{printf("input to erase person: ");scanf("%s", name);erase_person(name,hash_table); break;}
			case 4:{printf("input to find a person: ");scanf("%s", name); find_person(name, hash_table); break;}
			case 5:{printf("Erace all people: ");erase_all_positions(hash_table);}
			case 0:{return 0;}
			default: {break;}
			}	
		}
		else{
			printf("invalid value!!!\n ");
		}
			getchar();
			printf("continue 1/0 :"); 
			if(scanf("%d", &t)>0){printf("\n");continue;}
			else{printf("\nnu va jucati cu focul!!!\n");}
			// printf("\nt = %d\n", t);
	}
	
	// print_hash_tabel(hash_table);
	
	hash_table = free_hash_table(hash_table);	

	
	return 0;
}