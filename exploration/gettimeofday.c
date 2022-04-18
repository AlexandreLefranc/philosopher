/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettimeofday.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:42:49 by alefranc          #+#    #+#             */
/*   Updated: 2022/04/16 12:17:54 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// struct timeval {
// 	time_t      tv_sec;     /* seconds */
// 	suseconds_t tv_usec;    /* microseconds */
// };

struct timeval	delta_tv(struct timeval *tv2, struct timeval *tv1)
{
	struct timeval delta;

	delta.tv_sec = tv2->tv_sec - tv1->tv_sec;
	delta.tv_usec = tv2->tv_usec - tv1->tv_usec;
	return (delta);
}

int	main(void)
{
	struct timeval tv1;
	struct timeval tv2;
	struct timeval delta;

	gettimeofday(&tv1, NULL);
	printf("tv1.tv_sec=%ld; tv1.tv_usec=%ld\n", tv1.tv_sec, tv1.tv_usec);

	sleep(3);
	gettimeofday(&tv2, NULL);
	printf("tv1.tv_sec=%ld; tv1.tv_usec=%ld\n", tv2.tv_sec, tv2.tv_usec);

	delta = delta_tv(&tv2, &tv1);
	printf("delta.tv_sec=%ld; delta.tv_usec=%ld\n", delta.tv_sec, delta.tv_usec);

	return (0);
}
