
#include "philosophers.h"

int	init_all(t_philo_gen *philo_gen)
{
	if (create_mutex(philo_gen))
		return (1);
	if (init_philo(philo_gen))
		return (1);
	if (create_philo(philo_gen))
		return (1);
	return (0);
}