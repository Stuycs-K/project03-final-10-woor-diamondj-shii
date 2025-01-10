#include "game.h"

#define SEMKEY 826534
#define SHMKEY 98195187

union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};

int main() {
  while (1) {
    // access semaphore
    printf("waiting for turn...\n");
    int semd = semget(SEMKEY, 1, 0);
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;

    // decrement semaphore
    semop(semd, &sb, 1);

    // accessing shared data
    char* answer = (char*) malloc(6 * sizeof(char));
    int shmid = shmget(SHMKEY, 0, 0);
    answer = shmat(shmid, 0, 0);

    // simulating turn
    printf("answer is %s\n", answer);
    printf("taking turn (3 seconds)\n");
    sleep(3);
    printf("turn over\n");

    // increment semaphore
    sb.sem_op = 1;
    semop(semd, &sb, 1);
  }
}
