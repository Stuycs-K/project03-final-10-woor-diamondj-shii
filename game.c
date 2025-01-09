<<<<<<< HEAD
#include "game.h"

#define KEY 826534

=======
#define SEMKEY 826534

>>>>>>> Julien
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
<<<<<<< HEAD
    int semd = semget(KEY, 1, 0);
=======
    int semd = semget(SEMKEY, 1, 0);
>>>>>>> Julien
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;

    // decrement semaphore
    semop(semd, &sb, 1);

    // simulating turn
    printf("taking turn (3 seconds)\n");
    sleep(3);
    printf("turn over\n");

    // increment semaphore
    sb.sem_op = 1;
    semop(semd, &sb, 1);
  }
}
