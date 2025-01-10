#include "game.h"

void runGame(int semkey, int shmkey) {
  while (1) {
    // access semaphore
    printf("waiting for turn...\n");
    int semd = semget(semkey, 1, 0);
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;

    // decrement semaphore
    semop(semd, &sb, 1);

    // accessing shared data
    char* answer = (char*) malloc(6 * sizeof(char));
    int shmid = shmget(shmkey, 0, 0);
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
