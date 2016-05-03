void consumer(){
	int end_of_slots = 10;
	int i =0;
	int position_of_filled_slot;
  while(!noMoreFiles && (end_of_slots != -1)){
		if (noMoreFiles)
			end_of_slots-- ;
		position_of_filled_slot =10;

		sem_wait(&full);	//ONE THREAD AT A TIME
		pthread_mutex_lock(&mutexFractal);

		for(i = 0; i<10; i++){
			if (get_height_value(slots[i])<0){
				position_of_filled_slot = i;
				break;
			}
		}
		fractal * fract = slots[position_of_filled_slot];
		slots[position_of_filled_slot] = emptyFract;
  	set_pixels(fract);

		pthread_mutex_unlock(&mutexFractal);
		sem_post(&empty);	//END ONE THREAD AT A TIME

		if (printAll == 1){
			write_bitmap_sdl(fract, fract->name);
		}
		else{

      pthread_mutex_lock(&meanMutex);

      fract_mean_value = get_mean_value(fract);
			if(highest_mean_value<fract_mean_value){
				highest_fract = fract;
				highest_mean_value = fract_mean_value;
			}

			pthread_mutex_unlock(&meanMutex);

		}//else
	}//while
}
