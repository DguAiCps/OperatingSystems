#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>       // usleep
#include <vector>
#include <cstdlib>
#include <ctime>

sem_t printers;  // 프린터 자원 세마포어

void* print_job(void* arg) {
    int id = *(int*)arg;
    delete (int*)arg;

    // 프린터 대기
    sem_wait(&printers);
	// todo: usleep을 사용해서 random으로 생성된 시간 만큼 잠들기 


    std::cout << "Thread " << id << " released a printer after "
              << actual_used << " ms.\n";
    sem_post(&printers);

    return nullptr;
}

int main() {
    srand(time(NULL));
    sem_init(&printers, 0, 3);  // 프린터 3대

    std::vector<pthread_t> threads;

    for (int i = 0; i < 50; ++i) {
        int* tid = new int(i);
        pthread_t t;
        pthread_create(&t, nullptr, print_job, tid);
        threads.push_back(t);
    }

    for (auto& t : threads)
        pthread_join(t, nullptr);

    sem_destroy(&printers);
    return 0;
}

