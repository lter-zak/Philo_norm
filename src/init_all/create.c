#include "philosophers.h"


void	*ft_thread_hendler(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	philo->fix_time = ft_time();
	if (philo->id % 2==0)
		go_to_eat(philo);
	else
	{
		ft_usleep(philo->time_to_eat);
		go_to_eat(philo);
	}
	return (0);
}

int	create_philo(t_philo_gen	*philo_gen)
{
	int	i;

	i = 0;
	philo_gen->thread_id = malloc(sizeof(pthread_t) * philo_gen->num_of_philo);
	while (i < philo_gen->num_of_philo)
	{
		if ((pthread_create(&(philo_gen->thread_id[i]), NULL,
					ft_thread_hendler, ((void *)&(philo_gen->philo[i])))) != 0)
			return (1);
			i++;
	}
	check_die(philo_gen, philo_gen->philo);
	return (0);
}

int	init_philo(t_philo_gen *philo_gen)
{
	int index;

	index = 0;
	philo_gen->philo = malloc(sizeof(t_philo) * philo_gen->num_of_philo);
	if (!(philo_gen->philo))
		return (1);
	while (index < philo_gen->num_of_philo)
	{
		philo_gen->philo[index].id = index;
		philo_gen->philo[index].right_fork = &philo_gen->forks_gen[(index + 1) % philo_gen->num_of_philo];
		philo_gen->philo[index].left_fork = &philo_gen->forks_gen[index];
		philo_gen->philo[index].time_to_eat = philo_gen->time_to_eat;
		philo_gen->philo[index].time_to_sleep = philo_gen->time_to_sleep;
		philo_gen->philo[index].philo_gen = philo_gen;
		philo_gen->philo[index].write = philo_gen->write;
		philo_gen->philo[index].fix_time = ft_time();
		philo_gen->philo[index].start_time = ft_time();
		philo_gen->philo[index].philo_must_eat = 0;
		index++;
	}
	return (0);
}

int	create_mutex(t_philo_gen	*philo_gen)
{
	int	index;

	index = 0;
	philo_gen->write = malloc(sizeof(pthread_mutex_t));
	philo_gen->forks_gen = malloc(sizeof(pthread_mutex_t) * philo_gen->num_of_philo);
	if (!(philo_gen->forks_gen))
		return (1);
	pthread_mutex_init(philo_gen->write, NULL);
	while (index < philo_gen->num_of_philo)
	{
		if (pthread_mutex_init(&philo_gen->forks_gen[index], NULL))
			return (1);
		index++;
	}
	return (0);
}