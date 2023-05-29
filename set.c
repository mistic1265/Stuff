#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define MAX_CHAR 256
#define TABLE_SIZE 10


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
	for(int i=0; i<TABLE_SIZE; i++){
		hash_table[i] = NULL;
	}
	return hash_table;
}

void print_hash_tabel(Person** hash_table){
	for(int i=0; i<TABLE_SIZE; i++){
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
			for(int i=0; i<TABLE_SIZE; i++){
				int poisition = (i+index)%TABLE_SIZE;
				if(!hash_table[poisition]){ hash_table[poisition]=info; printf("\nperson %s was successfully inserted\n", info->name);return 0;}
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
	printf("\nindex1 = %d\n", index);
	printf("\n%s||%s\n", hash_table[index]->name, name);
	// printf("%d", strcmp(hash_table[index]->name, name));
	
	if(!strcmp(hash_table[index]->name, name)&&hash_table[index]){ printf("Person %s was found!\n", name); return index;}
	else {
		for(int i=0; i<TABLE_SIZE; i++){
	 		int poisition = (i+index)%TABLE_SIZE;
	 		printf("i = %d ", i);
	 		if(!strcmp(hash_table[poisition]->name, name)&&hash_table[poisition]){ printf("\n%s was found!\n", name);  return poisition;}
	 		else {invalid_positions++; printf(" Ipos = %d", invalid_positions);}
	 		if(invalid_positions>=TABLE_SIZE||i>=TABLE_SIZE-1) {printf("\n%s was not found\n", name); return -1;}
	 	}
	}
}

void erase(char* name, Person** hash_table){
	if(!name){ printf("invalid value"); return;}
	int index = find_person(name, hash_table);
	printf("\nindex = %d\n", index);
	if(index>-1) {hash_table[index]=NULL; printf("%s was succesfully eraced!\n", name); return;}
	else {printf("invalid person!\n"); return;}
}

void erace_all(Person** hash_table){
	for(int i=0; i<TABLE_SIZE;i++){
		hash_table[i] = NULL;
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
	for(int i=0; i<TABLE_SIZE; i++)
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
	// input_function("maria", hash_table);
	// input_function("mar", hash_table);
	// input_function("ia", hash_table);
	// input_function("mara", hash_table);
	// find_person("ia", hash_table);


	while(t){	
		printf("Type option : \n1.Enter person\n2.Print all entered people\n3.Erace person\n4.Find person\n");
		
		scanf("%d", &alegere);
			switch(alegere){
			case 1:{scanf("%s",name);input_function(name, hash_table);break;}
			case 2:{print_hash_tabel(hash_table); break;}
			case 3:{printf("input to erace person: ");scanf("%s", name);erase(name,hash_table); break;}
			case 4:{printf("input to find a person: ");scanf("%s", name); find_person(name, hash_table); break;}
			default: {printf("invalid value!!!\n ");break;}
			}	
			getchar();
			printf("continuati :"); scanf("%d", &t);
			printf("\nt = %d\n", t);

	}
	
	// print_hash_tabel(hash_table);
	
	hash_table = free_hash_table(hash_table);	

	
	return 0;
}