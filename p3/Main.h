header Main

  uses System, Thread, Synch

  functions
    main ()

  class SleepingBarber
	superclass Object
    fields
	  customers : Semaphore
	  barbers : Semaphore
	  mutex : Semaphore
	  waiting: int
	methods
	  Init()
	  Barber()
      Customer(id: int)
	  
	  -- Private Methods
	  cut_hair()
	  get_haircut()

	  -- Printing Methods
      -- print_barbershop_waiting_list()
      -- print_barbershop_transaction()
  endClass
 

endHeader
