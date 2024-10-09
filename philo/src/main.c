/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:42:30 by dasal             #+#    #+#             */
/*   Updated: 2024/10/09 12:42:43 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *thread(void *arg) {
  void *ret;
  printf("thread() entered with argument '%s'\n", (char *)arg);
  if ((ret = (char*) malloc(20)) == NULL) {
    perror("malloc() error");
    exit(2);
  }
  strcpy(ret, "This is a test");
  pthread_exit(ret);
}


long long get_timestamp_in_milliseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL); // Get the current time

    // Calculate milliseconds since epoch
    long long milliseconds = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    return milliseconds;
}

int main(void) {
  pthread_t thid;
  void *ret;
  
  long long timestamp = get_timestamp_in_milliseconds();
  printf("Current timestamp in milliseconds: %lld\n", timestamp);
  if (pthread_create(&thid, NULL, thread, "thread 1") != 0) {
    perror("pthread_create() error");
    exit(1);
  }
  if (pthread_join(thid, &ret) != 0) {
    perror("pthread_create() error");
    exit(3);
  }
  printf("thread exited with '%s'\n", (char *)ret);
  timestamp = get_timestamp_in_milliseconds();
  printf("Current timestamp in milliseconds: %lld\n", timestamp);
}
