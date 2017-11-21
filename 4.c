#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t a_mutex;

int count_add = 0;
int count_find = 0;
int count_del = 0;

void *find();
void *add();
void *delete();

struct node{
	int data;
	struct node* next;
}

main(){
	//ввод кол-ва добавлятелей, поисковиков и удалятелей
	printf("Введите M, N, K: ");
	int M, N, K;
	scanf("%d%d%d", &M, &N, &K);
	
	struct node* head = NULL;
	add(&head);
	//объявление потоков
	pthread_t add_thread[M];
	pthread_t find_thread[N];
	pthread_t delete_thread[K];
	//для вывода времени
	struct tm *tm_ptr;
 	time_t the_time;
 	(void)time(&the_time);
 	tm_ptr = gmtime(&the_time);
	//arg->head = head;
	pthread_mutex_init(&a_mutex, NULL);
	//create потоков
	for(int i=1; i<M; i++){	
		pthread_create(&add_thread[i], NULL, add, &head);
	}
	for(int j=1; j<N; j++){	
		pthread_create(&find_thread[j], NULL, find, &head);
		
	}
	for(int l=1; l<K; l++){
		pthread_create(&delete_thread[l], NULL, delete, &head);	
	}
	
	for(int i=1; i<M; i++){	
		pthread_join(add_thread[i], NULL);
	}

	for(int j=1; j<N; j++){	
		pthread_join(find_thread[j], NULL);
	}

	for(int l=1; l<K; l++){ 
		pthread_join(delete_thread[l], NULL);
	}   
}

void *find(struct node** head){
 	sleep(rand()%(4));
	struct tm *tm_ptr;
 	time_t the_time;
 	(void)time(&the_time);
 	tm_ptr = gmtime(&the_time);
	count_find++;
	printf("%02d:%02d:%02d Поисковик #%d хочет начать поиск. \n",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec,count_find);
	//поиск
	printf("%02d:%02d:%02d Поисковик #%d закончил поиск. \n",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec,count_find);
}

void *add(struct node** head){
	struct tm *tm_ptr;
	sleep(rand()%(7));
 	time_t the_time;
 	(void)time(&the_time);
 	tm_ptr = gmtime(&the_time);
	count_add++;
	printf("%02d:%02d:%02d Добавлятель #%d хочет начать добавление. \n",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, count_add);		
	pthread_mutex_lock(&a_mutex);
	printf("%02d:%02d:%02d Добавлятель #%d начал добавление. \n",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, count_add);
	struct node* newNode = malloc(sizeof(struct node));
	newNode->data = rand();
	newNode->next = *head;
	*head = newNode;
	pthread_mutex_unlock(&a_mutex);
	printf("%02d:%02d:%02d Добавлятель #%d закончил добавление. \n",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, count_add);
}

void *delete(struct node** head){
	struct tm *tm_ptr;
 	time_t the_time;
 	(void)time(&the_time);
 	tm_ptr = gmtime(&the_time);
	sleep(1);
	sleep(rand()%(7));
	count_del = count_del+1;
	printf("%02d:%02d:%02d Удалятель #%d хочет начать удаление. \n",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, count_del);
	pthread_mutex_lock(&a_mutex);	
	struct node * temp = *head;
  	int data=temp->data;
	if(temp->next != NULL){
		printf("%02d:%02d:%02d Удалятель #%d начал удаление. \n",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, count_del);
	  	*head = temp->next;
  		free(temp);
		printf("%02d:%02d:%02d Удалятель #%d закончил удаление. \n",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, count_del);
	} else{
		printf("Список пуст\n");
	}
	pthread_mutex_unlock(&a_mutex);
	

	}

