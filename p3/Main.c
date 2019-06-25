code Main

  -- OS Class: Project 3
  --
  -- Steve Braich
  -- 

-----------------------------  Main  ---------------------------------

  function main ()
	InitializeScheduler()
	test_SleepingBarber()
  endFunction


--------------------- Sleeping Barber Class Implementation ------------------
  behavior SleepingBarber
    -- This class provides the following methods:
    --    Init() 
	--      Initialize the semaphores and others vars
    --    barber()
    --         The barber executes this code to start his work day.  
	--         He alternates between sleeping, waiting, and cutting hair
    --    customer()
    --         Each customer executes this code to wait for a haircut
    --    cut_hair()
    --         Function to simulate time taken to cut hair
    --    get_haircut()
    --         Function used by customers to be seated and be served

	  ----------SleepingBarber. Init  ----------
		 
      method Init ()
	    -- Initalize Semaphores and member fields
		barbers = new Semaphore
		barbers.Init(0)
		customers = new Semaphore
		customers.Init(0)
        mutex = new Semaphore
		mutex.Init(1)
        waiting = 0
	  endMethod

	  ---------- SleepingBarber.Barber----------

	  method Barber ()
		while (true)
		  customers.Down()		    -- go to sleep if # of customers is 0
		  mutex.Down()			    -- acquire access to "waiting'
		  waiting = waiting - 1	    -- decrement count of waiting customers
		  barbers.Up()			    -- one barber is now ready to cut hair
		  mutex.Up()				-- release 'waiting'
		  self.cut_hair()			-- cut hair (outside critical region)
	    endWhile	
      endMethod

	  ---------- SleepingBarber.customer ----------

	  method Customer (id: int)
        mutex.Down()				-- enter critical region
	    -- Print Enter
		if waiting < CHAIRS			-- if there are no free chairs, leave
		  waiting = waiting + 1	    -- increment count of waiting customers
		  -- Print S
		  customers.Up()			-- wake up barber if necessary
		  mutex.Up()				-- release access to 'waiting'
		  barbers.Down()			-- go to sleep if # of free barbers is 0
	      self.get_haircut()		-- be seated and be served
		else
		    mutex.Up()				-- shop is full; do not wait
			--print L
		endIf
      endMethod

	  ---------- Private Methods ----------

	  -- Simulates cutting a customers hair
	  method cut_hair()
        var 
          i: int
	    for i = 1 to 100
			currentThread.Yield()
        endFor
		-- Print - end
	  endMethod

      -- Simulates being seated and served
      method get_haircut () 
        var
          i : int
		-- Print - Start
        for i = 1 to 100
			currentThread.Yield()
        endFor
      endMethod

  endBehavior

  ----------------- Test Sleeping Barber -----------------------------------------
  function BarberThreadMethodInit(x: int)
    (x asPtrTo SleepingBarber).Barber()
  endFunction

  function CustomerThreadMethodInit(x: int)
    (x asPtrTo SleepingBarber).Customer(customer_index)
  endFunction

  const
	CHAIRS = 5
    BARBER_COUNT = 1
	CUSTOMER_COUNT = 10 

  var
	barbershop : SleepingBarber = new SleepingBarber
	barb_threads : array[BARBER_COUNT] of Thread = new array of Thread { BARBER_COUNT of new Thread}
	cust_threads : array[CUSTOMER_COUNT] of Thread = new array of Thread { CUSTOMER_COUNT of new Thread}
    customer_index: int

  function test_SleepingBarber()
    var
      classPtr: ptr to SleepingBarber

	classPtr 
    barbershop.Init()
	-- Test that barbershop is initialized

	print("barbershop.barbers.count: ")
	printInt(barbershop.barbers.count)
	print("\n")

	print ("barbershop.customers.count: ")
	printInt (barbershop.customers.count)
	print ("\n")

    barb_threads[0].Init("Barber")
    barb_threads[0].Fork(BarberThreadMethodInit, classPtr asInteger)

    print("         Barber  1  2  3  4  5  6  7  8  9  10 \n")
    cust_threads[0].Init("Customer #1")
    cust_threads[1].Init("Customer #2")
    cust_threads[2].Init("Customer #3")
    cust_threads[3].Init("Customer #4")
    cust_threads[4].Init("Customer #5")
    cust_threads[5].Init("Customer #6") 
    cust_threads[6].Init("Customer #7")
    cust_threads[7].Init("Customer #8")
    cust_threads[8].Init("Customer #9")
    cust_threads[9].Init("Customer #10")

    for customer_index = 0 to CUSTOMER_COUNT - 1
      cust_threads[customer_index].Fork(CustomerThreadMethodInit, classPtr asInteger)
    endFor

	ThreadFinish()
	
  endFunction

endCode
	

